#include "idt.h"
#include "interrupts.h"
#include "../include/defs.h"

#define KSEG 0x08


idt_descriptor_pointer_t global_idt_pointer;
__attribute__((aligned(0x10))) idt_gate_descriptor_t global_idt[256];

static void idt_gen_entry(idt_gate_descriptor_t *idt, u32 offset, u16 ss, u8 attributes) {
  idt->offset_low = offset & 0xffff;
  idt->segment_selector = ss;
  idt->reserved = 0x00; // better be explicit
  idt->attributes = attributes;
  idt->offset_high = (offset >> 16) & 0xffff;
}

void idt_setup_exception_handlers() {
  global_idt_pointer.base = (u32)global_idt;
  global_idt_pointer.limit = (sizeof(idt_gate_descriptor_t) * 256) - 1;
  idt_gen_entry(&global_idt[0], (u32)_isr0, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[1], (u32)_isr1, KSEG, IDT_TRAP_GATE_ATTR);
  idt_gen_entry(&global_idt[2], (u32)_isr2, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[3], (u32)_isr3, KSEG, IDT_TRAP_GATE_ATTR);
  idt_gen_entry(&global_idt[4], (u32)_isr4, KSEG, IDT_TRAP_GATE_ATTR);
  idt_gen_entry(&global_idt[5], (u32)_isr5, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[6], (u32)_isr6, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[7], (u32)_isr7, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[8], (u32)_isr8, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[9], (u32)_isr9, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xa], (u32)_isr10, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xb], (u32)_isr11, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xc], (u32)_isr12, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xd], (u32)_isr13, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xe], (u32)_isr14, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xf], (u32)_isr15, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x10], (u32)_isr16, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x11], (u32)_isr17, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x12], (u32)_isr18, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x13], (u32)_isr19, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x14], (u32)_isr20, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x15], (u32)_isr21, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x16], (u32)_isr22, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x17], (u32)_isr23, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x18], (u32)_isr24, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x19], (u32)_isr25, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x1a], (u32)_isr26, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x1b], (u32)_isr27, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x1c], (u32)_isr28, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x1d], (u32)_isr29, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x1e], (u32)_isr30, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x1f], (u32)_isr31, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x7f], (u32)_isr127, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x20], (u32)_irq0, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x21], (u32)_irq1, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0x22], (u32)_irq2, KSEG, IDT_INTERRUPT_GATE_ATTR);
}

