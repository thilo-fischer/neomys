/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <string.h>

#include "getkeys.h"

#include "io.h"
#include "ctlrcomm.h"


typedef enum {
    KT_PLAIN,
    KT_LEVELMOD,
    KT_IGNORE_SHIFTLOCK,
    KT_IGNORE_LEVEL,
    KT_DUMB,
} keytype_t;

typedef void (*keyfunc_t)();

typedef struct {
    keytype_t type;
    keyfunc_t kf[LEVEL_COUNT];
} keyrecord_t;

keyrecord_t keymap[ROW_COUNT][2][COL_COUNT] = {
    // ROW_NUM
    {
        //ROW_NUM left
        {
            // in contrast to neo layout, the key for the circumfex accent has been moved from the top left to the top right corner of the keyboard
            // 1
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_1, kf_degree, kf_superscript1, },
            },
            // 2
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_2, kf_sectionsign, kf_superscript2, },
            },
            // 3
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_3, NULL, kf_superscript3, },
            },
            // 4
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_4, kf_guillemet_dbl_gt, kf_guillemet_sgl_gt, },
            },
            // 5
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_5, kf_guillemet_dbl_lt, kf_guillemet_sgl_lt, },
            },
            // 6
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_6, kf_dollar, kf_cent_currency, kf_pound_currency, },
            },
        }, // controller (left/right side)
        //ROW_NUM right
        {
            // 7
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_7, kf_euro_currency, kf_yen_currency, kf_currency_sign, },
            },
            // 8
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_8, kf_low9quote_dbl, kf_low9quote_sgl, kf_tab, },
            },
            // 9
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_9, kf_6quote_dbl, kf_6quote_sgl, kf_numpad_slash, },
            },
            // 0
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_0, kf_9quote_dbl, kf_9quote_sgl, kf_numpad_asterisk, },
            },
            // -
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dash, kf_mdash, NULL, kf_numpad_dash},
            },
            // ò
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_grave, kf_dead_cedilla, kf_dead_ring, kf_dead_umlaut, },
            },
            // ô
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_circumfex, kf_dead_caron, NULL, kf_dead_dot, },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_TOP
    {
        //ROW_TOP left
        {
            // in contrast to neo layout, the left level4 modifier key has been moved from right of the left level2 mod key to ontop of the level3 mod ked
            // level4 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level4mod_left },
            },
            // X
            {
                .type = KT_PLAIN,
                .kf = { kf_x, kf_X, kf_ellipsis, kf_page_up, },
            },
            // V
            {
                .type = KT_PLAIN,
                .kf = { kf_v, kf_V, kf_underscore, kf_backspace, },
            },
            // L
            {
                .type = KT_PLAIN,
                .kf = { kf_l, kf_L, kf_bracket_left, kf_up, },
            },
            // C
            {
                .type = KT_PLAIN,
                .kf = { kf_c, kf_C, kf_bracket_right, kf_delete, },
            },
            // W
            {
                .type = KT_PLAIN,
                .kf = { kf_w, kf_W, kf_caret, kf_page_down, },
            },
        }, // controller (left/right side)
        //ROW_TOP right
        {
            // K
            {
                .type = KT_PLAIN,
                .kf = { kf_k, kf_K, kf_exclamation_mark, kf_inverted_exclamation_mark, },
            },
            // H
            {
                .type = KT_PLAIN,
                .kf = { kf_h, kf_H, kf_chevron_left, kf_numpad_7, },
            },
            // G
            {
                .type = KT_PLAIN,
                .kf = { kf_g, kf_G, kf_chevron_right, kf_numpad_8, },
            },
            // F
            {
                .type = KT_PLAIN,
                .kf = { kf_f, kf_F, kf_equals, kf_numpad_9, },
            },
            // Q
            {
                .type = KT_PLAIN,
                .kf = { kf_q, kf_Q, kf_ampersand, kf_numpad_plus, },
            },
            // ß
            {
                .type = KT_PLAIN,
                .kf = { kf_eszett, kf_ESZETT, kf_long_s, kf_minus, },
            },
            // ó
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_acute, kf_dead_perispomene, kf_dead_bar, kf_dead_double_acute},
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_HOME
    {
        //ROW_HOME left
        {
            // level3 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level3mod_left },
            },
            // U
            {
                .type = KT_PLAIN,
                .kf = { kf_u, kf_U, kf_backslash, kf_home, },
            },
            // I
            {
                .type = KT_PLAIN,
                .kf = { kf_i, kf_I, kf_slash, kf_left, },
            },
            // A
            {
                .type = KT_PLAIN,
                .kf = { kf_a, kf_A, kf_brace_left, kf_down, },
            },
            // E
            {
                .type = KT_PLAIN,
                .kf = { kf_e, kf_E, kf_brace_right, kf_right, },
            },
            // O
            {
                .type = KT_PLAIN,
                .kf = { kf_o, kf_O, kf_asterisk, kf_end, },
            },
        }, // controller (left/right side)
        //ROW_HOME right
        {
            // S
            {
                .type = KT_PLAIN,
                .kf = { kf_s, kf_S, kf_question_mark, kf_inverted_question_mark, },
            },
            // N
            {
                .type = KT_PLAIN,
                .kf = { kf_n, kf_N, kf_parentheses_left, kf_numpad_4, },
            },
            // R
            {
                .type = KT_PLAIN,
                .kf = { kf_r, kf_R, kf_parentheses_right, kf_numpad_5, },
            },
            // T
            {
                .type = KT_PLAIN,
                .kf = { kf_t, kf_T, kf_dash, kf_numpad_6, },
            },
            // D
            {
                .type = KT_PLAIN,
                .kf = { kf_d, kf_D, kf_colon, kf_numpad_comma, },
            },
            // Y
            {
                .type = KT_PLAIN,
                .kf = { kf_y, kf_Y, kf_at, kf_numpad_dot, },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_BTM
    {
        //ROW_BTM left
        {
            // level2 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level2mod_left },
            },
            // Ü
            {
                .type = KT_PLAIN,
                .kf = { kf_uuml, kf_UUML, kf_hash, kf_escape, },
            },
            // Ö
            {
                .type = KT_PLAIN,
                .kf = { kf_ouml, kf_OUML, kf_dollar, kf_tab, },
            },
            // Ä
            {
                .type = KT_PLAIN,
                .kf = { kf_auml, kf_AUML, kf_pipe, kf_insert, },
            },
            // P
            {
                .type = KT_PLAIN,
                .kf = { kf_p, kf_P, kf_tilde, kf_return, },
            },
            // Z
            {
                .type = KT_PLAIN,
                .kf = { kf_z, kf_Z, kf_backtick, kf_undo, },
            },
        }, // controller (left/right side)
        //ROW_BTM right
        {
            // B
            {
                .type = KT_PLAIN,
                .kf = { kf_b, kf_B, kf_plus, kf_colon, },
            },
            // M
            {
                .type = KT_PLAIN,
                .kf = { kf_m, kf_M, kf_percent, kf_numpad_1, },
            },
            // ,
            {
                .type = KT_PLAIN,
                .kf = { kf_comma, kf_ndash, kf_straight_dbl_quote, kf_numpad_2, },
            },
            // .
            {
                .type = KT_PLAIN,
                .kf = { kf_dot, kf_bullet, kf_apostrophe, kf_numpad_3, },
            },
            // J
            {
                .type = KT_PLAIN,
                .kf = { kf_j, kf_J, kf_semicolon, kf_semicolon, },
            },
            // level2 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level2mod_right },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_SPACE
    {
        //ROW_SPACE left
        {
            // left Ctrl
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_ctrl_left },
            },
            // left GUI
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_gui_left },
            },
            // unused
            {
                .type = KT_DUMB,
                .kf = { NULL },
            },
            // unused
            {
                .type = KT_DUMB,
                .kf = { NULL },
            },
            // space
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_space },
            },
            // left Alt
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_alt_left },
            },
        }, // controller (left/right side)
        //ROW_SPACE right
        {
            // left Alt
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_alt_left },
            },
            // level4 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level4mod_right },
            },
            // space, numpad-zero
            {
                .type = KT_PLAIN,
                .kf = { kf_space, kf_space, kf_space, kf_numpad_zero, },
            },
            // unused
            {
                .type = KT_DUMB,
                .kf = { NULL },
            },
            // left GUI
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_gui_left },
            },
            // left Ctrl
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_ctrl_left },
            },
        }, // controller (left/right side)
    }, // row
};



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
