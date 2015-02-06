/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include "usb_keyboard.h"
#include "keymappings.h"

const union keymapping_u keymapping[KB_COUNT][LEVEL_COUNT][ROW_COUNT][2][COL_COUNT] = {
    // KB_DE
    {
        // DE LEVEL1
        {
            // DE LEVEL1 ROW_NUM
            {
                // left
                {
                    /* 0 > 1 */ { .single = {KMT_PLAIN  , KEY_1}},
                    /* 1 > 2 */ { .single = {KMT_PLAIN  , KEY_2}},
                    /* 2 > 3 */ { .single = {KMT_PLAIN  , KEY_3}},
                    /* 3 > 4 */ { .single = {KMT_PLAIN  , KEY_4}},
                    /* 4 > 5 */ { .single = {KMT_PLAIN  , KEY_5}},
                    /* 5 > 6 */ { .single = {KMT_PLAIN  , KEY_6}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > 7 */ { .single = {KMT_PLAIN  , KEY_7}},
                    /* 1 > 8 */ { .single = {KMT_PLAIN  , KEY_8}},
                    /* 2 > 9 */ { .single = {KMT_PLAIN  , KEY_9}},
                    /* 3 > 0 */ { .single = {KMT_PLAIN  , KEY_0}},
                    /* 4 > - */ { .single = {KMT_PLAIN  , KEY_SLASH}},
                    /* 5 > ` */ { .single = {KMT_SHIFT  , KEY_EQUAL}},
                    /* 6 > ^ */ { .single = {KMT_PLAIN  , KEY_TILDE}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL1 ROW_TOP
            {
                // left
                {
                    /* 0 _M4 */ { .type   = {KMT_MOD4_L}        },
                    /* 1 > x */ { .single = {KMT_PLAIN  , KEY_X}},
                    /* 2 > v */ { .single = {KMT_PLAIN  , KEY_V}},
                    /* 3 > l */ { .single = {KMT_PLAIN  , KEY_L}},
                    /* 4 > c */ { .single = {KMT_PLAIN  , KEY_C}},
                    /* 5 > w */ { .single = {KMT_PLAIN  , KEY_W}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > k */ { .single = {KMT_PLAIN  , KEY_K}},
                    /* 1 > h */ { .single = {KMT_PLAIN  , KEY_H}},
                    /* 2 > g */ { .single = {KMT_PLAIN  , KEY_G}},
                    /* 3 > f */ { .single = {KMT_PLAIN  , KEY_F}},
                    /* 4 > q */ { .single = {KMT_PLAIN  , KEY_Q}},
                    /* 5 > ß */ { .single = {KMT_PLAIN  , KEY_MINUS}},
                    /* 6 > ' */ { .single = {KMT_PLAIN  , KEY_EQUAL}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL1 ROW_HOME
            {
                // left
                {
                    /* 0 lM3 */ { .type   = {KMT_MOD3_L}        },
                    /* 1 > u */ { .single = {KMT_PLAIN  , KEY_U}},
                    /* 2 > i */ { .single = {KMT_PLAIN  , KEY_I}},
                    /* 3 > a */ { .single = {KMT_PLAIN  , KEY_A}},
                    /* 4 > e */ { .single = {KMT_PLAIN  , KEY_E}},
                    /* 5 > o */ { .single = {KMT_PLAIN  , KEY_O}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > s */ { .single = {KMT_PLAIN  , KEY_S}},
                    /* 1 > n */ { .single = {KMT_PLAIN  , KEY_N}},
                    /* 2 > r */ { .single = {KMT_PLAIN  , KEY_R}},
                    /* 3 > t */ { .single = {KMT_PLAIN  , KEY_T}},
                    /* 4 > d */ { .single = {KMT_PLAIN  , KEY_D}},
                    /* 5 > y */ { .single = {KMT_PLAIN  , KEY_Z}},
                    /* 6 rM3 */ { .type   = {KMT_MOD3_R        }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL1 ROW_BTM
            {
                // left
                {
                    /* 0 lSH */ { .type   = {KMT_MOD_SHIFT_L}   },
                    /* 1 > ü */ { .single = {KMT_PLAIN  , KEY_LEFT_BRACE}},
                    /* 2 > ö */ { .single = {KMT_PLAIN  , KEY_SEMICOLON}},
                    /* 3 > ä */ { .single = {KMT_PLAIN  , KEY_QUOTE}},
                    /* 4 > p */ { .single = {KMT_PLAIN  , KEY_P}},
                    /* 5 > z */ { .single = {KMT_PLAIN  , KEY_Y}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > b */ { .single = {KMT_PLAIN  , KEY_B}},
                    /* 1 > m */ { .single = {KMT_PLAIN  , KEY_M}},
                    /* 2 > , */ { .single = {KMT_PLAIN  , KEY_COMMA}},
                    /* 3 > . */ { .single = {KMT_PLAIN  , KEY_PERIOD}},
                    /* 4 > j */ { .single = {KMT_PLAIN  , KEY_J}},
                    /* 5 rSH */ { .type   = {KMT_MOD_SHIFT_R   }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL1 ROW_SPACE
            {
                // left
                {
                    /* 0 ctrl*/ { .single = {KMT_PLAIN  , KEY_LEFT_CTRL}},
                    /* 1 win */ { .single = {KMT_PLAIN  , KEY_LEFT_GUI}}, // XXX correct?
                    /* 2 spce*/ { .single = {KMT_PLAIN  , KEY_SPACE}},
                    /* 3 alt */ { .single = {KMT_PLAIN  , KEY_LEFT_ALT}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 alt */ { .single = {KMT_PLAIN  , KEY_RIGHT_ALT}},
                    /* 1 M4M */ { .type   = {KMT_MOD4_MOUSE}},
                    /* 2 spce*/ { .single = {KMT_PLAIN  , KEY_SPACE}},
                    /* 3 win */ { .single = {KMT_PLAIN  , KEY_RIGHT_GUI}}, // XXX correct?
                    /* 4 menu*/ { .single = {KMT_PLAIN  , KEY_GUI}}, // FIXME
                    /* 5 ctrl*/ { .single = {KMT_PLAIN  , KEY_RIGHT_CTRL}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
        },
        // DE LEVEL2
        {
            // DE LEVEL2 ROW_NUM
            {
                // left
                {
                    /* 0 > ! */ { .single = {KMT_SHIFT  , KEY_1}},
                    /* 1 > " */ { .single = {KMT_SHIFT  , KEY_2}},
                    /* 2 > § */ { .single = {KMT_SHIFT  , KEY_3}},
                    /* 3 > $ */ { .single = {KMT_SHIFT  , KEY_4}},
                    /* 4 > % */ { .single = {KMT_SHIFT  , KEY_5}},
                    /* 5 > & */ { .single = {KMT_SHIFT  , KEY_6}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > / */ { .single = {KMT_SHIFT  , KEY_7}},
                    /* 1 > ( */ { .single = {KMT_SHIFT  , KEY_8}},
                    /* 2 > ) */ { .single = {KMT_SHIFT  , KEY_9}},
                    /* 3 > = */ { .single = {KMT_SHIFT  , KEY_0}},
                    /* 4 > _ */ { .single = {KMT_SHIFT  , KEY_SLASH}},
                    /* 5 > ` */ { .single = {KMT_PLAIN  , KEY_EQUAL}},
                    /* 6 > ^ */ { .single = {KMT_PLAIN  , KEY_TILDE}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL2 ROW_TOP
            {
                // left
                {
                    /* 0 _M4 */ { .type   = {KMT_MOD4_L}        },
                    /* 1 > X */ { .single = {KMT_SHIFT  , KEY_X}},
                    /* 2 > V */ { .single = {KMT_SHIFT  , KEY_V}},
                    /* 3 > L */ { .single = {KMT_SHIFT  , KEY_L}},
                    /* 4 > C */ { .single = {KMT_SHIFT  , KEY_C}},
                    /* 5 > W */ { .single = {KMT_SHIFT  , KEY_W}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > K */ { .single = {KMT_SHIFT  , KEY_K}},
                    /* 1 > H */ { .single = {KMT_SHIFT  , KEY_H}},
                    /* 2 > G */ { .single = {KMT_SHIFT  , KEY_G}},
                    /* 3 > F */ { .single = {KMT_SHIFT  , KEY_F}},
                    /* 4 > Q */ { .single = {KMT_SHIFT  , KEY_Q}},
                    /* 5 > ß */ { .single = {KMT_PLAIN  , KEY_MINUS}},
                    /* 6 > ~ */ { .single = {KMT_SHIFT  , KEY_TILDE}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL2 ROW_HOME
            {
                // left
                {
                    /* 0 lM3 */ { .type   = {KMT_MOD3_L}        },
                    /* 1 > U */ { .single = {KMT_SHIFT  , KEY_U}},
                    /* 2 > I */ { .single = {KMT_SHIFT  , KEY_I}},
                    /* 3 > A */ { .single = {KMT_SHIFT  , KEY_A}},
                    /* 4 > E */ { .single = {KMT_SHIFT  , KEY_E}},
                    /* 5 > O */ { .single = {KMT_SHIFT  , KEY_O}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > S */ { .single = {KMT_SHIFT  , KEY_S}},
                    /* 1 > N */ { .single = {KMT_SHIFT  , KEY_N}},
                    /* 2 > R */ { .single = {KMT_SHIFT  , KEY_R}},
                    /* 3 > T */ { .single = {KMT_SHIFT  , KEY_T}},
                    /* 4 > D */ { .single = {KMT_SHIFT  , KEY_D}},
                    /* 5 > Y */ { .single = {KMT_SHIFT  , KEY_Z}},
                    /* 6 rM3 */ { .type   = {KMT_MOD3_R        }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL2 ROW_BTM
            {
                // left
                {
                    /* 0 lSH */ { .type   = {KMT_MOD_SHIFT_L}   },
                    /* 1 > Ü */ { .single = {KMT_SHIFT  , KEY_LEFT_BRACE}},
                    /* 2 > Ö */ { .single = {KMT_SHIFT  , KEY_SEMICOLON}},
                    /* 3 > Ä */ { .single = {KMT_SHIFT  , KEY_QUOTE}},
                    /* 4 > P */ { .single = {KMT_SHIFT  , KEY_P}},
                    /* 5 > Z */ { .single = {KMT_SHIFT  , KEY_Y}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > B */ { .single = {KMT_SHIFT  , KEY_B}},
                    /* 1 > M */ { .single = {KMT_SHIFT  , KEY_M}},
                    /* 2 > - */ { .single = {KMT_PLAIN  , KEY_MINUS}},
                    /* 3 > . */ { .single = {KMT_PLAIN  , KEY_PERIOD}},
                    /* 4 > J */ { .single = {KMT_SHIFT  , KEY_J}},
                    /* 5 rSH */ { .type   = {KMT_MOD_SHIFT_R   }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL2 ROW_SPACE
            {
                // left
                {
                    /* 0 ctrl*/ { .single = {KMT_SHIFT  , KEY_LEFT_CTRL}},
                    /* 1 win */ { .single = {KMT_SHIFT  , KEY_LEFT_GUI}}, // XXX correct?
                    /* 2 spce*/ { .single = {KMT_SHIFT  , KEY_SPACE}},
                    /* 3 alt */ { .single = {KMT_SHIFT  , KEY_LEFT_ALT}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 alt */ { .single = {KMT_SHIFT  , KEY_RIGHT_ALT}},
                    /* 1 M4M */ { .type   = {KMT_MOD4_MOUSE}},
                    /* 2 spce*/ { .single = {KMT_SHIFT  , KEY_SPACE}},
                    /* 3 win */ { .single = {KMT_SHIFT  , KEY_RIGHT_GUI}}, // XXX correct?
                    /* 4 menu*/ { .single = {KMT_SHIFT  , KEY_GUI}}, // FIXME
                    /* 5 ctrl*/ { .single = {KMT_SHIFT  , KEY_RIGHT_CTRL}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
        },
        // DE LEVEL3
        {
            // DE LEVEL3 ROW_NUM
            {
                // left
                {
                    /* 0  -- */ { .type   = {KMT_PHANTOM}       },
                    /* 1 > ² */ { .single = {KMT_ALTGR  , KEY_2}},
                    /* 2 > ³ */ { .single = {KMT_ALTGR  , KEY_3}},
                    /* 3 > > */ { .single = {KMT_SHIFT  , KEY_4}}, // FIXME
                    /* 4 > < */ { .single = {KMT_SHIFT  , KEY_5}}, // FIXME
                    /* 5  -- */ { .type   = {KMT_PHANTOM}       },
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0  -- */ { .type   = {KMT_PHANTOM}       },
                    /* 1 > , */ { .single = {KMT_PLAIN  , KEY_COMMA}},
                    /* 2 > ' */ { .single = {KMT_SHIFT  , KEY_BACKSLASH}},
                    /* 3 > ' */ { .single = {KMT_SHIFT  , KEY_BACKSLASH}},
                    /* 4 > _ */ { .type   = {KMT_PHANTOM}       },
                    /* 5 > ° */ { .single = {KMT_SHIFT  , KEY_TILDE}},
                    /* 6  -- */ { .type   = {KMT_PHANTOM}       },
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL3 ROW_TOP
            {
                // left
                {
                    /* 0 _M4 */ { .type   = {KMT_MOD4_L}        },
                    /* 1  -- */ { .type   = {KMT_PHANTOM}       },
                    /* 2 > _ */ { .single = {KMT_SHIFT  , KEY_SLASH}},
                    /* 3 > [ */ { .single = {KMT_ALTGR  , KEY_8}},
                    /* 4 > ] */ { .single = {KMT_ALTGR  , KEY_9}},
                    /* 5 > ^ */ { .compose= {KMT_PLAIN , KEY_TILDE, KMT_PLAIN , KEY_SPACE }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > ! */ { .single = {KMT_SHIFT  , KEY_1}},
                    /* 1 > < */ { .single = {KMT_SHIFT  , KEY_H}}, // FIXME
                    /* 2 > > */ { .single = {KMT_SHIFT  , KEY_G}}, // FIXME
                    /* 3 > = */ { .single = {KMT_SHIFT  , KEY_0}},
                    /* 4 > & */ { .single = {KMT_SHIFT  , KEY_6}},
                    /* 5  -- */ { .type   = {KMT_PHANTOM}       },
                    /* 6  -- */ { .type   = {KMT_PHANTOM}       },
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL3 ROW_HOME
            {
                // left
                {
                    /* 0 lM3 */ { .type   = {KMT_MOD3_L}        },
                    /* 1 > \ */ { .single = {KMT_PLAIN  , KEY_BACKSLASH}},
                    /* 2 > / */ { .single = {KMT_PLAIN  , KEY_SLASH}},
                    /* 3 > { */ { .single = {KMT_ALTGR  , KEY_7}},
                    /* 4 > } */ { .single = {KMT_ALTGR  , KEY_0}},
                    /* 5 > * */ { .single = {KMT_SHIFT  , KEY_RIGHT_BRACE}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > ? */ { .single = {KMT_SHIFT  , KEY_MINUS}},
                    /* 1 > ( */ { .single = {KMT_SHIFT  , KEY_8}},
                    /* 2 > ) */ { .single = {KMT_SHIFT  , KEY_9}},
                    /* 3 > - */ { .single = {KMT_PLAIN  , KEY_SLASH}},
                    /* 4 > : */ { .single = {KMT_SHIFT  , KEY_PERIOD}},
                    /* 5 > @ */ { .single = {KMT_ALTGR  , KEY_Q}},
                    /* 6 rM3 */ { .type   = {KMT_MOD3_R        }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL3 ROW_BTM
            {
                // left
                {
                    /* 0 lSH */ { .type   = {KMT_MOD_SHIFT_L}   },
                    /* 1 > # */ { .single = {KMT_PLAIN  , KEY_BACKSLASH}},
                    /* 2 > $ */ { .single = {KMT_SHIFT  , KEY_4}},
                    /* 3 > | */ { .single = {KMT_SHIFT  , KEY_QUOTE}}, // FIXME
                    /* 4 > ~ */ { .single = {KMT_ALTGR  , KEY_RIGHT_BRACE}},
                    /* 5 > ` */ { .compose= {KMT_SHIFT , KEY_EQUAL, KMT_PLAIN, KEY_SPACE}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > + */ { .single = {KMT_PLAIN  , KEY_RIGHT_BRACE}},
                    /* 1 > % */ { .single = {KMT_SHIFT  , KEY_5}},
                    /* 2 > " */ { .single = {KMT_SHIFT  , KEY_2}},
                    /* 3 > ' */ { .single = {KMT_SHIFT  , KEY_BACKSLASH}},
                    /* 4 > ; */ { .single = {KMT_SHIFT  , KEY_COMMA}},
                    /* 5 rSH */ { .type   = {KMT_MOD_SHIFT_R   }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL3 ROW_SPACE
            {
                // left
                {
                    /* 0 ctrl*/ { .single = {KMT_PLAIN  , KEY_LEFT_CTRL}},
                    /* 1 win */ { .single = {KMT_PLAIN  , KEY_LEFT_GUI}}, // XXX correct?
                    /* 2 spce*/ { .single = {KMT_PLAIN  , KEY_SPACE}},
                    /* 3 alt */ { .single = {KMT_PLAIN  , KEY_LEFT_ALT}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 alt */ { .single = {KMT_PLAIN  , KEY_RIGHT_ALT}},
                    /* 1 M4M */ { .type   = {KMT_MOD4_MOUSE}},
                    /* 2 spce*/ { .single = {KMT_PLAIN  , KEY_SPACE}},
                    /* 3 win */ { .single = {KMT_PLAIN  , KEY_RIGHT_GUI}}, // XXX correct?
                    /* 4 menu*/ { .single = {KMT_PLAIN  , KEY_GUI}}, // FIXME
                    /* 5 ctrl*/ { .single = {KMT_PLAIN  , KEY_RIGHT_CTRL}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
        },
        // DE LEVEL4
        {
            // DE LEVEL4 ROW_NUM
            {
                // left
                {
                    /* 0 > 1 */ { .single = {KMT_PLAIN  , KEY_1}}, // xxx
                    /* 1 > 2 */ { .single = {KMT_PLAIN  , KEY_2}}, // xxx
                    /* 2 > 3 */ { .single = {KMT_PLAIN  , KEY_3}}, // xxx
                    /* 3 > 4 */ { .single = {KMT_PLAIN  , KEY_4}}, // xxx
                    /* 4 > 5 */ { .single = {KMT_PLAIN  , KEY_5}}, // xxx
                    /* 5 > 6 */ { .single = {KMT_PLAIN  , KEY_6}}, // xxx
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > 7 */ { .single = {KMT_PLAIN  , KEY_7}}, // xxx
                    /* 1 >tab*/ { .single = {KMT_PLAIN_X, KEY_TAB}},
                    /* 2 > / */ { .single = {KMT_PLAIN_X, KEYPAD_SLASH}},
                    /* 3 > * */ { .single = {KMT_PLAIN_X, KEYPAD_ASTERIX}},
                    /* 4 > - */ { .single = {KMT_PLAIN_X, KEYPAD_MINUS}},
                    /* 5 > ` */ { .single = {KMT_SHIFT  , KEY_EQUAL}}, // xxx
                    /* 6 > ^ */ { .single = {KMT_PLAIN  , KEY_TILDE}}, // xxx
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL4 ROW_TOP
            {
                // left
                {
                    /* 0 _M4 */ { .type   = {KMT_MOD4_L}        },
                    /* 1 >pup*/ { .single = {KMT_PLAIN_X, KEY_PAGE_UP}},
                    /* 2 >bsp*/ { .single = {KMT_PLAIN_X, KEY_BACKSPACE}},
                    /* 3 >aup*/ { .single = {KMT_PLAIN_X, KEY_UP}},
                    /* 4 >del*/ { .single = {KMT_PLAIN_X, KEY_DELETE}},
                    /* 5 >pdn*/ { .single = {KMT_PLAIN_X, KEY_PAGE_DOWN}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > k */ { .single = {KMT_PLAIN  , KEY_K}}, // xxx
                    /* 1 > 7 */ { .single = {KMT_PLAIN_X, KEYPAD_7}},
                    /* 2 > 8 */ { .single = {KMT_PLAIN_X, KEYPAD_8}},
                    /* 3 > 9 */ { .single = {KMT_PLAIN_X, KEYPAD_9}},
                    /* 4 > q */ { .single = {KMT_PLAIN_X, KEYPAD_PLUS}},
                    /* 5 > ß */ { .single = {KMT_PLAIN_X, KEYPAD_MINUS}},
                    /* 6 > ' */ { .single = {KMT_PLAIN  , KEY_EQUAL}}, // xxx
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL4 ROW_HOME
            {
                // left
                {
                    /* 0 lM3 */ { .type   = {KMT_MOD3_L}        },
                    /* 1 >hme*/ { .single = {KMT_PLAIN_X, KEY_HOME}},
                    /* 2 >alf*/ { .single = {KMT_PLAIN_X, KEY_LEFT}},
                    /* 3 >adn*/ { .single = {KMT_PLAIN_X, KEY_DOWN}},
                    /* 4 >art*/ { .single = {KMT_PLAIN_X, KEY_RIGHT}},
                    /* 5 >end*/ { .single = {KMT_PLAIN_X, KEY_END}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > ? */ { .single = {KMT_PLAIN_X, KEY_S}}, // xxx
                    /* 1 > 4 */ { .single = {KMT_PLAIN_X, KEYPAD_4}},
                    /* 2 > 5 */ { .single = {KMT_PLAIN_X, KEYPAD_5}},
                    /* 3 > 6 */ { .single = {KMT_PLAIN_X, KEYPAD_6}},
                    /* 4 > , */ { .single = {KMT_PLAIN  , KEY_COMMA}},
                    /* 5 > . */ { .single = {KMT_PLAIN  , KEY_PERIOD}},
                    /* 6 rM3 */ { .type   = {KMT_MOD3_R        }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL4 ROW_BTM
            {
                // left
                {
                    /* 0 lSH */ { .type   = {KMT_MOD_SHIFT_L}   },
                    /* 1 >esc*/ { .single = {KMT_PLAIN_X, KEY_ESC}},
                    /* 2 >tab*/ { .single = {KMT_PLAIN_X, KEY_TAB}},
                    /* 3 >ins*/ { .single = {KMT_PLAIN_X, KEY_INSERT}},
                    /* 4 >ret*/ { .single = {KMT_PLAIN_X, KEYPAD_ENTER}},
                    /* 5 >udo*/ { .single = {KMT_PLAIN_X, KEY_Y}}, // xxx
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > : */ { .single = {KMT_SHIFT  , KEY_PERIOD}},
                    /* 1 > 1 */ { .single = {KMT_PLAIN_X, KEYPAD_1}},
                    /* 2 > 2 */ { .single = {KMT_PLAIN_X, KEYPAD_2}},
                    /* 3 > 3 */ { .single = {KMT_PLAIN_X, KEYPAD_3}},
                    /* 4 > ; */ { .single = {KMT_SHIFT  , KEY_COMMA}},
                    /* 5 rSH */ { .type   = {KMT_MOD_SHIFT_R   }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL4 ROW_SPACE
            {
                // left
                {
                    /* 0 ctrl*/ { .single = {KMT_PLAIN  , KEY_LEFT_CTRL}},
                    /* 1 win */ { .single = {KMT_PLAIN  , KEY_LEFT_GUI}}, // XXX correct?
                    /* 2 spce*/ { .single = {KMT_PLAIN  , KEY_SPACE}},
                    /* 3 alt */ { .single = {KMT_PLAIN  , KEY_LEFT_ALT}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 alt */ { .single = {KMT_PLAIN  , KEY_RIGHT_ALT}},
                    /* 1 M4M */ { .type   = {KMT_MOD4_MOUSE}},
                    /* 2 > 0 */ { .single = {KMT_PLAIN_X, KEYPAD_0}},
                    /* 3 win */ { .single = {KMT_PLAIN  , KEY_RIGHT_GUI}}, // XXX correct?
                    /* 4 menu*/ { .single = {KMT_PLAIN  , KEY_GUI}}, // FIXME
                    /* 5 ctrl*/ { .single = {KMT_PLAIN  , KEY_RIGHT_CTRL}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
        },
        // DE LEVEL4_MOUSE
        {
            // DE LEVEL4_MOUSE ROW_NUM
            {
                // left
                {
                    /* 0 >f1 */ { .single = {KMT_PLAIN_X, KEY_F1}},
                    /* 1 >f2 */ { .single = {KMT_PLAIN_X, KEY_F2}},
                    /* 2 >f3 */ { .single = {KMT_PLAIN_X, KEY_F3}},
                    /* 3 >f4 */ { .single = {KMT_PLAIN_X, KEY_F4}},
                    /* 4 >f5 */ { .single = {KMT_PLAIN_X, KEY_F5}},
                    /* 5 >f6 */ { .single = {KMT_PLAIN_X, KEY_F6}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 >f7 */ { .single = {KMT_PLAIN_X, KEY_F7}},
                    /* 1 >f8 */ { .single = {KMT_PLAIN_X, KEY_F8}},
                    /* 2 >f9 */ { .single = {KMT_PLAIN_X, KEY_F9}},
                    /* 3 >f10*/ { .single = {KMT_PLAIN_X, KEY_F10}},
                    /* 4 >f11*/ { .single = {KMT_PLAIN_X, KEY_F11}},
                    /* 5 >f12*/ { .single = {KMT_PLAIN_X, KEY_F12}},
                    /* 6 >pnt*/ { .single = {KMT_PLAIN_X, KEY_PRINTSCREEN}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL4_MOUSE ROW_TOP
            {
                // left
                {
                    /* 0 _M4 */ { .type   = {KMT_MOD4_L}        },
                    /* 1 >pup*/ { .single = {KMT_PLAIN_X, KEY_PAGE_UP}},
                    /* 2 >bsp*/ { .single = {KMT_PLAIN_X, KEY_BACKSPACE}},
                    /* 3 >aup*/ { .single = {KMT_PLAIN_X, KEY_UP}},
                    /* 4 >del*/ { .single = {KMT_PLAIN_X, KEY_DELETE}},
                    /* 5 >pdn*/ { .single = {KMT_PLAIN_X, KEY_PAGE_DOWN}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > k */ { .single = {KMT_PLAIN  , KEY_K}}, // xxx
                    /* 1 > 7 */ { .single = {KMT_PLAIN_X, KEYPAD_7}}, // TODO: ctrl+c
                    /* 2 > 8 */ { .single = {KMT_PLAIN_X, KEYPAD_8}}, // TODO: ctrl+v
                    /* 3 > 9 */ { .single = {KMT_PLAIN_X, KEYPAD_9}}, // TODO: ctrl+x
                    /* 4 > q */ { .single = {KMT_PLAIN_X, KEYPAD_PLUS}},
                    /* 5 > ß */ { .single = {KMT_PLAIN_X, KEYPAD_MINUS}},
                    /* 6 > ' */ { .single = {KMT_PLAIN  , KEY_EQUAL}}, // xxx
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL4_MOUSE ROW_HOME
            {
                // left
                {
                    /* 0 lM3 */ { .type   = {KMT_MOD3_L}        },
                    /* 1 >hme*/ { .single = {KMT_PLAIN_X, KEY_HOME}},
                    /* 2 >alf*/ { .single = {KMT_PLAIN_X, KEY_LEFT}},
                    /* 3 >adn*/ { .single = {KMT_PLAIN_X, KEY_DOWN}},
                    /* 4 >art*/ { .single = {KMT_PLAIN_X, KEY_RIGHT}},
                    /* 5 >end*/ { .single = {KMT_PLAIN_X, KEY_END}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > ? */ { .single = {KMT_PLAIN_X, KEY_S}}, // todo: mouse btn5
                    /* 1 > 4 */ { .single = {KMT_PLAIN_X, KEYPAD_4}}, // todo: mouse btn1
                    /* 2 > 5 */ { .single = {KMT_PLAIN_X, KEYPAD_5}}, // todo: mouse btn2
                    /* 3 > 6 */ { .single = {KMT_PLAIN_X, KEYPAD_6}}, // todo: mouse btn3
                    /* 4 > , */ { .single = {KMT_PLAIN  , KEY_COMMA}}, // todo: mouse btn4
                    /* 5 > . */ { .single = {KMT_PLAIN  , KEY_PERIOD}}, // todo: mouse btn6
                    /* 6 rM3 */ { .type   = {KMT_MOD3_R        }},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL4_MOUSE ROW_BTM
            {
                // left
                {
                    /* 0 lSH */ { .type   = {KMT_MOD_SHIFT_L}   },
                    /* 1 >esc*/ { .single = {KMT_PLAIN_X, KEY_ESC}},
                    /* 2 >tab*/ { .single = {KMT_PLAIN_X, KEY_TAB}},
                    /* 3 >ins*/ { .single = {KMT_PLAIN_X, KEY_INSERT}},
                    /* 4 >ret*/ { .single = {KMT_PLAIN_X, KEY_ENTER}},
                    /* 5 >udo*/ { .single = {KMT_PLAIN_X, KEY_Y}}, // xxx
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 > : */ { .single = {KMT_SHIFT  , KEY_PERIOD}}, // todo: mouse btn5 double click
                    /* 1 > 1 */ { .single = {KMT_PLAIN_X, KEYPAD_1}}, // todo: mouse btn1 double click
                    /* 2 > 2 */ { .single = {KMT_PLAIN_X, KEYPAD_2}}, // todo: mouse btn2 double click
                    /* 3 > 3 */ { .single = {KMT_PLAIN_X, KEYPAD_3}}, // todo: mouse btn3 double click
                    /* 4 > ; */ { .single = {KMT_SHIFT  , KEY_COMMA}}, // todo: mouse btn4 double click
                    /* 5 rSH */ { .type   = {KMT_MOD_SHIFT_R   }}, // todo: mouse btn6 double click
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE LEVEL4_MOUSE ROW_SPACE
            {
                // left
                {
                    /* 0 ctrl*/ { .single = {KMT_PLAIN  , KEY_LEFT_CTRL}},
                    /* 1 win */ { .single = {KMT_PLAIN  , KEY_LEFT_GUI}}, // XXX correct?
                    /* 2 spce*/ { .single = {KMT_PLAIN  , KEY_SPACE}},
                    /* 3 alt */ { .single = {KMT_PLAIN  , KEY_LEFT_ALT}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 alt */ { .single = {KMT_PLAIN  , KEY_RIGHT_ALT}},
                    /* 1 M4M */ { .type   = {KMT_MOD4_MOUSE}},
                    /* 2 > 0 */ { .single = {KMT_PLAIN_X, KEYPAD_0}},
                    /* 3 win */ { .single = {KMT_PLAIN  , KEY_RIGHT_GUI}}, // XXX correct?
                    /* 4 menu*/ { .single = {KMT_PLAIN  , KEY_GUI}}, // FIXME
                    /* 5 ctrl*/ { .single = {KMT_PLAIN  , KEY_RIGHT_CTRL}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
        },
        // all remaining levels will be initialzed with zeros (=> KMT_PHANTOM)
    },
   // KB_NEO
    {
        // NEO LEVEL1
        {
            // NEO LEVEL1 ROW_NUM
            {
                // left
                {
                    /* 0 */ { .single = {KMT_PLAIN  , KEY_1}},
                    /* 1 */ { .single = {KMT_PLAIN  , KEY_2}},
                    /* 2 */ { .single = {KMT_PLAIN  , KEY_3}},
                    /* 3 */ { .single = {KMT_PLAIN  , KEY_4}},
                    /* 4 */ { .single = {KMT_PLAIN  , KEY_5}},
                    /* 5 */ { .single = {KMT_PLAIN  , KEY_6}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 */ { .single = {KMT_PLAIN  , KEY_7}},
                    /* 1 */ { .single = {KMT_PLAIN  , KEY_8}},
                    /* 2 */ { .single = {KMT_PLAIN  , KEY_9}},
                    /* 3 */ { .single = {KMT_PLAIN  , KEY_0}},
                    /* 4 */ { .single = {KMT_PLAIN  , KEY_MINUS}},
                    /* 5 */ { .single = {KMT_PLAIN  , KEY_EQUAL}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // NEO LEVEL1 ROW_TOP
            {
            },
            // NEO LEVEL1 ROW_HOME
            {
            },
            // NEO LEVEL1 ROW_BTM
            {
            },
            // NEO LEVEL1 ROW_COUNT
            {
            },
        },
        // NEO LEVEL2
        {
        },
        // NEO LEVEL3
        {
        },
        // NEO LEVEL4
        {
        },
        // NEO LEVEL4_MOUSE
        {
        },
        // all remaining levels will be initialzed with zeros (=> KMT_PHANTOM)
    },   
   // KB_US
   {
        // US LEVEL1
        {
            // US LEVEL1 ROW_NUM
            {
                // left
                {
                    /* 0 */ { .single = {KMT_PLAIN  , KEY_1}},
                    /* 1 */ { .single = {KMT_PLAIN  , KEY_2}},
                    /* 2 */ { .single = {KMT_PLAIN  , KEY_3}},
                    /* 3 */ { .single = {KMT_PLAIN  , KEY_4}},
                    /* 4 */ { .single = {KMT_PLAIN  , KEY_5}},
                    /* 5 */ { .single = {KMT_PLAIN  , KEY_6}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 */ { .single = {KMT_PLAIN  , KEY_7}},
                    /* 1 */ { .single = {KMT_PLAIN  , KEY_8}},
                    /* 2 */ { .single = {KMT_PLAIN  , KEY_9}},
                    /* 3 */ { .single = {KMT_PLAIN  , KEY_0}},
                    /* 4 */ { .single = {KMT_PLAIN  , KEY_MINUS}},
                    /* 5 */ { .single = {KMT_SHIFT  , KEY_TILDE}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // US LEVEL1 ROW_TOP
            {
            },
            // US LEVEL1 ROW_HOME
            {
            },
            // US LEVEL1 ROW_BTM
            {
            },
            // US LEVEL1 ROW_COUNT
            {
            },
        },
        // US LEVEL2
        {
        },
        // US LEVEL3
        {
        },
        // US LEVEL4
        {
        },
        // US LEVEL4_MOUSE
        {
        },
        // all remaining levels will be initialzed with zeros (=> KMT_PHANTOM)
    },
   // KB_DE_APPLE
   // KB_US_APPLE
};