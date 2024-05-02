#ifndef _USERSPACE_API
#define _USERSPACE_API

// to become actual userspace later

#include "defs.h"

void unsyscall(u32, u32, u32, u32);
void printf(char *fmt, ...);
void cprintf(u8 col, char *fmt, ...);
void putc(u8 chr, u8 col);
void ucputc(u8 chr);
char getch();

#endif /* _USERSPACE_API */
