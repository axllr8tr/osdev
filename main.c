#include <stdint.h>
#include "include/defs.h"
// #include "include/input.h"
#include "include/panic.h"
#include "include/llhw.h"
#include "video/video.h"
#include "baseio/uprint.h"
#include "baseio/printf.h"
#include "utils/panic.h"
#include "llhw/cpuid.h"
#include "llhw/8042_ps2.h"
#include "llhw/8259_pic.h"
#include "input/kbd.h"

int kmain(size_t mboot_ptr, u32 mboot_mag, u32p esp) {
  vga_init_term();

  u32 scode = 0x0;

  fix_pic();

  printf("Hello, world!\n");
 
  do { 
    scode = ps2d_receive_data();
    if ((scode & 0xff) < 0x80) printf("%c", kbd_layout_us_qwerty[*(u8p)&scode]);
} while (true);

  return 0;
}
