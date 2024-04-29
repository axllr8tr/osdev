#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "../include/defs.h"

// not sure if this is even right
typedef struct iframe {
  u32 eip;
  u16 cs;
  u32 eflags;
  u32 esp;
  u16 ss;
} x86_simple_interrupt_frame_t; 

typedef struct eiframe {
  u32 gs, fs, es, ds;
  u32 esi, edi, ebp, esp, ebx, edx, ecx, eax;
  u32 vector;
  u32 err;
  u32 eip, cs, eflags;
  u32 iret_esp, iret_ss;
} __attribute__((packed)) x86_extended_interrupt_frame_t;

// entry points
void interrupt_handler_generic_entry(); /* interrupts.S */
void interrupt_handler_err_entry(); /* interrupts.S */

// actual handlers
void interrupt_handler_generic(x86_extended_interrupt_frame_t*);
void interrupt_handler_err(x86_extended_interrupt_frame_t*);

#endif /* _INTERRUPTS_H */
