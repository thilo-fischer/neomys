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


#ifdef NDEBUG

#define dbg_init(...)
#define dbg_cycle(...)
#define dbg_set_threshold(...)

#define dbg_define_msg(...)

#define dbg_error(...)
#define dbg_warn(...)
#define dbg_info(...)

#define dbg_flush_buffer(...)

#else // def NDEBUG
// !def(NDEBUG)

void dbg_init();

void dbg_cycle();

/// Debug messages shall be categorized with a loglevel indicating the
/// severity of the issue being logged. The enum defines the supported
/// loglevels.
enum dbg_level_e {
  DBG_LVL_DEBUG,   ///< debug messages
  DBG_LVL_INFO,    ///< informative messages
  DBG_LVL_WARN,    ///< messages to signal something not working as expected
  DBG_LVL_ERROR,   ///< messages to signal something is going seriously wrong
  DBG_LVL_ENUM_END ///< not a loglevel, just a reference behind the last enum element
};

/// Only debug messages with a loglevel equal to or greater than the
/// value configured as threshold will be processed. Set to
/// DBG_LVL_ENUM_END to disable logging at all.
extern enum dbg_level_e dbg_threshold;

static inline void dbg_set_threshold(enum dbg_level_e t) {
  dbg_threshold = t;
}

/// Only debug messages with a loglevel equal to or greater than the
/// value configured as buffer threshold will be buffered. Set to
/// DBG_LVL_ENUM_END to disable debug message buffering at all.
extern enum dbg_level_e dbg_buffer_threshold;

static inline void dbg_set_buffer_threshold(enum dbg_level_e t) {
  dbg_buffer_threshold = t;
}

/// Debug messages can be sent via one or multiple interfaces to
/// different destinations. The enum defines the set of supported
/// channels and specifies bit positions to store the set of active
/// channels in a bitfield.
enum dbg_channels_e {
  DBG_CH_BUFFER = (1 << 0), ///< store all relevant data of the debug
			    ///  message in a buffer and (optionally)
			    ///  signal to the keyboard user there is
			    ///  new data in the buffer.
  DBG_CH_UART   = (1 << 1), ///< send debug info via a UART interface of the controller
  DBG_CH_KEYS   = (1 << 2), ///< send keycodes to the host that will
			    ///  make the debug message appear in a text
			    ///  editor
};
/// Bitfield to specify the set of active channels. Debug messages
/// will be directed only to those channels whose bit is high in this
/// bitfield.
typedef uint8_t dbg_channel_spec_t;
extern dbg_channel_spec_t dbg_active_channels;

/// format used to store info about defined debug messages. @see dbg_define_msg
struct dbg_msgspec_s {
  uint8_t errcode;    ///< The error code to be associated with this
                      ///  debug message. To be used when sending
                      ///  debug messages is an abbreviated binary
                      ///  format.
  char *const format; ///< Format string compatible to printf format
                      ///  strings. To be used when outputting the
                      ///  debug message in text form.
  uint8_t *arg_sizes; ///< Byte sizes of additional arguments to be expected.
  uint8_t args_cnt;   ///< Number of additional arguments to be expected.
  uint8_t args_total_size; ///< Sum of byte sizes of all additional arguments.
};

/// XXX move to another file
/// @return the sum of +count+ size_t arguments in the variable argument list.
static inline size_t util_sum_args_size_t(uint8_t count, ...) {
  va_list argptr;
  va_start(argptr, count);
  size_t sum = 0;
  for (int i = 0; i < count; ++i) {
    sum += va_arg(argptr, size_t);
  }
  va_end(argptr);
}

