#ifndef _PANIC_H
#define _PANIC_H

#include "../include/defs.h"
#include "../cpu/interrupts.h"

#define panic(a)    invoke_panic(0x0, __FILE__, __func__, __LINE__, a)
#define cpanic(a,b) invoke_panic(a, __FILE__, __func__, __LINE__, b)
#define hcf(iframe) hcf_real(iframe, __FILE__, __func__, __LINE__)

void invoke_panic(u32 code, char *file, const char *scope, int line, char *msg);
void hcf_real(x86_extended_interrupt_frame_t* iframe, char *file, const char *scope, int line);

#endif /* _PANIC_H */
