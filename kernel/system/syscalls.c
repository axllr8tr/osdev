#include "../include/defs.h"
#include "syscalls.h"
#include "../video/video.h"
#include "../baseio/printf.h"

// inspired by klange/toaruos branch old_kernel_shell (not straight-up stolen I hope)


void syscall_hang()  {
  vga_init_term();
  cprintf(0x2f, "Bye-bye~");
  asm volatile ("hlt");
}

static void syscall_get_keyboard_input(char *dest) {
  // nothing for now //
}

u32p nonstandard_system_calls[] = {
  (u32p)syscall_hang,
  (u32p)syscall_get_keyboard_input
};

u32 execute_nonstandard_system_call(u32 eax, u32 ebx, u32 ecx, u32 edx, u32 esi, u32 edi) {
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
    : "=a" (ret) : "r" (ecx), "r" (ebx), "r" (eax), "r" (syscall_function)
  );
  return ret;
}


