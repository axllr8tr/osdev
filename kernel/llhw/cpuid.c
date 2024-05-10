#include "../include/defs.h"
#include "../logging/log.h"
#include "../utils/mem.h"
#include "cpuid.h"
#include <cpuid.h>

void cpuid_execute(u32 op, u32 *eax, u32 *ebx, u32 *ecx, u32 *edx) {
  kdebug_log(DEBUG "cpuid: pre: op %x eax %x ebx %x ecx %x edx %x", op, *eax, *ebx, *ecx, *edx);
  __cpuid(op, *eax, *ebx, *ecx, *edx);
  kdebug_log(DEBUG "cpuid: post: op %x eax %x ebx %x ecx %x edx %x", op, *eax, *ebx, *ecx, *edx);
}

void cpuid_get_vendor(char *dest) {
  u32 eax = 0, ebx = 0, ecx = 0, edx = 0;
  u8 locidx = 0;
  cpuid_execute(0, &eax, &ebx, &ecx, &edx);
  u8p st = (u8p)&ebx, mi = (u8p)&edx, en = (u8p)&ecx;
  for (locidx = 0; locidx < 4; locidx++) {
    *dest++ = st[locidx];
  }
  for (locidx = 0; locidx < 4; locidx++) {
    *dest++ = mi[locidx];
  }
  for (locidx = 0; locidx < 4; locidx++) {
    *dest++ = en[locidx];
  } // genuine jank
  *dest = 0; // nul
}
