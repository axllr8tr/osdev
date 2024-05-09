#ifndef _USERSPACE_API
#define _USERSPACE_API

// to become actual userspace later

#include "defs.h"
#include <stdarg.h>

void ksyscall(u32, u32, u32, u32); 
void kprintf(const char *fmt, ...); 
void kvprintf(const char *fmt, va_list ap);
void kcprintf(u8 col, const char *fmt, ...);
void kcvprintf(u8 col, const char *fmt, va_list ap);
void putc(u8 chr, u8 col);
void ucputc(u8 chr); 
char getch(); 

#endif /* _USERSPACE_API */
