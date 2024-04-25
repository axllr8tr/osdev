#ifndef __IO_PORTS_H
#define __IO_PORTS_H

#include "../include/defs.h"

extern inline u8 inb(u16 port) { 
  u8 _ret; 
  asm volatile ("inb %1, %0" : "=a" (_ret) : "dN" (port));
  return _ret;
}

extern inline u16 inw(u16 port) { 
  u16 _ret; 
  asm volatile ("inw %1, %0" : "=a" (_ret) : "dN" (port));
  return _ret;
}

extern inline u32 inl(u16 port) { 
  u32 _ret; 
  asm volatile ("inl %%dx, %%eax" : "=a" (_ret) : "dN" (port));
  return _ret;
}

extern inline void outb(u16 port, u8 data) {
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}

extern inline void outw(u16 port, u16 data) {
  asm volatile ("outw %1, %0" : : "dN" (port), "a" (data));
}

extern inline void outl(u16 port, u32 data) {
  asm volatile ("outl %1, %0" : : "dN" (port), "a" (data));
}

extern inline void io_wait() {
  asm ("inb $0xff");
}

#endif /* __IO_PORTS_H */
