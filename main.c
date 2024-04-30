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
#include "cpu/gdt.h"
#include "cpu/idt.h"


int kmain(size_t mboot_ptr, u32 mboot_mag, u32p esp) {
  asm volatile ("cli");
  gdt_setup_flat();
  gdt_deploy_flat();
  idt_setup_exception_handlers();
  idt_deploy();
  asm volatile ("sti");
  fix_pic();

  vga_init_term();

  scode_t a, b;
  keyevent_t a1, b1;


  printf("Hello, world!\n");

  do { 
    receive_keystroke(&b);
    keystroke_to_keyevent(&b, &b1);
    if(b.rawScancode != a.rawScancode) {
      vga_init_term();
      printf("ks rl %B pr %B sc %x fl %b lk %b", !b1.pressed, b1.printable, b1.scancode.rawScancode, b1.modifiers, b1.locks);
      if (b1.printable) {
        printf(" ch %c\n", b1.pchar);
      }
    }
    a = b;
    a1 = b1;
  } while (true);

  return 0;
}
