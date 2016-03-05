/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * API to be used to publish debug messages.
 *
 * Actual mechanisms used to publish the debug messages may be changed
 * at compile time and even at runtime.
 */


void dbg_init();

void dbg_cycle();

enum dbg_level_e {
  DBG_LVL_NONE,
  DBG_LVL_ERROR,
  DBG_LVL_WARN,
  DBG_LVL_INFO,
};
extern enum dbg_level_e dbg_threshold;

enum dbg_channels_e {
  DBG_CH_BUFFER = (1 << 0),
  DBG_CH_UART   = (1 << 1),
  DBG_CH_KEYS   = (1 << 2),
};
extern uint8_t dbg_active_channels;

#define dbg_declare_msg(id, errcode, format, ...)			\
  const uint8_t dbg_msg_##id##_errcode = errcode;			\
  const char *const dbg_msg_##id##_format = format;			\
  const uint8_t dbg_msg_##id##_arg_sizes[] = __VA_ARGS__;

//const uint8_t dbg_msg_##id##payload_size = payload_size;
//struct dbg_msg_##id##_args_s { __VA_ARGS__ };				\
//const uint16_t dbg_msg_##id##_args_size = sizeof(struct dbg_msg_##id##_args_s)

/// For internal use, shuold not be called directly.
/// Call dbg_error, dbg_warn or dbg_info instead.
#define dbg_resolve_args(lvl, id, ...)			\
  dbg_process(						\
	      lvl,					\
	      dbg_msg_##id##_errcode,			\
	      dbg_msg_##id##_format,			\
	      dbg_msg_##id##_arg_sizes,			\
	      sizeof(dbg_msg_##id##_arg_sizes),		\
	      __VA_ARGS__				\
						)

/// For internal use, shuold not be called directly.
/// Call dbg_error, dbg_warn or dbg_info instead.
#define dbg_add(lvl, ...) {					\
    if (lvl <= dbg_threshold && dbg_is_active()) {		\
      dbg_resolve_args(lvl, __VA_ARGS__);				\
    }								\
  }

#define dbg_error(...) {				\
    dbg_add(DBG_LVL_ERROR, __VA_ARGS__);			\
  }

#define dbg_warn(...) {				\
    dbg_add(DBG_LVL_WARN, __VA_ARGS__);			\
  }

#define dbg_info(...) {				\
    dbg_add(DBG_LVL_INFO, __VA_ARGS__);			\
  }

static inline bool dbg_is_active() {
  return dbg_active_channels > 0;
}

void dbg_process(enum dbg_level_e lvl, uint8_t errcode, char *format, arg_sizes[], arg_sizes_cnt, ...);
