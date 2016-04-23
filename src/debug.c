/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * Generic parts and inclusion of specific debug implementation.
 */

#include "debug.h"

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "indication.h"
#include "ucontroller.h"

//////////////////
// declarations //
//////////////////

/// Output debug message to all currently active channels.
static void dbg_vprocess(enum dbg_level_e lvl, const struct dbg_msgspec_s *msgspec, const va_list argptr);

/// vararg wrapper to dbg_voutput
static void dbg_output(dbg_channel_spec_t dest_channels, enum dbg_level_e lvl, const struct dbg_msgspec_s *msgspec, ...);

/// Output debug message to all channels active in the given bitfield.
static void dbg_voutput(dbg_channel_spec_t dest_channels, enum dbg_level_e lvl, const struct dbg_msgspec_s *msgspec, const va_list start_argptr);

static void dbg_buf_add(enum dbg_level_e lvl, const struct dbg_msgspec_s *msgspec, uint8_t *bin_buf, uint8_t bin_buf_size);

static void dbg_output_uart_bin(uint8_t errcode, uint8_t *bin_buf, uint8_t bin_buf_size);
static void dbg_voutput_string(dbg_channel_spec_t dest_channel, enum dbg_level_e lvl, const char *fmtstr, va_list argptr);

static inline bool dbg_is_binary_active(dbg_channel_spec_t dest_channels);
static inline bool dbg_is_string_active(dbg_channel_spec_t dest_channels);


/////////////////
// definitions //
/////////////////

#if 1
enum dbg_level_e dbg_threshold = DBG_LVL_WARN;
#else
enum dbg_level_e dbg_threshold = DBG_LVL_DEBUG;
#endif
enum dbg_level_e dbg_buffer_threshold = DBG_LVL_WARN;

dbg_channel_spec_t dbg_active_channels = DBG_CH_BUFFER;

/// whether to send just error codes via UART (in contrast to sending
/// string corstructed form the printf-alike format string and
/// optional additional arguments)
#if 0
bool dbg_uart_code = true;
#else
bool dbg_uart_code = false;
#endif

/// when dbg_uart_code is active: send binary data of additional
/// arguments @todo not yet supported
bool dbg_uart_payload = true;

/// prepend these bytes to each UART debug output
uint8_t dbg_uart_prefix_default[] = { 0x00 };
uint8_t *dbg_uart_prefix = dbg_uart_prefix_default;
uint8_t dbg_uart_prefix_size = sizeof(dbg_uart_prefix_default);

/// append these bytes to each UART debug output
uint8_t dbg_uart_suffix_default[] = { 0XFF };
uint8_t *dbg_uart_suffix = dbg_uart_suffix_default;
uint8_t dbg_uart_suffix_size = sizeof(dbg_uart_suffix_default);

/// maximum size of debug output in binary format
static const uint16_t dbg_max_out_binary_size =  12;
/// maximum size of debug output in text format
static const uint16_t dbg_max_out_string_size = 128;

////////////////////
// implementation //
////////////////////

void dbg_init() {
  uc_uart_init();
}

void dbg_cycle() {
  uc_uart_cycle();
}

void dbg_process(enum dbg_level_e lvl, const struct dbg_msgspec_s *msgspec, ...) {
  va_list argptr;
  va_start(argptr, msgspec);
  dbg_vprocess(lvl, msgspec, argptr);
  va_end(argptr);
}

static void dbg_vprocess(enum dbg_level_e lvl, const struct dbg_msgspec_s *msgspec, const va_list argptr) {
  dbg_voutput(dbg_active_channels, lvl, msgspec, argptr);
}

static void dbg_output(dbg_channel_spec_t dest_channels, enum dbg_level_e lvl, const struct dbg_msgspec_s *msgspec, ...) {
  va_list argptr;
  va_start(argptr, msgspec);
  dbg_voutput(dest_channels, lvl, msgspec, argptr);
  va_end(argptr);
}

