/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <string.h>

#include "getkeys.h"

#include "io.h"
#include "ctlrcomm.h"

// FIXME
#include "keytranslation.h"

enum neo_levels_e level_current = LEVEL1;

// key states
// Transmit states of all keys from slave to master. This is the simplest, most deterministic and probably most fail-safe approach (compared to sending only pressed keys or key state changes).

uint8_t key_state[2][ROW_COUNT] = {{0}, {0}};
uint8_t prev_key_state[2][ROW_COUNT] = {{0}, {0}};

bool level_mod [LEVEL_COUNT] = { false };
bool level_lock[LEVEL_COUNT] = { false };

#define CHANGED_KEYS_CNT_MAX 8
struct key_change_s changed_keys[CHANGED_KEYS_CNT_MAX] = {{ 0 }}; // XXX initialization is debugging aid only
uint8_t keychange_cnt = 0;

// FIXME
#include "sendkeys.c"

void update_own_key_states() {
    uint8_t row;
    for (row = 0; row < ROW_COUNT; ++row) {
        activate_row(row);
        key_state[CONTROLLER][row] = 0;
        uint8_t col;
        for (col = 0; col < COL_COUNT; ++col) {
            key_state[CONTROLLER][row] |= (test_col(col) << col);
        }
        deactivate_row(row);
    }
}

// key changes

enum key_change_e get_key_state(uint8_t controller, enum row_e row, uint8_t col) {
    return ((key_state[controller][row] & (1 << col)) > 0) ? KC_PRESS : KC_RELEASE;
}

void set_key_state(uint8_t controller, enum row_e row, uint8_t col, enum key_change_e state) {
    if (state == KC_PRESS) {
        key_state[controller][row] |=  (1 << col);
    } else {
        key_state[controller][row] &= ~(1 << col);
    }
}

void add_keychange(uint8_t row, uint8_t controller, uint8_t col, enum key_change_e change) {
    if (keychange_cnt < CHANGED_KEYS_CNT_MAX) {
        changed_keys[keychange_cnt].change = change;
        changed_keys[keychange_cnt].controller = controller;
        changed_keys[keychange_cnt].row = row;
        changed_keys[keychange_cnt].col = col;
        ++keychange_cnt;
    } else {
        warning(W_TOO_MANY_KEYS);
    }
}

void clear_changed_keys() {
    memset(changed_keys, 0, sizeof(changed_keys)); // XXX debugging aid only
    keychange_cnt = 0;
}

// FIXME
enum neo_levels_e determine_current_level() {
    enum neo_levels_e l = LEVEL1;

    if (level_lock[LEVEL3]) {
        if (level_lock[LEVEL4] || level_lock[LEVEL4_MOUSE]) {
            l = LEVEL6;
        } else if (level_lock[LEVEL2]) {
            l = LEVEL5;
        } else {
            l = LEVEL3;
        }
    } else if (level_lock[LEVEL4]) {
        l = LEVEL4;
    } else if (level_lock[LEVEL4_MOUSE]) {
        l = LEVEL4_MOUSE;
    } else if (level_lock[LEVEL2]) {
        l = LEVEL2;
    }

    if (level_mod[LEVEL3]) {
        if (level_mod[LEVEL4] || level_mod[LEVEL4_MOUSE]) {
            l = LEVEL6;
        } else if (level_mod[LEVEL2]) {
            l = LEVEL5;
        } else {
            l = LEVEL3;
        }
    } else if (level_mod[LEVEL4]) {
        l = LEVEL4;
    } else if (level_mod[LEVEL4_MOUSE]) {
        l = LEVEL4_MOUSE;
    } else if (level_mod[LEVEL2]) {
        l = LEVEL2;
    }

    if (level_mod[l] && level_lock[l]) {
        if (l != LEVEL2 && level_mod[LEVEL2]) {
            l = LEVEL2;
        } else {
            l = LEVEL1;
        }
    }

    dbg_uarttx_byte(0xC0 | l);

    return l;
}

void process_keychange(uint8_t row, uint8_t controller, uint8_t col) {
    flash_led();
    const struct keyleveltranslations_s klt = get_current_mapped_klt(controller, row, col);
    enum key_change_e kchange = get_key_state(controller, row, col);
    dbg_uarttx_byte(keychange_char(kchange, row, controller, col));
    if (klt.special == TT_LEVEL_MOD) {
        if (klt.seq[0].type.type == KO_LEVEL_MOD || klt.seq[0].type.type == KO_LEVEL_MOD_X) {
        enum neo_levels_e level = klt.seq[0].level_mod.level;
        switch (level) {
        case LEVEL4: // XXX
            if (kchange == KC_PRESS) {
                if (level_mod[LEVEL4_MOUSE] == true) {
                    level_lock[LEVEL4_MOUSE] = true;
                }
                level_mod [level] = true;
            } else {
                level_mod[level] = !level_mod[level];
            }
            break;
        case LEVEL4_MOUSE: // XXX
            if (kchange == KC_PRESS) {
                if (level_mod[LEVEL4] == true) {
                    level_lock[LEVEL4] = true;
                }
                level_mod [level] = true;
            } else {
                level_mod[level] = !level_mod[level];
            }
            break;
        default:
            if (kchange == KC_PRESS) {
                if (level_mod[level] == true) {
                    level_lock[level] = !level_lock[level];
                    level_mod [level] = false;
                } else {
                    level_mod [level] = true;
                }
            } else {
                level_mod[level] = !level_mod[level];
            }
        }
        }
        if (klt.seq[0].type.type == KO_MODIFIER || klt.seq[0].type.type == KO_LEVEL_MOD_X) {
            uint8_t key;
            if (klt.seq[0].type.type == KO_MODIFIER) {
                key = klt.seq[0].single.key;
            } else {
                key = klt.seq[0].level_mod_X.key;
            }
            if (kchange == KC_PRESS) {
                modifiers |=  key;
            } else {
                modifiers &= ~key;
            }
            modifiers_changed = true;
        }
    } else {
        add_klt_charge(klt, kchange);
    }
}


void process_key_states() {
    // find changes

    if (memcmp(prev_key_state, key_state, sizeof(key_state))) {

        clear_klt_charge();

        uint8_t controller;
        for (controller = CTLR_MASTER; controller < CTLR_COUNT; ++controller) {
            uint8_t row;
            for (row = 0; row < ROW_COUNT; ++row) {
                uint8_t xor = prev_key_state[controller][row] ^ key_state[controller][row];
                if (xor > 0) {
                    uint8_t col;
                    for (col = 0; col < COL_COUNT; ++col) {
                        if ((xor & (1 << col)) > 0) {
                            // key state at [row,col] has changed
                            process_keychange(row, controller, col);
                        }
                    } // col loop
                } // xor > 0
            } // row loop
        } // controller loop

        enum neo_levels_e level = determine_current_level();
        process_klt_charge(level);

        if (modifiers_changed == true) {
            struct key_seq_step_s step = { .change = KC_PRESS, .key = 0, .modifier = modifiers};
            key_seq_queue_enqueue(&step);
            modifiers_changed = false;
        }

        memcpy(prev_key_state, key_state, sizeof(key_state));
    } // memcmp
}
