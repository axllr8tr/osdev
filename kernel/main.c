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
  counter++;
  kcprintf(counter & 0xf, "%u ", counter);
}

int kmain(void) {
  vga_init_term();

  kdebug_log(INFO "Welcome to thos!");

  char cpuid_vendor[33] = {0};
  char cpuid_brand_string[49] = {0};

  cpuid_get_vendor(cpuid_vendor);
  cpuid_get_brand_string(cpuid_brand_string);
  kdebug_log(INFO "CPU vendor is %s", cpuid_vendor);
  kdebug_log(INFO "CPU is %s", cpuid_brand_string);

  fix_pic();

  asm volatile ("cli");
  gdt_setup_flat();
  gdt_deploy_flat();
  kdebug_log(DEBUG "installed GDT");
  idt_setup_exception_handlers();
  idt_deploy();
  kdebug_log(DEBUG "installed IDT");
  asm volatile ("sti");

  ksyscall_install_full();

  extern void shell_entry(void);
  shell_entry();

  irq_handler_install(0, left_userspace);
  
  kdebug_log(SOFTPANIC "exited userspace");

  while (true) {

  }
  return 0;
}
