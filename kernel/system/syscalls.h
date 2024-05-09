#ifndef _KERNEL_SYSCALLS
#define _KERNEL_SYSCALLS

#include "../include/defs.h"

int ksyscall_install_full();
int ksyscall(u32 eax, u32 ebx, u32 ecx, u32 edx); 

#endif /* _KERNEL_SYSCALLS */
