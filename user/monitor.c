#include "include/api.h"

static char curchar = 0;
u32 last_location = 0, store = 0;
u8 mode = 0;

void kbd_handler_monitor() {
  curchar = getch();
}

void monitor(void) {
  printf("stupid x86 monitor\n");
  unsyscall(1, 1, (u32)kbd_handler_monitor, 0); // set up local keyboard irq
  printf("will be done in the future!\n");
  
}
