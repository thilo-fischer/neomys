/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Read key states from hardware, detect key state changes, determine current level to apply to the key state changes of regular (i.e. non-modifier etc.) keys, invoke function associated with pressed keys at current level (from keytranslation.c).
 * @todo To much distinct functionality in this one file. Split it to several files with more specific purposes.
 */

#include <string.h>

#include "getkeys.h"

#include "keyhandling.h"
#include "keytranslation.h"
#include "io.h"
#include "ctlrcomm.h"


enum neo_levels_e locked_level = LEVEL1;
uint8_t level_modifiers = 0x00;

enum neo_levels_e get_level_from_modifiers(uint8_t mods) {
    
    switch (mods) {
    case 0x00:
    case (LM2_L | LM2_R):
    case (LM3_L | LM3_R):
    case (LM4_L | LM4_R):
    case (LM2_L | LM2_R | LM3_L | LM3_R):
    case (LM3_L | LM3_R | LM4_L | LM4_R):
    case (LM2_L | LM2_R | LM3_L | LM3_R | LM4_L | LM4_R):
        return LEVEL1;
    case LM2_L:
    case LM2_R:
    case (LM2_L | LM3_L | LM3_R | LM4_L | LM4_R):
    case (LM2_R | LM3_L | LM3_R | LM4_L | LM4_R):
        return LEVEL2;
    case LM3_L:
    case LM3_R:
        return LEVEL3;
    case (LM2_L | LM3_L):
    case (LM2_L | LM3_R):
    case (LM2_R | LM3_L):
    case (LM2_R | LM3_R):
        return LEVEL5;
    case (LM3_L | LM4_L):
    case (LM3_L | LM4_R):
    case (LM3_R | LM4_L):
    case (LM3_R | LM4_R):
        return LEVEL6;
    }

    // ignore LM2_x (because it shall be possible to combine shift (LM2_x) and keys from LEVEL4/LEVEL4_MOUSE [e.g. arrow keys, return, F1, mouse clicks])
    switch (mods & ~(LM2_L|LM2_R)) {    
    case LM4_L:
        return LEVEL4;
    case LM4_R:
        return LEVEL4_MOUSE;
    }

    // fallback behaviour for weired modifier key press combinations (like 3 or 4 L/R modifiers at it time)
    if (mods & LM4_R)
        return LEVEL4_MOUSE;
    if (mods & LM4_L)
        return LEVEL4;
    if (mods & LM2_L || mods & LM2_R)
        return LEVEL2;
    if (mods & LM3_L || mods & LM3_R)
        return LEVEL3;

    return LEVEL1;

}


enum neo_levels_e get_level() {
    enum neo_levels_e pressed_level = get_level_from_modifiers(level_modifiers);
    if (pressed_level == LEVEL1)
        return locked_level;
    if (locked_level == pressed_level)
        return LEVEL1;
    return pressed_level;
}

// ignore level2 lock
enum neo_levels_e get_level_il2l() {
    if (locked_level == LEVEL2)
        return get_level_from_modifiers(level_modifiers);
    return get_level();
}



// key states
// Transmit states of all keys from slave to master. This is the simplest, most deterministic and probably most fail-safe approach (compared to sending only pressed keys or key state changes).

uint8_t key_states[2][ROW_COUNT] = {{0}, {0}};
uint8_t prev_key_states[2][ROW_COUNT] = {{0}, {0}};

keystate_t get_keystate(uint8_t controller, enum row_e row, uint8_t col) {
    return ((key_states[controller][row] & (1 << col)) > 0) ? KS_PRESS : KS_RELEASE;
}

void set_keystate(uint8_t controller, enum row_e row, uint8_t col, keystate_t state) {
    if (state == KS_PRESS) {
        key_states[controller][row] |=  (1 << col);
    } else {
        key_states[controller][row] &= ~(1 << col);
    }
}

enum key_role_e {
    KR_REGULAR,
    KR_LEVELMOD,
    KR_COUNT
};

#define CHANGE_CNT_MAX 8

const keyrecord_t *keychange[KR_COUNT][2][CHANGE_CNT_MAX] /*= {{ 0 }}*/;
uint8_t keychange_cnt[KR_COUNT][2] = {{ 0, }, };

static inline void inform_keystates() {
    if (info_uart(IL_DBG)) {
        inform(IL_DBG, SC_DBG_KEYSTATES);
        uint8_t row;
        for (row = 0; row < ROW_COUNT; ++row) {
            info_add(key_states[CONTROLLER][row]);
        }
    }
}

void update_own_key_states() {
    uint8_t row;
    for (row = 0; row < ROW_COUNT; ++row) {
        activate_row(row);
        // set all switches of that row to KS_RELEASE (KS_RELEASE == 0x00)
        key_states[CONTROLLER][row] = 0x00;
        uint8_t col;
        for (col = 0; col < COL_COUNT; ++col) {
            if (test_col(col) == 1)
                set_keystate(CONTROLLER, row, col, KS_PRESS);
        }
        deactivate_row(row);
    }
    inform_keystates();
}


