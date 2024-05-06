#ifndef _USERSPACE_API
#define _USERSPACE_API

// to become actual userspace later

#include "defs.h"

// non-standard syscall from userspace
void unsyscall(u32, u32, u32, u32); 

// formatted print
void printf(char *fmt, ...); 

// formatted print (with color)
void cprintf(u8 col, char *fmt, ...); 

// put character onto terminal
void putc(u8 chr, u8 col); 

// put character onto terminal, using next one's color
void ucputc(u8 chr); 

// get character from keyboard
char getch(); 

#endif /* _USERSPACE_API */
