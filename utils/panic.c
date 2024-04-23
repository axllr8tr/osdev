#include "../include/baseio.h"
#include "panic.h"
#include "../video/video.h"
#include "../baseio/printf.h"

static void halt() {
  asm inline ("hlt");
}

// invoke_panic(...) is invoked with panic(msg) and cpanic(code, msg) macros
// do not invoke manually as this defeats the whole purpose of these args!!!!
void invoke_panic(u32 code, char *file, const char *scope, int line, char *msg) {
  vga_fill_screen(vga_gen_entry(' ', 0x55)); // purple void
  x = 0; y = 0;
  cprintf(0x5f, "\nPanic!\n");
  if (code) cprintf(0x5f, "Error code: 0x%x\n", code);
  cprintf(0x5f, "\nIn file %s on line %u in function %s: %s\n", file, line, scope, msg);
  cprintf(0x5f, "\nThat's about it. Staying here until hardware reset.");
  // printf("%s", "oranges");
  halt();
}



