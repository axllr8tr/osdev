#include "../include/defs.h"
#include "8259_pic.h"
#include "../utils/io_ports.h"
#include "../logging/log.h"


void init_pic(u8 offs1, u8 offs2) {
  u8 a1, a2;
  
  a1 = inb(PIC1_DATA); // preserve masks
  a2 = inb(PIC2_DATA);
  
  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
  io_wait();
  outb(PIC1_DATA, offs1);
  io_wait();
  outb(PIC2_DATA, offs2);
  io_wait();
  outb(PIC1_DATA, 4);
  io_wait();
  outb(PIC2_DATA, 2);
  io_wait();

  // outb(PIC1_DATA, ICW4_AUTO);
  // io_wait();
  // outb(PIC2_DATA, ICW4_AUTO);
  // io_wait();

  outb(PIC1_DATA, a1);
  outb(PIC2_DATA, a2);
  kdebug_log(DEBUG "remapped PICs: master offs 0x%x, slave offs 0x%x", offs1, offs2);
}

void fix_pic(void) { 
  init_pic(0x20, 0x28); 
}
