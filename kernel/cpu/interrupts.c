#include "idt.h"
#include "interrupts.h"
#include "../baseio/uprint.h"
#include "../baseio/printf.h"
#include "../utils/panic.h"
#include "../utils/io_ports.h"
#include "../input/kbd.h"
#include "../video/video.h"
#include "../system/syscalls.h"
#include "v8086.h"

irq_handler_t irq_handlers[16] = {0};

void irq_handler_install(u8 idx, irq_handler_t handler) {
  irq_handlers[idx] = handler;
}

void irq_handler_uninstall(u8 idx) {
  irq_handlers[idx] = 0;
}

void null_handler(x86_extended_interrupt_frame_t *iframe) {
  iframe = iframe;
}


const char *exception_messages[32] = {
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

void interrupt_handler_generic(x86_extended_interrupt_frame_t *iframe) {
  switch (iframe->vector) { 
    case 0x7e : {
      hcf(iframe); 
      break;
    }
    case 0x7f : {
      ksyscall(iframe->eax, iframe->ebx, iframe->ecx, iframe->edx);
      break;
    }
    case 0xfe : {
      kprintf("Requested to enter virtual 8086 mode");
      enter_v8086();
      break;
    }
    case 0xff : {
      kprintf("Requested to execute code in virtual 8086 mode");
      run_inside_v8086(iframe->edi);
      break;
    }
    default : {
      kcprintf(0x6f, 
          "Caught an interrupt v=%x e=%x\n"
          "Cause: %s\n"
          "The system will now be halted.", 
          iframe->vector, iframe->err, exception_messages[iframe->vector]
      );
      while (true)
        asm volatile ("hlt");
    }
  }  
} 

void interrupt_handler_irq(x86_extended_interrupt_frame_t *iframe) {
  irq_handler_t local_irq_handler = irq_handlers[iframe->vector - 32];
  // printf("Caught an IRQ #%u\n", iframe->vector - 0x20);
  if (iframe->vector >= 40) {
    outb(0x20, 0xa0);
  }
  outb(0x20, 0x20);
  if (local_irq_handler) 
    local_irq_handler(iframe);
  else
    if (iframe->vector - 32 != 0)
      kcprintf(0x2a, "irq%u!", iframe->vector - 32);
}

void interrupt_handler_simple(x86_simple_interrupt_frame_t *iframe) {
  kcprintf(0x4f,
          "Caught an interrupt!\n"
          "Err %x Vec %x EFlags %x CS %x EIP %x\n",
          iframe->err, iframe->vector, iframe->eflags, iframe->cs, iframe->eip
  );
  asm volatile ("hlt");
}
