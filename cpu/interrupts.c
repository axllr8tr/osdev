#include "idt.h"
#include "interrupts.h"
#include "../utils/panic.h"
__attribute__((interrupt)) void interrupt_handler_generic(x86_simple_interrupt_frame_t *iframe) {
  uprint("well");
} 

__attribute__((interrupt)) void interrupt_handler_err(x86_simple_interrupt_frame_t *iframe) {
  cpanic(0xfffffff, "Caught an interrupt with an error code");
} 

