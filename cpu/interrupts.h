#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "../include/defs.h"

typedef struct iframe {
  u16 ip;
  u16 cs;
  u16 flags;
  u16 sp;
  u16 ss;
} x86_simple_interrupt_frame_t;

typedef struct eiframe {
  u32 eax;
  u32 ebx;
  u32 ecx;
  u32 edx;
  u32 esp;
  u32 ebp;
  u32 esi;
  u32 edi;
  u32 eip;
  u32 eflags; 
  u16 cs;
  u16 ss;
  u16 ds;
} x86_extended_interrupt_frame_t;

void interrupt_handler_generic(x86_simple_interrupt_frame_t*);
void interrupt_handler_err(x86_simple_interrupt_frame_t*);

#endif /* _INTERRUPTS_H */
