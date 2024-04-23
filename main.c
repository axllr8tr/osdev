#include <stdint.h>
#include "include/defs.h"
#include "include/input.h"
#include "include/panic.h"
#include "include/llhw.h"
#include "video/video.h"
#include "baseio/uprint.h"
#include "baseio/printf.h"
#include "utils/panic.h"
#include "llhw/cpuid.h"

int kmain(size_t mboot_ptr, u32 mboot_mag, u32p esp) {
  vga_init_term();

  printf("Hello, world!\n");
 
  return 0;
}
