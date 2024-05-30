// syscalls!

#include "../defs.h"

void unsyscall(u32 eax, u32 ebx, u32 ecx, u32 edx) {
  asm volatile (
    "mov %0, %%eax\n\t"
    "mov %1, %%ebx\n\t"
    "mov %2, %%ecx\n\t"
    "mov %3, %%edx\n\t"
    "int $0x7f"
    :
    : "g" (eax), "g" (ebx), "g" (ecx), "g" (edx)
    : "%eax", "%ebx", "%ecx", "%edx"
  );
} // unstandard system call

int read(int fd, char *data, size_t limit) {
  unsyscall(0, (u32)fd, (u32)data, (u32)limit);
  return 0; // INFO: errno some time in the future
}

int write(int fd, const char *data, size_t limit) {
  unsyscall(1, (u32)fd, (u32)data, (u32)limit);
  return 0; 
}
