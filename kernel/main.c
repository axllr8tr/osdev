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
#include "cpu/interrupts.h"
#include "ansi_test.h"

u32 counter = 0;

void left_userspace() {
  cprintf(0x07, "Tick %u\n", counter++);
  if (!(counter % 100)) {
    cprintf(0x0e, "You are outside userspace.\n");
  }
}

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
  
  // extern void tprint(const char *);
  // tprint(
  //   "\e[32m\e[4CHello, world!\n"
  //   "\e[32m\e[4CHello, world!\n"
  //   "\e[32m\e[4CHello, world!\n"
  //   "\e[32m\e[4CHello, world!\n"
  //   "\e[32m\e[4CHello, world!\n"
  // );

  irq_handler_install(0, left_userspace);
  
  while (true) {
  }
  return 0;
}
