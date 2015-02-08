/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include "usb_keyboard.h"
#include "keymappings.h"

const union keyout_u keymap[KMM_COUNT][ROW_COUNT][2][COL_COUNT][LEVEL_COUNT] = {
    // KMM_DE
    {
        // DE ROW_NUM
        {
            // DE ROW_NUM left
            {
                {
                    /* lvl1 > 1 */ { .single = {KO_PLAIN  , KEY_1}},
                    /* lvl2 > ! */ { .single = {KO_SHIFT  , KEY_1}},
                    /* lvl3  -- */ { .type   = {KO_PHANTOM}       },
                    /* lvl4 > 1 */ { .single = {KO_PLAIN  , KEY_1}}, // xxx
                    /* lvlM >f1 */ { .single = {KO_PLAIN_X, KEY_F1}},
                },
                {
                    /* lvl1 > 2 */ { .single = {KO_PLAIN  , KEY_2}},
                    /* lvl2 > " */ { .single = {KO_SHIFT  , KEY_2}},
                    /* lvl3 > ² */ { .single = {KO_ALTGR  , KEY_2}},
                    /* lvl4 > 2 */ { .single = {KO_PLAIN  , KEY_2}}, // xxx
                    /* lvlM >f2 */ { .single = {KO_PLAIN_X, KEY_F2}},
                },
                {
                    /* lvl1 > 3 */ { .single = {KO_PLAIN  , KEY_3}},
                    /* lvl2 > § */ { .single = {KO_SHIFT  , KEY_3}},
                    /* lvl3 > ³ */ { .single = {KO_ALTGR  , KEY_3}},
                    /* lvl4 > 3 */ { .single = {KO_PLAIN  , KEY_3}}, // xxx
                    /* lvlM >f3 */ { .single = {KO_PLAIN_X, KEY_F3}},
                },
                {
                    /* lvl1 > 4 */ { .single = {KO_PLAIN  , KEY_4}},
                    /* lvl2 > $ */ { .single = {KO_SHIFT  , KEY_4}},
                    /* lvl3 > > */ { .single = {KO_SHIFT  , KEY_4}}, // FIXME
                    /* lvl4 > 4 */ { .single = {KO_PLAIN  , KEY_4}}, // xxx
                    /* lvlM >f4 */ { .single = {KO_PLAIN_X, KEY_F4}},
                },
                {
                    /* lvl1 > 5 */ { .single = {KO_PLAIN  , KEY_5}},
                    /* lvl2 > % */ { .single = {KO_SHIFT  , KEY_5}},
                    /* lvl3 > < */ { .single = {KO_SHIFT  , KEY_5}}, // FIXME
                    /* lvl4 > 5 */ { .single = {KO_PLAIN  , KEY_5}}, // xxx
                    /* lvlM >f5 */ { .single = {KO_PLAIN_X, KEY_F5}},
                },
                {
                    /* lvl1 > 6 */ { .single = {KO_PLAIN  , KEY_6}},
                    /* lvl2 > & */ { .single = {KO_SHIFT  , KEY_6}},
                    /* lvl3  -- */ { .type   = {KO_PHANTOM}       },
                    /* lvl4 > 6 */ { .single = {KO_PLAIN  , KEY_6}}, // xxx
                    /* lvlM >f6 */ { .single = {KO_PLAIN_X, KEY_F6}},
                },
                // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
            // DE ROW_NUM right
            {
                {
                    /* lvl1 > 7 */ { .single = {KO_PLAIN  , KEY_7}},
                    /* lvl2 > / */ { .single = {KO_SHIFT  , KEY_7}},
                    /* lvl3  -- */ { .type   = {KO_PHANTOM}       },
                    /* lvl4 > 7 */ { .single = {KO_PLAIN  , KEY_7}}, // xxx
                    /* lvlM >f7 */ { .single = {KO_PLAIN_X, KEY_F7}},
                },
                {
                    /* lvl1 > 8 */ { .single = {KO_PLAIN  , KEY_8}},
                    /* lvl2 > ( */ { .single = {KO_SHIFT  , KEY_8}},
                    /* lvl3 > , */ { .single = {KO_PLAIN  , KEY_COMMA}},
                    /* lvl4 >tab*/ { .single = {KO_PLAIN_X, KEY_TAB}},
                    /* lvlM >f8 */ { .single = {KO_PLAIN_X, KEY_F8}},
                },
                {
                    /* lvl1 > 9 */ { .single = {KO_PLAIN  , KEY_9}},
                    /* lvl2 > ) */ { .single = {KO_SHIFT  , KEY_9}},
                    /* lvl3 > ' */ { .single = {KO_SHIFT  , KEY_BACKSLASH}},
                    /* lvl4 > / */ { .single = {KO_PLAIN_X, KEYPAD_SLASH}},
                    /* lvlM >f9 */ { .single = {KO_PLAIN_X, KEY_F9}},
                },
                {
                    /* lvl1 > 0 */ { .single = {KO_PLAIN  , KEY_0}},
                    /* lvl2 > = */ { .single = {KO_SHIFT  , KEY_0}},
                    /* lvl3 > ' */ { .single = {KO_SHIFT  , KEY_BACKSLASH}},
                    /* lvl4 > * */ { .single = {KO_PLAIN_X, KEYPAD_ASTERIX}},
                    /* lvlM >f10*/ { .single = {KO_PLAIN_X, KEY_F10}},
                },
                {
                    /* lvl1 > - */ { .single = {KO_PLAIN  , KEY_SLASH}},
                    /* lvl2 > _ */ { .single = {KO_SHIFT  , KEY_SLASH}},
                    /* lvl3 > _ */ { .type   = {KO_PHANTOM}       },
                    /* lvl4 > - */ { .single = {KO_PLAIN_X, KEYPAD_MINUS}},
                    /* lvlM >f11*/ { .single = {KO_PLAIN_X, KEY_F11}},
                },
                {
                    /* lvl1 > ` */ { .single = {KO_SHIFT  , KEY_EQUAL}},
                    /* lvl2 > ` */ { .single = {KO_PLAIN  , KEY_EQUAL}},
                    /* lvl3 > ° */ { .single = {KO_SHIFT  , KEY_TILDE}},
                    /* lvl4 > ` */ { .single = {KO_SHIFT  , KEY_EQUAL}}, // xxx
                    /* lvlM >f12*/ { .single = {KO_PLAIN_X, KEY_F12}},
                },
                {
                    /* lvl1 > ^ */ { .single = {KO_PLAIN  , KEY_TILDE}},
                    /* lvl2 > ^ */ { .single = {KO_PLAIN  , KEY_TILDE}},
                    /* lvl3  -- */ { .type   = {KO_PHANTOM}       },
                    /* lvl4 > ^ */ { .single = {KO_PLAIN  , KEY_TILDE}}, // xxx
                    /* lvlM >pnt*/ { .single = {KO_PLAIN_X, KEY_PRINTSCREEN}},
                },
                    // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
        },
        // DE ROW_TOP
        {
            //  DE ROW_TOP left
            {
                {
                    /* lvl1 _M4 */ { .type   = {KO_MOD4_L}        },
                    /* lvl2 _M4 */ { .type   = {KO_MOD4_L}        },
                    /* lvl3 _M4 */ { .type   = {KO_MOD4_L}        },
                    /* lvl4 _M4 */ { .type   = {KO_MOD4_L}        },
                    /* lvlM _M4 */ { .type   = {KO_MOD4_L}        },
                },
                {
                    /* lvl1 > x */ { .single = {KO_PLAIN  , KEY_X}},
                    /* lvl2 > X */ { .single = {KO_SHIFT  , KEY_X}},
                    /* lvl3  -- */ { .type   = {KO_PHANTOM}       },
                    /* lvl4 >pup*/ { .single = {KO_PLAIN_X, KEY_PAGE_UP}},
                    /* lvlM >pup*/ { .single = {KO_PLAIN_X, KEY_PAGE_UP}},
                },
                {
                    /* lvl1 > v */ { .single = {KO_PLAIN  , KEY_V}},
                    /* lvl2 > V */ { .single = {KO_SHIFT  , KEY_V}},
                    /* lvl3 > _ */ { .single = {KO_SHIFT  , KEY_SLASH}},
                    /* lvl4 >bsp*/ { .single = {KO_PLAIN_X, KEY_BACKSPACE}},
                    /* lvlM >bsp*/ { .single = {KO_PLAIN_X, KEY_BACKSPACE}},
                },
                {
                    /* lvl1 > l */ { .single = {KO_PLAIN  , KEY_L}},
                    /* lvl2 > L */ { .single = {KO_SHIFT  , KEY_L}},
                    /* lvl3 > [ */ { .single = {KO_ALTGR  , KEY_8}},
                    /* lvl4 >aup*/ { .single = {KO_PLAIN_X, KEY_UP}},
                    /* lvlM >aup*/ { .single = {KO_PLAIN_X, KEY_UP}},
                },
                {
                    /* lvl1 > c */ { .single = {KO_PLAIN  , KEY_C}},
                    /* lvl2 > C */ { .single = {KO_SHIFT  , KEY_C}},
                    /* lvl3 > ] */ { .single = {KO_ALTGR  , KEY_9}},
                    /* lvl4 >del*/ { .single = {KO_PLAIN_X, KEY_DELETE}},
                    /* lvlM >del*/ { .single = {KO_PLAIN_X, KEY_DELETE}},
                },
                {
                    /* lvl1 > w */ { .single = {KO_PLAIN  , KEY_W}},
                    /* lvl2 > W */ { .single = {KO_SHIFT  , KEY_W}},
                    /* lvl3 > ^ */ { .compose= {KO_PLAIN , KEY_TILDE, KO_PLAIN , KEY_SPACE }},
                    /* lvl4 >pdn*/ { .single = {KO_PLAIN_X, KEY_PAGE_DOWN}},
                    /* lvlM >pdn*/ { .single = {KO_PLAIN_X, KEY_PAGE_DOWN}},
                },
                // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
            // DE ROW_TOP right
            {
                {
                    /* lvl1 > k */ { .single = {KO_PLAIN  , KEY_K}},
                    /* lvl2 > K */ { .single = {KO_SHIFT  , KEY_K}},
                    /* lvl3 > ! */ { .single = {KO_SHIFT  , KEY_1}},
                    /* lvl4 > k */ { .single = {KO_PLAIN  , KEY_K}}, // xxx
                    /* lvlM > k */ { .single = {KO_PLAIN  , KEY_K}}, // xxx
                },
                {
                    /* lvl1 > h */ { .single = {KO_PLAIN  , KEY_H}},
                    /* lvl2 > H */ { .single = {KO_SHIFT  , KEY_H}},
                    /* lvl3 > < */ { .single = {KO_SHIFT  , KEY_H}}, // FIXME
                    /* lvl4 > 7 */ { .single = {KO_PLAIN_X, KEYPAD_7}},
                    /* lvlM > 7 */ { .single = {KO_PLAIN_X, KEYPAD_7}}, // TODO: ctrl+c
                },
                {
                    /* lvl1 > g */ { .single = {KO_PLAIN  , KEY_G}},
                    /* lvl2 > G */ { .single = {KO_SHIFT  , KEY_G}},
                    /* lvl3 > > */ { .single = {KO_SHIFT  , KEY_G}}, // FIXME
                    /* lvl4 > 8 */ { .single = {KO_PLAIN_X, KEYPAD_8}},
                    /* lvlM > 8 */ { .single = {KO_PLAIN_X, KEYPAD_8}}, // TODO: ctrl+v
                },
                {
                    /* lvl1 > f */ { .single = {KO_PLAIN  , KEY_F}},
                    /* lvl2 > F */ { .single = {KO_SHIFT  , KEY_F}},
                    /* lvl3 > = */ { .single = {KO_SHIFT  , KEY_0}},
                    /* lvl4 > 9 */ { .single = {KO_PLAIN_X, KEYPAD_9}},
                    /* lvlM > 9 */ { .single = {KO_PLAIN_X, KEYPAD_9}}, // TODO: ctrl+x
                },
                {
                    /* lvl1 > q */ { .single = {KO_PLAIN  , KEY_Q}},
                    /* lvl2 > Q */ { .single = {KO_SHIFT  , KEY_Q}},
                    /* lvl3 > & */ { .single = {KO_SHIFT  , KEY_6}},
                    /* lvl4 > q */ { .single = {KO_PLAIN_X, KEYPAD_PLUS}},
                    /* lvlM > q */ { .single = {KO_PLAIN_X, KEYPAD_PLUS}},
                },
                {
                    /* lvl1 > ß */ { .single = {KO_PLAIN  , KEY_MINUS}},
                    /* lvl2 > ß */ { .single = {KO_PLAIN  , KEY_MINUS}},
                    /* lvl3  -- */ { .type   = {KO_PHANTOM}       },
                    /* lvl4 > ß */ { .single = {KO_PLAIN_X, KEYPAD_MINUS}},
                    /* lvlM > ß */ { .single = {KO_PLAIN_X, KEYPAD_MINUS}},
                },
                {
                    /* lvl1 > ' */ { .single = {KO_PLAIN  , KEY_EQUAL}},
                    /* lvl2 > ~ */ { .single = {KO_SHIFT  , KEY_TILDE}},
                    /* lvl3  -- */ { .type   = {KO_PHANTOM}       },
                    /* lvl4 > ' */ { .single = {KO_PLAIN  , KEY_EQUAL}}, // xxx
                    /* lvlM > ' */ { .single = {KO_PLAIN  , KEY_EQUAL}}, // xxx
                },
                // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
            // DE ROW_HOME
            {
                // DE ROW_HOME left
                {
                    /* lvl1 lM3 */ { .type   = {KO_MOD3_L}        },
                    /* lvl2 lM3 */ { .type   = {KO_MOD3_L}        },
                    /* lvl3 lM3 */ { .type   = {KO_MOD3_L}        },
                    /* lvl4 lM3 */ { .type   = {KO_MOD3_L}        },
                    /* lvlM lM3 */ { .type   = {KO_MOD3_L}        },
                },
                {
                    /* lvl1 > u */ { .single = {KO_PLAIN  , KEY_U}},
                    /* lvl2 > U */ { .single = {KO_SHIFT  , KEY_U}},
                    /* lvl3 > \ */ { .single = {KO_PLAIN  , KEY_BACKSLASH}},
                    /* lvl4 >hme*/ { .single = {KO_PLAIN_X, KEY_HOME}},
                    /* lvlM >hme*/ { .single = {KO_PLAIN_X, KEY_HOME}},
                },
                {
                    /* lvl1 > i */ { .single = {KO_PLAIN  , KEY_I}},
                    /* lvl2 > I */ { .single = {KO_SHIFT  , KEY_I}},
                    /* lvl3 > / */ { .single = {KO_PLAIN  , KEY_SLASH}},
                    /* lvl4 >alf*/ { .single = {KO_PLAIN_X, KEY_LEFT}},
                    /* lvlM >alf*/ { .single = {KO_PLAIN_X, KEY_LEFT}},
                },
                {
                    /* lvl1 > a */ { .single = {KO_PLAIN  , KEY_A}},
                    /* lvl2 > A */ { .single = {KO_SHIFT  , KEY_A}},
                    /* lvl3 > { */ { .single = {KO_ALTGR  , KEY_7}},
                    /* lvl4 >adn*/ { .single = {KO_PLAIN_X, KEY_DOWN}},
                    /* lvlM >adn*/ { .single = {KO_PLAIN_X, KEY_DOWN}},
                },
                {
                    /* lvl1 > e */ { .single = {KO_PLAIN  , KEY_E}},
                    /* lvl2 > E */ { .single = {KO_SHIFT  , KEY_E}},
                    /* lvl3 > } */ { .single = {KO_ALTGR  , KEY_0}},
                    /* lvl4 >art*/ { .single = {KO_PLAIN_X, KEY_RIGHT}},
                    /* lvlM >art*/ { .single = {KO_PLAIN_X, KEY_RIGHT}},
                },
                {
                    /* lvl1 > o */ { .single = {KO_PLAIN  , KEY_O}},
                    /* lvl2 > O */ { .single = {KO_SHIFT  , KEY_O}},
                    /* lvl3 > * */ { .single = {KO_SHIFT  , KEY_RIGHT_BRACE}},
                    /* lvl4 >end*/ { .single = {KO_PLAIN_X, KEY_END}},
                    /* lvlM >end*/ { .single = {KO_PLAIN_X, KEY_END}},
                },
                // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
            // DE ROW_HOME right
            {
                {
                    /* lvl1 > s */ { .single = {KO_PLAIN  , KEY_S}},
                    /* lvl2 > S */ { .single = {KO_SHIFT  , KEY_S}},
                    /* lvl3 > ? */ { .single = {KO_SHIFT  , KEY_MINUS}},
                    /* lvl4 > ? */ { .single = {KO_PLAIN_X, KEY_S}}, // xxx
                    /* lvlM > ? */ { .single = {KO_PLAIN_X, KEY_S}}, // todo: mouse btn5
                },
                {
                    /* lvl1 > n */ { .single = {KO_PLAIN  , KEY_N}},
                    /* lvl2 > N */ { .single = {KO_SHIFT  , KEY_N}},
                    /* lvl3 > ( */ { .single = {KO_SHIFT  , KEY_8}},
                    /* lvl4 > 4 */ { .single = {KO_PLAIN_X, KEYPAD_4}},
                    /* lvlM > 4 */ { .single = {KO_PLAIN_X, KEYPAD_4}}, // todo: mouse btn1
                },
                {
                    /* lvl1 > r */ { .single = {KO_PLAIN  , KEY_R}},
                    /* lvl2 > R */ { .single = {KO_SHIFT  , KEY_R}},
                    /* lvl3 > ) */ { .single = {KO_SHIFT  , KEY_9}},
                    /* lvl4 > 5 */ { .single = {KO_PLAIN_X, KEYPAD_5}},
                    /* lvlM > 5 */ { .single = {KO_PLAIN_X, KEYPAD_5}}, // todo: mouse btn2
                },
                {
                    /* lvl1 > t */ { .single = {KO_PLAIN  , KEY_T}},
                    /* lvl2 > T */ { .single = {KO_SHIFT  , KEY_T}},
                    /* lvl3 > - */ { .single = {KO_PLAIN  , KEY_SLASH}},
                    /* lvl4 > 6 */ { .single = {KO_PLAIN_X, KEYPAD_6}},
                    /* lvlM > 6 */ { .single = {KO_PLAIN_X, KEYPAD_6}}, // todo: mouse btn3
                },
                {
                    /* lvl1 > d */ { .single = {KO_PLAIN  , KEY_D}},
                    /* lvl2 > D */ { .single = {KO_SHIFT  , KEY_D}},
                    /* lvl3 > : */ { .single = {KO_SHIFT  , KEY_PERIOD}},
                    /* lvl4 > , */ { .single = {KO_PLAIN  , KEY_COMMA}},
                    /* lvlM > , */ { .single = {KO_PLAIN  , KEY_COMMA}}, // todo: mouse btn4
                },
                {
                    /* lvl1 > y */ { .single = {KO_PLAIN  , KEY_Z}},
                    /* lvl2 > Y */ { .single = {KO_SHIFT  , KEY_Z}},
                    /* lvl3 > @ */ { .single = {KO_ALTGR  , KEY_Q}},
                    /* lvl4 > . */ { .single = {KO_PLAIN  , KEY_PERIOD}},
                    /* lvlM > . */ { .single = {KO_PLAIN  , KEY_PERIOD}}, // todo: mouse btn6
                },
                {
                    /* lvl1 rM3 */ { .type   = {KO_MOD3_R        }},
                    /* lvl2 rM3 */ { .type   = {KO_MOD3_R        }},
                    /* lvl3 rM3 */ { .type   = {KO_MOD3_R        }},
                    /* lvl4 rM3 */ { .type   = {KO_MOD3_R        }},
                    /* lvlM rM3 */ { .type   = {KO_MOD3_R        }},
                },
                // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
        },
        // DE ROW_BTM
        {
            // DE ROW_BTM left
            {
                {
                    /* lvl1 lSH */ { .type   = {KO_MOD_SHIFT_L}   },
                    /* lvl2 lSH */ { .type   = {KO_MOD_SHIFT_L}   },
                    /* lvl3 lSH */ { .type   = {KO_MOD_SHIFT_L}   },
                    /* lvl4 lSH */ { .type   = {KO_MOD_SHIFT_L}   },
                    /* lvlM lSH */ { .type   = {KO_MOD_SHIFT_L}   },
                },
                {
                    /* lvl1 > ü */ { .single = {KO_PLAIN  , KEY_LEFT_BRACE}},
                    /* lvl2 > Ü */ { .single = {KO_SHIFT  , KEY_LEFT_BRACE}},
                    /* lvl3 > # */ { .single = {KO_PLAIN  , KEY_BACKSLASH}},
                    /* lvl4 >esc*/ { .single = {KO_PLAIN_X, KEY_ESC}},
                    /* lvlM >esc*/ { .single = {KO_PLAIN_X, KEY_ESC}},
                },
                {
                    /* lvl1 > ö */ { .single = {KO_PLAIN  , KEY_SEMICOLON}},
                    /* lvl2 > Ö */ { .single = {KO_SHIFT  , KEY_SEMICOLON}},
                    /* lvl3 > $ */ { .single = {KO_SHIFT  , KEY_4}},
                    /* lvl4 >tab*/ { .single = {KO_PLAIN_X, KEY_TAB}},
                    /* lvlM >tab*/ { .single = {KO_PLAIN_X, KEY_TAB}},
                },
                {
                    /* lvl1 > ä */ { .single = {KO_PLAIN  , KEY_QUOTE}},
                    /* lvl2 > Ä */ { .single = {KO_SHIFT  , KEY_QUOTE}},
                    /* lvl3 > | */ { .single = {KO_SHIFT  , KEY_QUOTE}}, // FIXME
                    /* lvl4 >ins*/ { .single = {KO_PLAIN_X, KEY_INSERT}},
                    /* lvlM >ins*/ { .single = {KO_PLAIN_X, KEY_INSERT}},
                },
                {
                    /* lvl1 > p */ { .single = {KO_PLAIN  , KEY_P}},
                    /* lvl2 > P */ { .single = {KO_SHIFT  , KEY_P}},
                    /* lvl3 > ~ */ { .single = {KO_ALTGR  , KEY_RIGHT_BRACE}},
                    /* lvl4 >ret*/ { .single = {KO_PLAIN_X, KEYPAD_ENTER}},
                    /* lvlM >ret*/ { .single = {KO_PLAIN_X, KEY_ENTER}},
                },
                {
                    /* lvl1 > z */ { .single = {KO_PLAIN  , KEY_Y}},
                    /* lvl2 > Z */ { .single = {KO_SHIFT  , KEY_Y}},
                    /* lvl3 > ` */ { .compose= {KO_SHIFT , KEY_EQUAL, KO_PLAIN, KEY_SPACE}},
                    /* lvl4 >udo*/ { .single = {KO_PLAIN_X, KEY_Y}}, // xxx
                    /* lvlM >udo*/ { .single = {KO_PLAIN_X, KEY_Y}}, // xxx
                },
                // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
            // DE ROW_BTM right
            {
                {
                    /* lvl1 > b */ { .single = {KO_PLAIN  , KEY_B}},
                    /* lvl2 > B */ { .single = {KO_SHIFT  , KEY_B}},
                    /* lvl3 > + */ { .single = {KO_PLAIN  , KEY_RIGHT_BRACE}},
                    /* lvl4 > : */ { .single = {KO_SHIFT  , KEY_PERIOD}},
                    /* lvlM > : */ { .single = {KO_SHIFT  , KEY_PERIOD}}, // todo: mouse btn5 double click
                },
                {
                    /* lvl1 > m */ { .single = {KO_PLAIN  , KEY_M}},
                    /* lvl2 > M */ { .single = {KO_SHIFT  , KEY_M}},
                    /* lvl3 > % */ { .single = {KO_SHIFT  , KEY_5}},
                    /* lvl4 > 1 */ { .single = {KO_PLAIN_X, KEYPAD_1}},
                    /* lvlM > 1 */ { .single = {KO_PLAIN_X, KEYPAD_1}}, // todo: mouse btn1 double click
                },
                {
                    /* lvl1 > , */ { .single = {KO_PLAIN  , KEY_COMMA}},
                    /* lvl2 > - */ { .single = {KO_PLAIN  , KEY_MINUS}},
                    /* lvl3 > " */ { .single = {KO_SHIFT  , KEY_2}},
                    /* lvl4 > 2 */ { .single = {KO_PLAIN_X, KEYPAD_2}},
                    /* lvlM > 2 */ { .single = {KO_PLAIN_X, KEYPAD_2}}, // todo: mouse btn2 double click
                },
                {
                    /* lvl1 > . */ { .single = {KO_PLAIN  , KEY_PERIOD}},
                    /* lvl2 > . */ { .single = {KO_PLAIN  , KEY_PERIOD}},
                    /* lvl3 > ' */ { .single = {KO_SHIFT  , KEY_BACKSLASH}},
                    /* lvl4 > 3 */ { .single = {KO_PLAIN_X, KEYPAD_3}},
                    /* lvlM > 3 */ { .single = {KO_PLAIN_X, KEYPAD_3}}, // todo: mouse btn3 double click
                },
                {
                    /* lvl1 > j */ { .single = {KO_PLAIN  , KEY_J}},
                    /* lvl2 > J */ { .single = {KO_SHIFT  , KEY_J}},
                    /* lvl3 > ; */ { .single = {KO_SHIFT  , KEY_COMMA}},
                    /* lvl4 > ; */ { .single = {KO_SHIFT  , KEY_COMMA}},
                    /* lvlM > ; */ { .single = {KO_SHIFT  , KEY_COMMA}}, // todo: mouse btn4 double click
                },
                {
                    /* lvl1 rSH */ { .type   = {KO_MOD_SHIFT_R   }},
                    /* lvl2 rSH */ { .type   = {KO_MOD_SHIFT_R   }},
                    /* lvl3 rSH */ { .type   = {KO_MOD_SHIFT_R   }},
                    /* lvl4 rSH */ { .type   = {KO_MOD_SHIFT_R   }},
                    /* lvlM rSH */ { .type   = {KO_MOD_SHIFT_R   }}, // todo: mouse btn6 double click
                },
                // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
        },
        // DE ROW_SPACE
        {
            // DE ROW_SPACE left
            {
                {
                    /* lvl1 ctrl*/ { .single = {KO_PLAIN  , KEY_LEFT_CTRL}},
                    /* lvl2 ctrl*/ { .single = {KO_SHIFT  , KEY_LEFT_CTRL}},
                    /* lvl3 ctrl*/ { .single = {KO_PLAIN  , KEY_LEFT_CTRL}},
                    /* lvl4 ctrl*/ { .single = {KO_PLAIN  , KEY_LEFT_CTRL}},
                    /* lvlM ctrl*/ { .single = {KO_PLAIN  , KEY_LEFT_CTRL}},
                },
                {
                    /* lvl1 win */ { .single = {KO_PLAIN  , KEY_LEFT_GUI}}, // XXX correct?
                    /* lvl2 win */ { .single = {KO_SHIFT  , KEY_LEFT_GUI}}, // XXX correct?
                    /* lvl3 win */ { .single = {KO_PLAIN  , KEY_LEFT_GUI}}, // XXX correct?
                    /* lvl4 win */ { .single = {KO_PLAIN  , KEY_LEFT_GUI}}, // XXX correct?
                    /* lvlM win */ { .single = {KO_PLAIN  , KEY_LEFT_GUI}}, // XXX correct?
                },
                {
                    /* lvl1 spce*/ { .single = {KO_PLAIN  , KEY_SPACE}},
                    /* lvl2 spce*/ { .single = {KO_SHIFT  , KEY_SPACE}},
                    /* lvl3 spce*/ { .single = {KO_PLAIN  , KEY_SPACE}},
                    /* lvl4 spce*/ { .single = {KO_PLAIN  , KEY_SPACE}},
                    /* lvlM spce*/ { .single = {KO_PLAIN  , KEY_SPACE}},
                },
                {
                    /* lvl1 alt */ { .single = {KO_PLAIN  , KEY_LEFT_ALT}},
                    /* lvl2 alt */ { .single = {KO_SHIFT  , KEY_LEFT_ALT}},
                    /* lvl3 alt */ { .single = {KO_PLAIN  , KEY_LEFT_ALT}},
                    /* lvl4 alt */ { .single = {KO_PLAIN  , KEY_LEFT_ALT}},
                    /* lvlM alt */ { .single = {KO_PLAIN  , KEY_LEFT_ALT}},
                },
                // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
            // DE ROW_SPACE right
            {
                {
                    /* lvl1 alt */ { .single = {KO_PLAIN  , KEY_RIGHT_ALT}},
                    /* lvl2 alt */ { .single = {KO_SHIFT  , KEY_RIGHT_ALT}},
                    /* lvl3 alt */ { .single = {KO_PLAIN  , KEY_RIGHT_ALT}},
                    /* lvl4 alt */ { .single = {KO_PLAIN  , KEY_RIGHT_ALT}},
                    /* lvlM alt */ { .single = {KO_PLAIN  , KEY_RIGHT_ALT}},
                },
                {
                    /* lvl1 M4M */ { .type   = {KO_MOD4_MOUSE}},
                    /* lvl2 M4M */ { .type   = {KO_MOD4_MOUSE}},
                    /* lvl3 M4M */ { .type   = {KO_MOD4_MOUSE}},
                    /* lvl4 M4M */ { .type   = {KO_MOD4_MOUSE}},
                    /* lvlM M4M */ { .type   = {KO_MOD4_MOUSE}},
                },
                {
                    /* lvl1 spce*/ { .single = {KO_PLAIN  , KEY_SPACE}},
                    /* lvl2 spce*/ { .single = {KO_SHIFT  , KEY_SPACE}},
                    /* lvl3 spce*/ { .single = {KO_PLAIN  , KEY_SPACE}},
                    /* lvl4 > 0 */ { .single = {KO_PLAIN_X, KEYPAD_0}},
                    /* lvlM > 0 */ { .single = {KO_PLAIN_X, KEYPAD_0}},
                },
                {
                    /* lvl1 win */ { .single = {KO_PLAIN  , KEY_RIGHT_GUI}}, // XXX correct?
                    /* lvl2 win */ { .single = {KO_SHIFT  , KEY_RIGHT_GUI}}, // XXX correct?
                    /* lvl3 win */ { .single = {KO_PLAIN  , KEY_RIGHT_GUI}}, // XXX correct?
                    /* lvl4 win */ { .single = {KO_PLAIN  , KEY_RIGHT_GUI}}, // XXX correct?
                    /* lvlM win */ { .single = {KO_PLAIN  , KEY_RIGHT_GUI}}, // XXX correct?
                },
                {
                    /* lvl1 menu*/ { .single = {KO_PLAIN  , KEY_GUI}}, // FIXME
                    /* lvl2 menu*/ { .single = {KO_SHIFT  , KEY_GUI}}, // FIXME
                    /* lvl3 menu*/ { .single = {KO_PLAIN  , KEY_GUI}}, // FIXME
                    /* lvl4 menu*/ { .single = {KO_PLAIN  , KEY_GUI}}, // FIXME
                    /* lvlM menu*/ { .single = {KO_PLAIN  , KEY_GUI}}, // FIXME
                },
                {
                    /* lvl1 ctrl*/ { .single = {KO_PLAIN  , KEY_RIGHT_CTRL}},
                    /* lvl2 ctrl*/ { .single = {KO_SHIFT  , KEY_RIGHT_CTRL}},
                    /* lvl3 ctrl*/ { .single = {KO_PLAIN  , KEY_RIGHT_CTRL}},
                    /* lvl4 ctrl*/ { .single = {KO_PLAIN  , KEY_RIGHT_CTRL}},
                    /* lvlM ctrl*/ { .single = {KO_PLAIN  , KEY_RIGHT_CTRL}},
                },
                // remaining will be initialzed with zeros (=> KO_PHANTOM)
            },
        },
    },
   // KMM_NEO
   // KMM_US
   // KMM_DE_APPLE
   // KMM_US_APPLE
};
