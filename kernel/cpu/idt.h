#ifndef _IDT_H
#define _IDT_H

#include "../include/defs.h"

#define IDT_INTERRUPT_GATE_ATTR 0x8e
#define IDT_TRAP_GATE_ATTR      0x8f
#define IDT_TASK_GATE_ATTR      0x85 // not often used, according to osdev wiki

// this header is ONLY for the IDT, everything else interrupt-related is in interrupts.h

typedef struct idesc {
  u16 offset_low;
  u16 segment_selector;
  u8 reserved; // aka must be 0
  u8 attributes; // bits 0-3 gate type, 4 always 0, 5-6 priviliges, 7 always 1
  u16 offset_high;
} __attribute__((packed)) idt_gate_descriptor_t;

typedef struct idtptr {
  u16 limit;
  u32 base;
} __attribute__((packed)) idt_descriptor_pointer_t;

void idt_setup_exception_handlers();
void idt_deploy();

#endif /* _IDT_H */
