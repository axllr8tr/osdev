#include "../include/defs.h"
#include "syscalls.h"
#include "../video/video.h"
#include "../baseio/printf.h"
#include "../utils/io_ports.h"
#include "../cpu/interrupts.h"

// inspired by klange/toaruos branch old_kernel_shell (not straight-up stolen I hope)


static void syscall_hang()  {
  vga_init_term();
  cprintf(0x2f, "Issued syscall 0 (hang)\n" "The system will now be halted.");
  asm volatile ("hlt");
}

static void syscall_irq_handler_install(u32 irq, irq_handler_t handler) {
  irq_handler_install(irq, handler);
}

static void syscall_irq_handler_uninstall(u32 irq) {
  irq_handler_uninstall(irq);
}


const u32p nonstandard_system_calls[] = {
  (u32p)syscall_hang,
  (u32p)syscall_irq_handler_install,
  (u32p)syscall_irq_handler_uninstall
};

u32 execute_nonstandard_system_call(u32 eax, u32 ebx, u32 ecx, u32 edx) {
  u32p syscall_function = nonstandard_system_calls[eax];
  u32 ret = 0x00;
  asm volatile (
    "push %1\n"
    "push %2\n"
    "push %3\n"
    "call *%4\n"
    "pop %%ebx\n"
    "pop %%ebx\n"
    "pop %%ebx\n"
    : "=a" (ret) : "r" (edx), "r" (ecx), "r" (ebx), "r" (syscall_function)
  );
  ret = *syscall_function;
  return ret;
}


