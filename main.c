#include <stdint.h>
#include "include/defs.h"
#include "include/input.h"
#include "include/panic.h"
#include "include/llhw.h"
#include "video/video.h"
#include "baseio/uprint.h"
#include "baseio/printf.h"

int kmain(size_t mboot_ptr, u32 mboot_mag, u32p esp) {
  vga_init_term();
//  uprint("Hello, world!\n");
  char x[256] = {0};


  u32 test_cases[] = {
    0, 0x7f, 0xff, 0x100, 0x7fff, 0xffff, 0x10000, 0x7fffffff, 0xffffffff
  };

  for (u8 i = 0; i < 9; i++) {  
    vsnprintf_(&x[0], 256, "Test case %u => %x\n", i, test_cases[i]);
    uprintc(x, 0xf0);
  }

//  _itoa(x, 255, 0xaabbccddeeff, 16, false);
  return 0;
}
