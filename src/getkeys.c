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
#include "keystates.h"
#include "io.h"
#include "ctlrcomm.h"

// keep track of the currently active keys
#define ACTIVE_KEYS_LIST_LENGTH 8
symfunc_t active_keys_list[ACTIVE_KEYS_LIST_LENGTH] /*= {{0}}*/;
size_t active_keys_count = 0;

void active_keys_list_add(symfunc_t keyfunc) {
    if (active_keys_count < ACTIVE_KEYS_LIST_LENGTH) {
        active_keys_list[active_keys_count] = keyfunc;
        ++active_keys_count;
    } else {
        inform(IL_WARN, SC_WARN_TOO_MANY_KEYS);        
    }
}

/**
 * If keyfunc is in list, remove it from there.
 * @return true if keyfunc was found in list, false otherwise.
 */
bool active_keys_list_remove(symfunc_t keyfunc) {
    for (size_t idx = 0; idx < active_keys_count; ++idx) {
        if (active_keys_list[idx] == keyfunc) {
            memmove(&active_keys_list[idx],
                    &active_keys_list[idx+1],
                    (active_keys_count-(idx+1))*sizeof(active_keys_list[0])
                    );
            --active_keys_count;
            return true;
        }
    }
    return false;
}

void active_keys_list_clear() {
    active_keys_count = 0;
}

void release_all_active_keys() {
    for (size_t idx = 0; idx < active_keys_count; ++idx) {
        active_keys_list[idx](target_layout, KS_RELEASE);
    }
    active_keys_list_clear();
}




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


//

enum key_role_e {
    KR_REGULAR,
    KR_LEVELMOD,
    KR_COUNT
};

#define CHANGE_CNT_MAX 8

const keyrecord_t *keychange[KR_COUNT][2][CHANGE_CNT_MAX] /*= {{ 0 }}*/;
uint8_t keychange_cnt[KR_COUNT][2] = {{ 0, }, };

#if 0
static inline void inform_keystates() {
    if (info_uart(IL_DBG)) {
        inform(IL_DBG, SC_DBG_KEYSTATES);
        uint8_t ctlr;
#if 0
        for (ctlr = 0; ctlr < CTLR_COUNT; ++ctlr) {
            info_add(ctlr);
#else
            ctlr = CONTROLLER;   
#endif
            uint8_t row;
            for (row = 0; row < ROW_COUNT; ++row) {
                info_add(key_states[ctlr][row]);
            }
#if 0
        }
#endif
    }
}
#endif

void update_own_key_states() {
  io_read_switches();
  //inform_keystates();
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

#if 0 // XXX
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
#endif

void process_keychange(uint8_t controller, uint8_t row, uint8_t col) {
    const keyrecord_t *keyrecord = get_keyrecord(controller, row, col);
    keystate_t keystate = get_keystate(controller, row, col);
    
    flash_led();
    inform_kchange(keystate, controller, row, col);

    switch (keyrecord->type) {
    case KT_LEVELMOD:
        enqueue_keychange(KR_LEVELMOD, keyrecord, keystate);
        release_all_active_keys();
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
        if (change == KS_PRESS) {
            active_keys_list_add(record->kf[level]);
        } else {
            active_keys_list_remove(record->kf[level]);
        }
        record->kf[level](target_layout, change);
    } else if (level == LEVEL4_MOUSE && record->kf[LEVEL4] != NULL) {
        // fallback to LEVEL4 if no kf specified for LEVEL4_MOUSE
        if (change == KS_PRESS) {
            active_keys_list_add(record->kf[LEVEL4]);
        } else {
            active_keys_list_remove(record->kf[LEVEL4]);
        }
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

  if (keystates_changed()) {

    clear_keychanges();

    uint8_t element;
    for (element = 0; element < ELEMENT_COUNT_MAX; ++element) {
      uint8_t row;
      for (row = 0; row < ROW_COUNT; ++row) {
	uint8_t row_changes = keystate_row_changes(element, row);
	if (row_changes > 0) {
	  uint8_t col;
	  for (col = 0; col < COL_COUNT; ++col) {
	    if (keystate_changed_col(col, row_changes)) {
	      // key state at [row,col] has changed
	      process_keychange(element, row, col);
	    }
	  } // col loop
	} // row_changes > 0
      } // row loop
    } // element loop

    process_change_queue();

    keystate_buffer();
  } // keystates_changed
}