static void dbg_voutput(dbg_channel_spec_t dest_channels, enum dbg_level_e lvl, const struct dbg_msgspec_s *msgspec, const va_list start_argptr) {

  const uint8_t errcode = msgspec->errcode;
  const size_t *arg_sizes = msgspec->arg_sizes;
  const uint8_t args_cnt = msgspec->args_cnt;

  if (dbg_is_binary_active(dest_channels)) {
    uint8_t bin_buf[dbg_max_out_binary_size];
    uint8_t bin_buf_size = 0;
    
    va_list argptr;
    va_copy(argptr, start_argptr);
    
    for (uint8_t i = 0; i < args_cnt; ++i) {

      if (bin_buf_size + arg_sizes[i] >= sizeof(bin_buf)) {
	// TODO signal error state?
	break;
      }

      switch (arg_sizes[i]) {
      case 1:
	*((uint8_t *)&(bin_buf[bin_buf_size])) = va_arg(argptr, uint16_t);
	break;
      case 2:
	*((uint16_t*)&(bin_buf[bin_buf_size])) = va_arg(argptr, uint16_t);
	break;
      case 4:
	*((uint32_t*)&(bin_buf[bin_buf_size])) = va_arg(argptr, uint32_t);
	break;
      default:
	// TODO signal error state?
	memset(&(bin_buf[bin_buf_size]), 0x00, arg_sizes[i]);
      } // switch
      
      bin_buf_size += arg_sizes[i];
    } // for


    if (dest_channels | DBG_CH_BUFFER) {
      dbg_buf_add(lvl, msgspec, bin_buf, bin_buf_size);
    }

    if ((dest_channels | DBG_CH_UART) && (dbg_uart_code)) {
      dbg_output_uart_bin(errcode, bin_buf, bin_buf_size);
    }

    va_end(argptr);
  } // dbg_is_binary_active(dest_channels)

  if (dbg_is_string_active(dest_channels)) {
    dbg_voutput_string(dest_channels, lvl, msgspec->format, start_argptr);
  }
  
}

static inline bool dbg_is_binary_active(dbg_channel_spec_t dest_channels) {
  return
    (dest_channels | DBG_CH_BUFFER)
    ||
    ((dest_channels | DBG_CH_UART) && (dbg_uart_code))
    ;
}

static inline bool dbg_is_string_active(dbg_channel_spec_t dest_channels) {
  return
    (dest_channels | DBG_CH_KEYS)
    ||
    ((dest_channels | DBG_CH_UART) && (!dbg_uart_code))
    ;
}

static void dbg_output_uart_bin(uint8_t errcode, uint8_t *bin_buf, uint8_t bin_buf_size) {
  if (dbg_uart_prefix_size) {
    uc_uart_send_blob(dbg_uart_prefix, dbg_uart_prefix_size);
  }
  uc_uart_send_char(errcode);
  if (dbg_uart_payload) {
    uc_uart_send_blob(bin_buf, bin_buf_size);
  }
  if (dbg_uart_suffix_size) {
    uc_uart_send_blob(dbg_uart_suffix, dbg_uart_suffix_size);
  }
}

void dbg_output_string(dbg_channel_spec_t dest_channels, enum dbg_level_e lvl, const char *fmtstr, ...) {
  va_list argptr;
  va_start(argptr, fmtstr);
  dbg_voutput_string(dest_channels, lvl, fmtstr, argptr);
  va_end(argptr);
}

// enqueue symbols from string: TODO
// enqueue the key codes that will cause the characters from the given string to appear as input on the host to the queue of keycodes to be sent to the host.
static inline void hc_enq_syms_from_str(const char *str_buf, uint8_t strlen) { /* TOD */ }

