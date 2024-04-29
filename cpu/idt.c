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
  idt_gen_entry(&global_idt[0], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[1], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[2], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[3], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[4], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[5], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[6], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[7], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[8], (u32)interrupt_handler_err, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[9], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xa], (u32)interrupt_handler_err, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xb], (u32)interrupt_handler_err, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xc], (u32)interrupt_handler_err, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xd], (u32)interrupt_handler_err, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xe], (u32)interrupt_handler_err, KSEG, IDT_INTERRUPT_GATE_ATTR);
  idt_gen_entry(&global_idt[0xf], (u32)interrupt_handler_generic, KSEG, IDT_INTERRUPT_GATE_ATTR);

}

