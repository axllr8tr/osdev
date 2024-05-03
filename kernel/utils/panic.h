#ifndef _PANIC_H
#define _PANIC_H

#include "../include/defs.h"
#include "../cpu/interrupts.h"

#define panic(a)    invoke_panic(0x0, __FILE__, __func__, __LINE__, a)
#define cpanic(a,b) invoke_panic(a, __FILE__, __func__, __LINE__, b)

void invoke_panic(u32 code, char *file, const char *scope, int line, char *msg);
void hcf(x86_extended_interrupt_frame_t* iframe);

#endif /* _PANIC_H */
