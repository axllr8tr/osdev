#ifndef _KERNEL_SYSCALLS
#define _KERNEL_SYSCALLS

#include "../include/defs.h"

u32 execute_nonstandard_system_call(u32 eax, u32 ebx, u32 ecx, u32 edx);
u32 nsyscall(u32 eax, u32 ebx, u32 ecx, u32 edx); 

#endif /* _KERNEL_SYSCALLS */