static void dbg_voutput_string(dbg_channel_spec_t dest_channels, enum dbg_level_e lvl, const char *fmtstr, va_list argptr) {
  char str_buf[dbg_max_out_string_size];
  int strlen = vsnprintf(str_buf, dbg_max_out_string_size, fmtstr, argptr);
  
  if (dest_channels | DBG_CH_KEYS) {
    hc_enq_syms_from_str(str_buf, strlen);
  }
  
  if ((dest_channels | DBG_CH_UART) && (!dbg_uart_code)) {
    if (dbg_uart_prefix_size) {
      uc_uart_send_blob(dbg_uart_prefix, dbg_uart_prefix_size);
    }
    uc_uart_send_blob((uint8_t*) str_buf, strlen);      
    if (dbg_uart_suffix_size) {
      uc_uart_send_blob(dbg_uart_suffix, dbg_uart_suffix_size);
    }
  }
}

#if 0 // TODO

uint32_t dbg_buffer_ovfl = 0;
dbg_define_msg(dbg_buffer_ovfl, 0xFF,
	       "debug msg buffer overflown by %i bytes",
	       sizeof(dbg_buffer_ovfl)
	       )

const uint8_t dbg_max_msg_arg_cnt = 8;

void dbg_buf_add(enum dbg_level_e lvl, const struct dbg_msgspec_s *msg, uint8_t *bin_buf, uint8_t bin_buf_size) {
  assert(msg->args_total_size, bin_buf_size);
  ind_signal(IND_SIG_DBG_MSG_BUF);
  dbg_buf_push_char(lvl);
  dbg_buf_push_ptr(msg);
  dbg_buf_push_blob(bin_buf, msg->args_total_size);
}

void dbg_flush_buffer(dbg_channel_spec_t dest_channels) {
  dest_channels &= (~DBG_CH_BUFFER); // ignore buffer channel
  
  if (dbg_buffer_ovfl) {
    dbg_channel_spec_t active_channels_restore = dbg_active_channels;
    dbg_active_channels = dest_channels;
    dbg_warn(dbg_buffer_ovfl, dbg_buffer_ovfl);
    dbg_active_channels = active_channels_restore;
  }

  while (!dbg_buf_empty()) {
    uint8_t lvl = dbg_buf_pop_char();
    const struct dbg_msgspec_s *msg = dbg_buf_pop_ptr();

    char bin_buf[dbg_max_out_binary_size];
    dbg_buf_pop_blob(&bin_buf, msg->args_total_size);

    if ((dest_channel | DBG_CH_UART) && (dbg_uart_code)) {
      dbg_output_uart_bin(msg->errcode, bin_buf, msg->args_total_size);
    }

    if (dbg_is_string_active()) {
      // XXX creating function invokation arguments from binary data may
      // have platform specific aspects (litte endian vs. big endian and
      // such). => extract to a controller specific function located in
      // ucontroller_*.h
      uint32_t args[dbg_max_msg_arg_cnt];
      uint8_t bin_buf_cursor = bin_buf;
    
      for (uint8_t arg_idx = 0; arg_idx < msg->arg_cnt; ++arg_idx) {
	args[arg_idx] = 0;
#if 0
	assert(msg->args_sizes[arg_idx] <= sizeof(args[arg_idx]));
	dbg_buf_pop_blob(&args[arg_idx], msg->args_sizes[arg_idx]);
#elsif 0
	for (uint8_t byte = 0; byte < msg->args_sizes[arg_idx]; ++byte) {
	  args[arg_idx] |= dbg_buf_pop_char() << (8 * byte);
	}
#else
	for (uint8_t byte = 0; byte < msg->args_sizes[arg_idx]; ++byte) {
	  args[arg_idx] |= (*bin_buf_cursor) << (8 * byte);
	  ++bin_buf_cursor;
	}	
#endif
      }
      dbg_output_string(dest_channels, lvl, msg->format,
		 // number of arguments in next line must match dbg_max_msg_arg_cnt !!
		 args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]
		 );
    } // dbg_is_string_active()
  } // while (!dbg_buf_empty())

} // dbg_flush_buffer

#else

void dbg_buf_add(enum dbg_level_e lvl, const struct dbg_msgspec_s *msg, uint8_t *bin_buf, uint8_t bin_buf_size) {}

#endif
