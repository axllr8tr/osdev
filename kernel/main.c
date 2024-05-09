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
#include "system/syscalls.h"
#include "logging/log.h"

u32 counter = 0;

void left_userspace() {
  kcprintf(++counter & 0xf, ".");
  if (!(counter % 100)) {
    kcprintf_c(0x0e, "You are outside userspace.");
  }
}

int kmain(void) {
  vga_init_term();

  kcprintf_c(0x0f, "Welcome to thos!\n");

  fix_pic();

  asm volatile ("cli");
  gdt_setup_flat();
  gdt_deploy_flat();
  kdebug_log(INFO "installed GDT");
  idt_setup_exception_handlers();
  idt_deploy();
  kdebug_log(INFO "installed IDT");
  asm volatile ("sti");

  ksyscall_install_full();

  extern void shell_entry(void);
  shell_entry();

  irq_handler_install(0, left_userspace);
  
  while (true) {

  }
  return 0;
}