/// Debug system is not prepared to send arbitrary messages to the
/// channels. All messages that possibly might be sent at runtime need
/// to be declared somewhere in the code. These debug message
/// definitions specify the associations of error codes and debug
/// messages and also allow to store debug message data in the
/// ringbuffer with minimal memory consumption. (The latter is very
/// beneficial on small controllers with little RAM).
/// 
/// @param[in] id the identifier used to refer to the debug message
/// being defined.
///
/// @param[in] errcode The error code to be associated with this debug
/// message. May be a char or a signed or unsigned int8_t. Does not
/// have any technical relevance. To be used when sending debug
/// messages is an abbreviated binary format.
///
/// @param[in] Format Format string compatible to printf format
/// strings. To be used when outputting the debug message in text form.
/// 
/// @param[in] ... If the format string expects additional arguments
/// and/or additional binary data shall be appended to the error code
/// when outputting the debug message in an abbreviated binary format,
/// a list of the sizes (in bytes) of those data types of the expected
/// additonal arguments shall be given as variable argument list.
#define dbg_define_msg(id, errcode, format, ...)			\
  static const uint8_t dbg_msg_##id##_arg_sizes[] = { __VA_ARGS__ };	\
  const struct dbg_msgspec_s dbg_msg_##id = {				\
    (uint8_t) errcode,							\
    format,								\
    &dbg_msg_##id##_arg_sizes,						\
    sizeof(dbg_msg_##id##_arg_sizes),					\
    util_sum_args(sizeof(dbg_msg_##id##_arg_sizes), __VA_ARGS__)	\
  }

/// Output debug message with loglevel DBG_LVL_ERROR.
/// 
/// @param[in] ... First parameter shall be the identifier refering to
/// the debug message to output. Additional arguments shall be given
/// according to the debug message's expectation of additional
/// arguments.
#define dbg_error(...) {					\
    dbg_add(DBG_LVL_ERROR, __VA_ARGS__);			\
  }
  
/// Output debug message with loglevel DBG_LVL_WARN. For parameter
/// desciption, see @see dbg_error.
#define dbg_warn(...) {					\
    dbg_add(DBG_LVL_WARN, __VA_ARGS__);			\
  }

/// Output debug message with loglevel DBG_LVL_INFO. For parameter
/// desciption, see @see dbg_error.
#define dbg_info(...) {					\
    dbg_add(DBG_LVL_INFO, __VA_ARGS__);			\
  }

/// Output debug message with loglevel DBG_LVL_INFO. For parameter
/// desciption, see @see dbg_error.
#define dbg_debug(...) {					\
    dbg_add(DBG_LVL_DEBUG, __VA_ARGS__);			\
  }

/// Shorthand for dbg_debug
#define dbg(...) dbg_debug(__VA_ARGS__)

/// For internal use, shuold not be called directly.
/// Call dbg_error, dbg_warn or dbg_info instead.
///
/// Wrapper of dbg_proces to be referenced from dbg_error, dbg_warn
/// and dbg_info.
#define dbg_add(lvl, ...) {						\
    if (lvl >= dbg_threshold && dbg_has_active_channels()) {		\
      dbg_resolve_args(lvl, __VA_ARGS__);				\
    }									\
  }

/// For internal use, shuold not be called directly.
/// Call dbg_error, dbg_warn or dbg_info instead.
///
/// Wrapper of dbg_proces to be referenced from dbg_add. Extract debug
/// message id from variable argument list.
#define dbg_resolve_args(lvl, id, ...)				\
  dbg_process(							\
	      lvl,						\
	      &dbg_msg_##id,					\
	      __VA_ARGS__					\
	     )

/// For internal use.
/// @return true if at least one channel is active, false otherwise.
static inline bool dbg_has_active_channels() {
  return dbg_active_channels > 0;
}

/// For internal use, shuold not be called directly.
/// Call dbg_error, dbg_warn or dbg_info instead.
///
/// Output debug message to all currently active channels.
void dbg_process(enum dbg_level_e lvl, struct dbg_msgspec_s *msgspec, ...);

/// Output buffered dbg messages to the specified channels. Buffer
/// channel will be ignored. Clear buffer afterwards.
void dbg_flush_buffer(dbg_channel_spec_t dest_channels);


#endif // def NDEBUG

