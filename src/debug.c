/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * Generic parts and inclusion of specific debug implementation.
 */

//////////////////
// declarations //
//////////////////

/// Output debug message to all currently active channels.
static void dbg_vprocess(enum dbg_level_e lvl, struct dbg_msgspec_s *msgspec, const va_list start_argptr);

/// Output debug message to all channels active in the given bitfield.
static void dbg_vprocess(enum dbg_level_e lvl, struct dbg_msgspec_s *msgspec, const va_list start_argptr, dbg_channel_spec_t dest_channels);


/////////////////
// definitions //
/////////////////

enum dbg_level_e dbg_threshold = DBG_WARN;

dbg_channel_spec_t dbg_active_channels = DBG_CH_BUFFER;

/// whether to send just error codes via UART (in contrast to sending
/// string corstructed form the printf-alike format string and
/// optional additional arguments)
bool dbg_uart_code = true;
/// when dbg_uart_code is active: send binary data of additional
/// arguments
bool dbg_uart_payload = true;

bool dbg_uart_add_prefix = false; ///< prepend a certain byte pattern to UART debug output
char dbg_uart_prefix = '\0'; ///< byte to prepend to UART debug output

bool dbg_uart_add_suffix = false; ///< append a certain byte pattern to UART debug output
char dbg_uart_suffix = '\0'; ///< byte to append to UART debug output

/// maximum size of debug output in binary format
static const uint16_t dbg_max_out_binary_size =  12;
/// maximum size of debug output in text format
static const uint16_t dbg_max_out_string_size = 128;

////////////////////
// implementation //
////////////////////

void dbg_process(enum dbg_level_e lvl, struct dbg_msgspec_s *msgspec, ...) {
  va_list argptr;
  va_start(argptr, format);
  dbg_process(lvl, msgspec, argptr);
  va_end(argptr);
}

static void dbg_vprocess(enum dbg_level_e lvl, struct dbg_msgspec_s *msgspec, const va_list start_argptr) {
  dbg_voutput(lvl, msgspec, start_argptr, dbg_active_channels);
}

static void dbg_voutput(enum dbg_level_e lvl, struct dbg_msgspec_s *msgspec, const va_list start_argptr, dbg_channel_spec_t dest_channels) {

  const uint8_t errcode = msgspec->errcode;
  const char *const format = msgspec->format;
  const uint8_t *arg_sizes = msgspec->arg_sizes;
  const uint8_t args_cnt = msgspec->args_cnt;

  if (dbg_is_binary_active(dest_channels)) {
    char bin_buf[dbg_max_out_binary_size];
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
	(uint8_t *) &(bin_buf[bin_buf_size]) = va_arg(argptr, uint8_t);
	break;
      case 2:
	(uint16_t*) &(bin_buf[bin_buf_size]) = va_arg(argptr, uint16_t);
	break;
      case 4:
	(uint32_t*) &(bin_buf[bin_buf_size]) = va_arg(argptr, uint32_t);
	break;
      default:
	// TODO signal error state?
	memset(&(bin_buf[bin_buf_size]), 0x00, arg_sizes[i]);
      } // switch
      
      bin_buf_size += arg_sizes[i];
    } // for


    if (dbg_active_channels | DBG_CH_BUFFER && to_buffer) {
      dbg_buf_add(lvl, msgspec, bin_buf, bin_buf_size);
    }

    if ((dbg_active_channels | DBG_CH_UART) && (dbg_uart_code)) {
      dbg_output_uart_bin(errcode, bin_buf, bin_buf_size);
    }
  } // dbg_is_binary_active(dest_channels)

  if (dbg_is_string_active()) {
    dbg_output_string(lvl, msgspec, start_argptr);
  }
  
}


void dbg_output_uart_bin(uint8_t errcode, char *bin_buf, uint8_t bin_buf_size) {
  if (dbg_uart_add_prefix) {
    uc_uart_send_char(dbg_uart_prefix);
  }
  uc_uart_send_char(errcode);
  if (dbg_uart_payload) {
    uc_uart_send_blob(bin_buf, bin_buf_size);
  }
  if (dbg_uart_add_suffix) {
    buffer[buf_size++] = dbg_uart_suffix;
  }
}

void dbg_output_string(enum dbg_level_e lvl, struct dbg_msgspec_s *msgspec, va_list argptr) {
  char str_buf[dbg_max_out_string_size];
  int strlen = vsnprintf(str_buf, dbg_max_out_string_size, format, argptr);
  
  if (dbg_active_channels | DBG_CH_KEYS) {
    hc_enq_syms_from_str(str_buf, strlen);
  }
  
  if ((dbg_active_channels | DBG_CH_UART) && (!dbg_uart_code)) {
    uc_uart_send_blob(str_buf, strlen);      
  }
}

#if 0 // TODO

uint32_t dbg_buffer_ovfl = 0;
dbg_define_msg(dbg_buffer_ovfl, 0xFF, "debug msg buffer overflown by %i bytes", sizeof(dbg_buffer_ovfl))

void dbg_buf_add(lvl, struct dbg_msgspec_s *msg, char *bin_buf, uint8_t bin_buf_size) {
  dbg_buf_push_char(lvl);
  dbg_buf_push_ptr(msg);
  dbg_buf_push_blob(bin_buf, bin_buf_size);
}

void dbg_flush_buffer(dbg_channel_spec_t dest_channels) {
  if (dbg_buffer_ovfl) {
    dbg_warn(dbg_buffer_ovfl, dbg_buffer_ovfl)
  }
  while (!dbg_buf_empty()) {
    uint8_t lvl = dbg_buf_pop_char();
    struct dbg_msgspec_s *msg = dbg_buf_pop_ptr();
    uint8_t arg_cnt = dbg_buf_pop_char();

    // XXX creating function invokation arguments from binary data may
    // have platform specific aspects (litte endian vs. big endian and
    // such). => extract to a controller specific function located in
    // ucontroller_*.h
    uint32_t args[dbg_max_msg_arg_cnt];
    uint8_t *bin_arg_ptr = dbg_buf_cursor();
    
    for (uint8_t arg = 0; arg < arg_cnt; ++arg) {
      for (uint8_t byte = 0; byte < msg->args_cnt; )
      args[i] = dbg_buf_pop_char();
    }
    dbg_output(
	       lvl, errcode, format,
	       bin_arg_ptr,
	       bin_arg_size,
	       args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]
	       );
    
    //uint32_t a01, a02, a03, a04, a05, a06;
    //switch (arg_cnt) {
    //case 0:
    //
    //  dbg_process(lvl, errcode, ..., a01, a02, a03, a04, a05, a06);
    //  break;
    //  
    //}
  }
}

#else

#define dbg_buf_add(...)

#endif
