


int main(void) {
  init();
  while (true) {
    await_next_cycle();
    pnl_sync_io_all();
    process_keystate_changes();
    progress_out_keyseq();
  };
  return 0;
}

void init() {
  uc_init();
  pnl_init_io_all();
}
