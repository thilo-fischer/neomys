/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * Generic parts and inclusion of specific debug implementation.
 */


enum dbg_level_e dbg_threshold = DBG_WARN;

uint8_t dbg_active_channels = DBG_CH_BUFFER;



bool dbg_uart_code = true; ///< whether to send just error codes via
			   ///  UART (in contrast to sending string
			   ///  corstructed form the printf-alike
			   ///  format string and optional additional
			   ///  arguments)
bool dbg_uart_payload = true; ///< when dbg_uart_code is active: send
			      ///  binary data of additional arguments

bool dbg_uart_add_prefix = false; ///< prepend a certain byte pattern to the debug output
char dbg_uart_prefix = '\0';

bool dbg_uart_add_suffix = false; ///< append a certain byte pattern to the debug output
char dbg_uart_suffix = '\0';



static const uint16_t dbg_max_out_binary_size =  12;
static const uint16_t dbg_max_out_string_size = 128;

static void dbg_vprocess(enum dbg_level_e lvl, uint8_t errcode, char *format, arg_sizes[], arg_sizes_cnt, const va_list start_argptr);

void dbg_set_threshold(enum dbg_level_e t) {
  threshold = t;
}


void dbg_process(enum dbg_level_e lvl, uint8_t errcode, char *format, arg_sizes[], arg_sizes_cnt, ...) {
  va_list argptr;
  va_start(argptr, format);
  dbg_process(lvl, errcode, format, argsizes, arg_sizes_cnt, argptr);
  va_end(argptr);
}

static void dbg_vprocess(enum dbg_level_e lvl, uint8_t errcode, char *format, arg_sizes[], arg_sizes_cnt, const va_list start_argptr) {

  if (dbg_is_binary_active()) {
    char bin_buf[dbg_max_out_binary_size];
    uint8_t bin_buf_cnt = 0;
    
    va_list argptr;
    va_copy(argptr, start_argptr);
    
    for (uint8_t i = 0; i < arg_sizes_cnt; ++i) {

      if (bin_buf_cnt + arg_sizes[i] >= sizeof(bin_buf)) {
	break;
      }

      switch (arg_sizes[i]) {
      case 1:
	(uint8_t *) &(bin_buf[bin_buf_cnt]) = va_arg(argptr, uint8_t);
	break;
      case 2:
	(uint16_t*) &(bin_buf[bin_buf_cnt]) = va_arg(argptr, uint16_t);
	break;
      case 4:
	(uint32_t*) &(bin_buf[bin_buf_cnt]) = va_arg(argptr, uint32_t);
	break;
      default:
	// TODO signal error state?
	memset(&(bin_buf[bin_buf_cnt]), 0x00, arg_sizes[i])
      }
      
      bin_buf_cnt += arg_sizes[i];
    }


    if (dbg_active_channels | DBG_CH_BUFFER) {
      dbg_buf_add(lvl, errcode, bin_buf, bin_buf_cnt);
    }

    
    if ((dbg_active_channels | DBG_CH_UART) && (dbg_uart_code)) {
      if (dbg_uart_add_prefix) {
	uc_uart_send_char(dbg_uart_prefix);
      }
      uc_uart_send_char(errcode);
      if (dbg_uart_payload) {
	uc_uart_send_blob(bin_buf, bin_buf_cnt);
      }
      if (dbg_uart_add_suffix) {
	buffer[buf_size++] = dbg_uart_suffix;
      }
    }
  }

  if (dbg_is_string_active()) {
    char str_buf[dbg_max_out_string_size];
    
    va_list argptr;
    va_copy(argptr, start_argptr);

    int strlen = vsnprintf(str_buf, dbg_max_out_string_size, format, argptr);

    if (dbg_active_channels | DBG_CH_KEYS) {
      hc_enq_syms_from_str(str_buf, strlen);
    }

    if ((dbg_active_channels | DBG_CH_UART) && (!dbg_uart_code)) {
      uc_uart_send_blob(str_buf, strlen);      
    }
  }
  
}


void dbg_output_buffer() {
  while (!dbg_buf_empty()) {
    uint8_t lvl = dbg_buf_pop_char();
    uint8_t errcode = dbg_buf_pop_char();
    uint8_t arg_cnt = dbg_buf_pop_char();

    uint32_t args[dbg_max_arg_cnt];
    void *bin_arg_ptr = dbg_buf_cursor();
    
    for (uint8_t i = 0; i < arg_cnt; ++i) {
      args[i] = dbg_buf_pop_char();
    }
    dbg_output(
	       lvl, errcode, format,
	       bin_arg_ptr,
	       bin_arg_size,
	       args[0], args[1], args[2], args[3], args[4], args[5], args[6]
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
