/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <string.h>

#include "getkeys.h"

#include "keyhandling.h"
#include "io.h"
#include "ctlrcomm.h"


enum neo_levels_e locked_level = LEVEL1;
enum uint8_t level_modifiers = 0x00;

struct keyevent_b {
    keystate_t event :1;
    uint8_t controller :1;
    uint8_t row :3;
    uint8_t col :3;
};


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

enum keystate_e get_keystate(uint8_t controller, enum row_e row, uint8_t col) {
    return ((key_states[controller][row] & (1 << col)) > 0) ? KS_PRESS : KS_RELEASE;
}

void set_keystate(uint8_t controller, enum row_e row, uint8_t col, enum keystate_e state) {
    if (state == KS_PRESS) {
        key_states[controller][row] |=  (1 << col);
    } else {
        key_states[controller][row] &= ~(1 << col);
    }
}


#define KEYEVENTS_CNT_MAX 8
struct keyevent_b keyevents[KEYEVENTS_CNT_MAX] /*= {{ 0 }}*/;
uint8_t keyevents_cnt = 0;


void update_own_key_states() {
    uint8_t row;
    for (row = 0; row < ROW_COUNT; ++row) {
        activate_row(row);
        key_states[CONTROLLER][row] = 0;
        uint8_t col;
        for (col = 0; col < COL_COUNT; ++col) {
            set_keystate(CONTROLLER, row, col, test_col(col));
        }
        deactivate_row(row);
    }
}


// key changes

#if 0
void add_keyevent(uint8_t controller, uint8_t row, uint8_t col, enum keyevent_e event) {
    if (keychange_cnt < CHANGED_KEYS_CNT_MAX) {
        changed_keys[keychange_cnt].event = event;
        changed_keys[keychange_cnt].controller = controller;
        changed_keys[keychange_cnt].row = row;
        changed_keys[keychange_cnt].col = col;
        ++keychange_cnt;
    } else {
        warning(W_TOO_MANY_KEYS);
    }
}

void clear_keyevents() {
    //memset(keyevents, 0, sizeof(keyevents));
    keyevents_cnt = 0;
}
#endif


void enqueue_keychange(const keyrecord_t *record, enum keyevent_e state) {
    if (keychange_cnt < CHANGED_KEYS_CNT_MAX) {
        keychange[keychange_cnt].record = record;
        keychange[keychange_cnt].state = state;
        ++keychange_cnt;
    } else {
        warning(W_TOO_MANY_KEYS);
    }
}

void clear_keychanges() {
    //memset(keyevents, 0, sizeof(keyevents));
    keychange_cnt = 0;
}



void process_keychange(uint8_t controller, uint8_t row, uint8_t col) {
    flash_led();
    dbg_uarttx_byte(keychange_char(kchange, row, controller, col));

    const keyrecord_t *keyrecord = get_keyrecord(controller, row, col);
    enum keystate_e keystate = get_keystate(controller, row, col);
    
    switch (keyrecord->type) {
    case KT_LEVELMOD:
    case KT_IGNORE_LEVEL:
        keyrecord->kf[0](keystate);
        break;
    case KT_DUMB:
        // do nothing
        break;
    default:
#if 0
        add_keyevent(controller, row, col, keystate);
#endif
        enqueue_keychange(keyrecord, keystate);
    }
}

void process_queued_keychange(const keychange_t *change) {
    const keyrecord_t *record = change->record;
    enum neo_levels_e level;
    
    switch (record->type) {
    case KT_LEVELMOD:
    case KT_IGNORE_LEVEL:
        // FIXME: log PROGRAMMING ERROR
        break;
    case IGNORE_SHIFTLOCK:
        level = get_level_il2l();
    default:
        level = get_level();
    }
    record->kf[level](change->state);
}

void process_keystates() {
    // find changes

    if (memcmp(prev_key_states, key_states, sizeof(key_states))) {

        clear_keyevents();

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

        if (modifiers_changed == true) {
            struct key_seq_step_s step = { .change = KC_PRESS, .key = 0, .modifier = modifiers};
            key_seq_queue_enqueue(&step);
            modifiers_changed = false;
        }

        memcpy(prev_key_states, key_states, sizeof(key_states));
    } // memcmp
}
