#include "idt.h"
#include "interrupts.h"
#include "../baseio/uprint.h"
#include "../baseio/printf.h"
#include "../utils/panic.h"
__attribute__((interrupt)) void interrupt_handler_generic(x86_extended_interrupt_frame_t *iframe) {
  cprintf(0x70, 
          "Caught an interrupt!! vec %x\n",
          iframe->vector
  );
  asm volatile ("hlt");
} 

/* __attribute__((interrupt)) */ void interrupt_handler_err(x86_extended_interrupt_frame_t *iframe) {
  cprintf(0x40, 
          "Caught an error!! vec %x err %x\n",
          iframe->vector, iframe->err
  );
} 

