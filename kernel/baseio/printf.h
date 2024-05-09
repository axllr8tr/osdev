#ifndef __PRINTF_H
#define __PRINTF_H

#include "../include/defs.h"

extern void k_vsnprintf(char *, size_t, const char *, va_list);
extern void kvsnprintf_(char *, size_t, const char *, ...);

// using write() for output
extern void kvprintf(const char *, va_list);
extern void kprintf(const char *, ...);
extern void kcprintf(u8, const char *, ...);

// using tprint() directly
extern void kvprintf_c(const char *, va_list);
extern void kprintf_c(const char *, ...);
extern void kcprintf_c(u8, const char *, ...);


#endif /* __PRINTF_H */
