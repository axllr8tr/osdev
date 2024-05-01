#include "idt.h"
#include "interrupts.h"
#include "../baseio/uprint.h"
#include "../baseio/printf.h"
#include "../utils/panic.h"
#include "../utils/io_ports.h"
#include "../input/kbd.h"
#include "../video/video.h"

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

void interrupt_handler_generic(x86_extended_interrupt_frame_t *iframe) {
  switch (iframe->vector) { 
    case 0x7f : {
      break;
    }
    default : {
      cprintf(0x6f, 
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
  scode_t a;
  keyevent_t b;
  // printf("Caught an IRQ #%u\n", iframe->vector - 0x20);
  switch (iframe->vector - 32) {
    case 0: {
      break;
    }
    case 1: {
      receive_keystroke(&a);
      keystroke_to_keyevent(&a, &b);
      printf("%c", b.pchar * b.pressed);
      break;
    }
  }
  if (iframe->vector >= 40) {
    outb(0x20, 0xa0);
  }
  outb(0x20, 0x20);
}

void interrupt_handler_simple(x86_simple_interrupt_frame_t *iframe) {
  cprintf(0x4f,
          "Caught an interrupt!\n"
          "Err %x Vec %x EFlags %x CS %x EIP %x\n",
          iframe->err, iframe->vector, iframe->eflags, iframe->cs, iframe->eip
  );
  asm volatile ("hlt");
}
