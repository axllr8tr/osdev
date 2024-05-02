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
#include "utils/io_ports.h"

int kmain() {
  fix_pic();
  asm volatile ("cli");
  gdt_setup_flat();
  gdt_deploy_flat();
  idt_setup_exception_handlers();
  idt_deploy();
  asm volatile ("sti");

  vga_init_term();


  extern void shell_entry();
  shell_entry();

  while (true) {
    printf("you are now outside the userspace... ");
  }
  return 0;
}
