#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "../include/defs.h"

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();
extern void _isr32();
extern void _isr126();
extern void _isr127();
extern void _isr254();
extern void _isr255();
extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

// not sure if this is even right
typedef struct iframe {
  u32 vector;
  u32 err;
  u32 eip;
  u32 cs;
  u32 eflags;
  u32 esp;
  u32 ss;
} x86_simple_interrupt_frame_t; 

typedef struct eiframe {
  u32 gs, fs, es, ds;
  u32 esi, edi, ebp, esp, ebx, edx, ecx, eax;
  u32 vector;
  u32 err;
  u32 eip, cs, eflags;
  u32 iret_esp, iret_ss;
} __attribute__((packed)) x86_extended_interrupt_frame_t;

typedef void (*irq_handler_t)(x86_extended_interrupt_frame_t*);

// interrupt handler utils
void irq_handler_install(u8 irq, irq_handler_t handler);
void irq_handler_uninstall(u8 irq);


#endif /* _INTERRUPTS_H */
