#include "idt.h"
#include "interrupts.h"
#include "../baseio/uprint.h"
#include "../baseio/printf.h"
#include "../utils/panic.h"

const char *exception_messages[] = {
  "Division by zero", // 0x00
  "Debug", // 0x01
  "Non-maskable interrupt", // 0x02
  "Breakpoint", // 0x03
  "Overflow", // 0x04
  "Out of bounds", // 0x05
  "Invalid instruction", // 0x06
  "No device", // 0x07
  "Double fault", // 0x08
  "Reserved", // 0x09
  "Invalid TSS", // 0x0a
  "Segment's presence bit is 0", // 0x0b
  "SS fault", // 0x0c
  "General protection fault", // 0x0d
  "Paging fault", // 0x0e
  "Reserved", // 0x0f
  "x87 floating point exception", // 0x10
  "Alignment check failed", // 0x11
  "Machine check failed", // 0x12
  "SSE floating point exception", // 0x13
  "Virtualization exception", // 0x14
  "Control protection exception", // 0x15
  "Reserved", // 0x16
  "Reserved", // 0x17
  "Reserved", // 0x18
  "Reserved", // 0x19
  "Reserved", // 0x1a
  "Reserved", // 0x1b
  "Hypervisor injection exception", // 0x1c
  "VMM communication exception", // 0x1d
  "Security exception", // 0x1e
  "Reserved" // 0x1f
};

__attribute__((interrupt)) void interrupt_handler_generic(x86_extended_interrupt_frame_t *iframe) {
  cprintf(0x70, 
          "\nCaught an interrupt!!\n"
          "iret ss %x iret esp %x\n"
          "eflags %x cs %x eip %x\n"
          "err %x vector %x\n"
          "eax %x ecx %x edx %x ebx %x\n"
          "esp %x ebp %x edi %x esi %x\n"
          "ds %x es %x fs %x gs %x\n"
          "%s\n",
          iframe->iret_ss, iframe->iret_esp, iframe->eflags, iframe->cs, iframe->eip, iframe->err, iframe->vector, iframe->eax, iframe->ecx, iframe->edx, iframe->ebx, iframe->esp, iframe->ebp, iframe->edi, iframe->esi, iframe->ds, iframe->es, iframe->fs, iframe->gs, exception_messages[iframe->vector]
  );
  asm volatile ("hlt");
} 

/* __attribute__((interrupt)) */ void interrupt_handler_err(x86_extended_interrupt_frame_t *iframe) {
  cprintf(0x40,
          "\nCaught an interrupt!!\n"
          "iret ss %x iret esp %x\n"
          "eflags %x cs %x eip %x\n"
          "err %x vector %x\n"
          "eax %x ecx %x edx %x ebx %x\n"
          "esp %x ebp %x edi %x esi %x\n"
          "ds %x es %x fs %x gs %x\n"
          "%s\n",
          iframe->iret_ss, iframe->iret_esp, iframe->eflags, iframe->cs, iframe->eip, iframe->err, iframe->vector, iframe->eax, iframe->ecx, iframe->edx, iframe->ebx, iframe->esp, iframe->ebp, iframe->edi, iframe->esi, iframe->ds, iframe->es, iframe->fs, iframe->gs, exception_messages[iframe->vector]
  );
  asm volatile ("hlt");
} 