// key changes

void enqueue_keychange(enum key_role_e type, const keyrecord_t *record, keystate_t state) {
    uint8_t cnt = keychange_cnt[type][state];
    if (cnt < CHANGE_CNT_MAX) {
        keychange[type][state][cnt] = record;
        ++keychange_cnt[type][state];
    } else {
        inform(IL_WARN, SC_WARN_TOO_MANY_KEYS);
    }
}

static inline void clear_keychanges() {
    for (enum key_role_e t = KR_REGULAR; t < KR_COUNT; ++t) {
        keychange_cnt[t][0] = 0;
        keychange_cnt[t][1] = 0;
    } // fixme: memset
}

struct kchange_info_byte {
    keystate_t keystate : 1;
    uint8_t controller  : 1;
    uint8_t row         : 3;
    uint8_t col         : 3;
};

static inline void inform_kchange(keystate_t keystate, uint8_t controller, uint8_t row, uint8_t col) {
    if (info_uart(IL_INFO)) {
        struct kchange_info_byte chbyte = {
            .keystate = keystate,
            .controller = controller,
            .row = row,
            .col = col,
        };
        inform(IL_INFO, SC_INFO_KEYCHANGE);
        info_add(*(uint8_t*)&chbyte);
    }
}

void process_keychange(uint8_t controller, uint8_t row, uint8_t col) {
    const keyrecord_t *keyrecord = get_keyrecord(controller, row, col);
    keystate_t keystate = get_keystate(controller, row, col);
    
    flash_led();
    inform_kchange(keystate, controller, row, col);

    switch (keyrecord->type) {
    case KT_LEVELMOD:
        enqueue_keychange(KR_LEVELMOD, keyrecord, keystate);
        break;      
    case KT_DUMB:
        // do nothing
        break;
    default:
        enqueue_keychange(KR_REGULAR, keyrecord, keystate);
    }
}

extern keyrecord_t keymap[ROW_COUNT][2][COL_COUNT]; // FIXME only for debugging output

void process_queued_keychange(const keyrecord_t *record, keystate_t change) {
    enum neo_levels_e level;
    
    switch (record->type) {
    case KT_LEVELMOD:
    case KT_IGNORE_LEVEL:
        if (record->kf[0] != NULL) {
            record->kf[0](target_layout, change);
        } else {
            // Does not make sense to have this pointer set to NULL, should be KT_DUMB instead of KT_LEVELMOD/KT_IGNORE_LEVEL then.
            inform_programming_error();
        }
        return;
    case KT_IGNORE_SHIFTLOCK:
        level = get_level_il2l();
        break;
    default:
        level = get_level();
    }
    
    if (record->kf[level] != NULL) {
        record->kf[level](target_layout, change);
    } else if (level == LEVEL4_MOUSE && record->kf[LEVEL4] != NULL) {
        // fallback to LEVEL4 if no kf specified for LEVEL4_MOUSE
        record->kf[LEVEL4](target_layout, change);
    } else {
        inform(IL_WARN, SC_WARN_KEY_NOT_YET_IMPLMTD);
    }
}

void process_change_queue_section(enum key_role_e type, keystate_t change) {
    for (uint8_t i = 0; i < keychange_cnt[type][change]; ++i) {
        process_queued_keychange(keychange[type][change][i], change);
    }
}

// TODO: handle situation where modifier key is being released while regular key remains pressed

void process_change_queue() {
    // first, process all regular key releases
    process_change_queue_section(KR_REGULAR, KS_RELEASE);
    // second, process all level modifier key presses and releases 
    process_change_queue_section(KR_LEVELMOD, KS_RELEASE);
    process_change_queue_section(KR_LEVELMOD, KS_PRESS);
    // last, process all regular key presses
    process_change_queue_section(KR_REGULAR, KS_PRESS);
}

void process_keystates() {
    // find changes

    if (memcmp(prev_key_states, key_states, sizeof(key_states))) {

        clear_keychanges();

        uint8_t controller;
        for (controller = CTLR_MASTER; controller < CTLR_COUNT; ++controller) {
            uint8_t row;
            for (row = 0; row < ROW_COUNT; ++row) {
                uint8_t xor = prev_key_states[controller][row] ^ key_states[controller][row];
                if (xor > 0) {
                    uint8_t col;
                    for (col = 0; col < COL_COUNT; ++col) {
                        if ((xor & (1 << col)) > 0) {
                            // key state at [row,col] has changed
                            process_keychange(controller, row, col);
                        }
                    } // col loop
                } // xor > 0
            } // row loop
        } // controller loop

        process_change_queue();

        memcpy(prev_key_states, key_states, sizeof(key_states));
    } // memcmp
}
