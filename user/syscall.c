#include "include/defs.h"

void unsyscall(u32 eax, u32 ebx, u32 ecx, u32 edx, u32 esi, u32 edi, u32 ebp) {
  asm volatile (
    "mov %0, %%eax\n\t"
    "mov %1, %%ebx\n\t"
    "mov %2, %%ecx\n\t"
    "mov %3, %%edx\n\t"
    "mov %4, %%esi\n\t"
    "mov %5, %%edi\n\t"
    "int $0x7f"
    :
    : "g" (eax), "g" (ebx), "g" (ecx), "g" (edx), "g" (esi), "g" (edi)
    : "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi"
  );
}
