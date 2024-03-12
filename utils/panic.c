#include "../include/baseio.h"
#include "panic.h"
#include "../video/video.h"
#include "../baseio/printf.h"

static void halt() {
  asm inline ("hlt");
}

void invoke_panic(u32 code, char *file, const char *scope, int line, char *msg) {
  vga_fill_screen(vga_gen_entry(' ', 0x5f));
  x = 0; y = 0;
  printf("\nPanic!\n");
  if (code) printf("Error code: 0x%x\n", code);
  printf("%s:%u in function %s: %s", file, line, scope, msg);
  // printf("%s", "oranges");
  halt();
}



