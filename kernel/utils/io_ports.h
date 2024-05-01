#ifndef __IO_PORTS_H
#define __IO_PORTS_H

#include "../include/defs.h"

extern u8 inb(u16 port);
extern u16 inw(u16 port);
extern u32 inl(u16 port);
extern void outb(u16 port, u8 data);
extern void outw(u16 port, u16 data);
extern void outl(u16 port, u32 data);
extern void io_wait();

#endif /* __IO_PORTS_H */
