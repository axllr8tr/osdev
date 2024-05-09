// Compatibility shims to be used until libc is half-working
// still uses kernel-side apis though

#include "include/defs.h"
#include "include/api.h"
#include <stdarg.h>

static void printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  kvprintf(fmt, ap);
  va_end(ap);
}

static void cprintf(u8 col, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  kcvprintf(col, fmt, ap);
  va_end(ap);
}

static void unsyscall(u32 eax, u32 ebx, u32 ecx, u32 edx) {
  ksyscall(eax, ebx, ecx, edx);
}

