#include "idt.h"
#include "interrupts.h"
#include "../baseio/uprint.h"
#include "../baseio/printf.h"
#include "../utils/panic.h"
__attribute__((interrupt)) void interrupt_handler_generic(x86_extended_interrupt_frame_t *iframe) {
  cprintf(0x70, 
          "\n*** CAUGHT INTERRUPT ***\n"
          "VECTOR %x\n"
          "*** CAUGHT INTERRUPT ***\n",
          iframe->vector
  );
} 

__attribute__((interrupt)) void interrupt_handler_err(x86_extended_interrupt_frame_t *iframe) {
  cprintf(0x70, 
          "\n*** CAUGHT INTERRUPT ***\n"
          "VECTOR %x\n"
          "*** CAUGHT INTERRUPT ***\n",
          iframe->vector
  );
  asm volatile ("hlt");
} 

