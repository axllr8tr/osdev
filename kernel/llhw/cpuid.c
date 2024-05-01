#include "../include/defs.h"
#include "cpuid.h"
#include <cpuid.h>

void cpuid_get_vendor(char *dest) {
  u32p eax, ebx, ecx, edx;
  eax =(u32p)&dest;
  ebx =(u32p)&dest[4];
  ecx =(u32p)&dest[8];
  edx =(u32p)&dest[12];

  __cpuid(0, eax, ebx, ecx, edx);
}
