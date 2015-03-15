/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include "sendkeys.h"

#include "keytranslation.h"
#include "teensy_codelib/usb_keyboard/usb_keyboard.h"

/**
 * Keyboard layout the USB host is configured to use.
 */
enum keylayout_e keymapping_mode_current = TKL_DE;

static inline const union keyseq_u *get_current_mapped_key_ptr(uint8_t controller, enum row_e row, uint8_t col) {
    return get_mapped_key_ptr(keymapping_mode_current, controller, row, col, level_current);
}

static inline const struct keyleveltranslations_s *get_current_mapped_klt_ptr(uint8_t controller, enum row_e row, uint8_t col) {
    return get_mapped_klt_ptr(keymapping_mode_current, controller, row, col);
}

static inline struct keyleveltranslations_s get_current_mapped_klt(uint8_t controller, enum row_e row, uint8_t col) {
    struct keyleveltranslations_s klt;
    uint8_t *ptr = (uint8_t *) get_current_mapped_klt_ptr(controller, row, col);
    uint8_t i;
    for (i = 0; i < sizeof(struct keyleveltranslations_s); ++i) {
        ((uint8_t *) &klt)[i] = pgm_read_byte(ptr + i);
    }
    return klt;
}


struct klt_changes_s {
    struct keyleveltranslations_s klt;
    enum key_change_e change;
};

struct klt_changes_s klt_charge[CHANGED_KEYS_CNT_MAX];
uint8_t klt_charge_cnt = 0;

void clear_klt_charge() {
    klt_charge_cnt = 0;
}

void add_klt_charge(struct keyleveltranslations_s klt, enum key_change_e kchange) {
    klt_charge[klt_charge_cnt].klt = klt;
    klt_charge[klt_charge_cnt].change = kchange;
    ++klt_charge_cnt;
    if (klt_charge_cnt >= CHANGED_KEYS_CNT_MAX) {
        warning(W_TOO_MANY_KEYS);
    }
}

struct key_seq_step_s {
    enum key_change_e change;
    uint8_t key;
    uint8_t modifier;
};

#define KEY_SEQ_QUEUE_LENGTH 32
struct key_seq_step_s key_seq_queue[KEY_SEQ_QUEUE_LENGTH] = {{0}};
size_t key_seq_queue_start = 0;
size_t key_seq_queue_end   = 0;

bool key_seq_queue_empty() {
    return key_seq_queue_start == key_seq_queue_end;
}

bool key_seq_queue_full() {
    if (key_seq_queue_start <= key_seq_queue_end) {
        return key_seq_queue_start == 0 && key_seq_queue_end == KEY_SEQ_QUEUE_LENGTH - 1;
    } else {
        return key_seq_queue_end == key_seq_queue_start - 1;
    }
}

void key_seq_queue_enqueue(const struct key_seq_step_s *step) {
    if (key_seq_queue_full()) {
        warning(W_TOO_MANY_KEYS);
        return;
    }
    key_seq_queue[key_seq_queue_end] = *step;
    ++key_seq_queue_end;
    if (key_seq_queue_end == KEY_SEQ_QUEUE_LENGTH) {
        key_seq_queue_end = 0;
    }
}

const struct key_seq_step_s NULL_STEP = { KC_PRESS, 0, 0}; // FIXME

struct key_seq_step_s key_seq_queue_dequeue() {
    if (key_seq_queue_empty()) {
        warning(W_PROGRAMMING_ERROR);
        return NULL_STEP; // FIXME
    }
    struct key_seq_step_s* result = &key_seq_queue[key_seq_queue_start];
    ++key_seq_queue_start;
    if (key_seq_queue_start == KEY_SEQ_QUEUE_LENGTH) {
        key_seq_queue_start = 0;
    }
    return *result;
}

#define KEY_ANY_SHIFT (KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT)
uint8_t modifiers = 0;
bool modifiers_changed = false;

void process_klt_charge(enum neo_levels_e level) {
    uint8_t i;
    for (i = 0; i < klt_charge_cnt; ++i) {
        const union keyseq_u *seq = &klt_charge[i].klt.seq[level];
        switch (seq->type.type) {
        case KO_PHANTOM:
            // do nothing
            break;
        case KO_PLAIN:
            {
                struct key_seq_step_s step = { .change = klt_charge[i].change, .key = seq->single.key, .modifier = (modifiers & ~KEY_ANY_SHIFT)};
                key_seq_queue_enqueue(&step);
                break;
            }
        case KO_PLAIN_X:
            {
                struct key_seq_step_s step = { .change = klt_charge[i].change, .key = seq->single.key, .modifier = modifiers};
                key_seq_queue_enqueue(&step);
                break;
            }
        case KO_SHIFT:
            {
                struct key_seq_step_s step = { .change = klt_charge[i].change, .key = seq->single.key, .modifier = (modifiers | KEY_SHIFT)};
                key_seq_queue_enqueue(&step);
                break;
            }
        case KO_ALTGR:
            {
                struct key_seq_step_s step = { .change = klt_charge[i].change, .key = seq->single.key, .modifier = (modifiers | KEY_CTRL | KEY_ALT)}; // FIXME !! need AltGr !!
                key_seq_queue_enqueue(&step);
                break;
            }
        case KO_LEVEL_MOD:
            warning(W_PROGRAMMING_ERROR);
            break;
        case KO_MODIFIER:
        case KO_LEVEL_MOD_X:
            warning(W_PROGRAMMING_ERROR);
            break;
        default:
            warning(W_PROGRAMMING_ERROR);
        }
    }
}

uint8_t *find_keyboard_key(uint8_t key) {
    uint8_t i;
    for (i = 0; i < 6; ++i) {
        if (keyboard_keys[i] == key) {
            return &keyboard_keys[i];
        }
    }
    return NULL;
}

void process_keyseqqueue() {
	if (!key_seq_queue_empty()) {
		struct key_seq_step_s step = key_seq_queue_dequeue();
		if (step.change == KC_PRESS) {
			uint8_t *free = find_keyboard_key(0);
			if (free == NULL) {
				warning(W_TOO_MANY_KEYS);
			} else {
				*free = step.key;
			}
		} else {
			uint8_t *pos = find_keyboard_key(step.key);
			if (pos == NULL) {
				warning(W_PROGRAMMING_ERROR);
			} else {
				*pos = 0;
			}
		}
		keyboard_modifier_keys = step.modifier;

		usb_keyboard_send();
	}
}

