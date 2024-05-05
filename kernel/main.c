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
  cprintf(++counter & 0xf, ".");
  if (!(counter % 100)) {
    cprintf(0x0e, "You are outside userspace.");
  }
}

int kmain() {
  vga_init_term();
  
  cprintf(0x0f, "Welcome to thos!\n");

  fix_pic();
  cprintf(0x0a, "[cpu] Remapped PICs: m -> 0x20, s -> 0x28\n");

  asm volatile ("cli");
  cprintf(0x0a, "[cpu] Interrupts disabled\n");

  gdt_setup_flat();
  gdt_deploy_flat();
  cprintf(0x0a, "[cpu] GDT installed\n");
  idt_setup_exception_handlers();
  idt_deploy();
  cprintf(0x0a, "[cpu] IDT installed\n");

  asm volatile ("sti");
  cprintf(0x0a, "[cpu] Interrupts enabled\n");



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
