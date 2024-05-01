#ifndef _KERNEL_SYSCALLS
#define _KERNEL_SYSCALLS

#include "../include/defs.h"

u32 execute_nonstandard_system_call(u32 eax, u32 ebx, u32 ecx, u32 edx, u32 esi, u32 edi); // <-- used in cpu/interrupts.c to invoke system call from vector 0x7f
u32 nsyscall(u32 eax, u32 ebx, u32 ecx, u32 edx, u32 esi, u32 edi); // <-- used anywhere else _in kernelspace_ to trigger the syscall


#endif /* _KERNEL_SYSCALLS */
