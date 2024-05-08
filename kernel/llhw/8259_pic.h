#ifndef _8259_PIC_H
#define _8259_PIC_H

#include "../include/defs.h"

#define PIC1_PORT		0x20
#define PIC2_PORT		0xA0
#define PIC1_COMMAND	PIC1_PORT
#define PIC1_DATA	(PIC1_PORT+1)
#define PIC2_COMMAND	PIC2_PORT
#define PIC2_DATA	(PIC2_PORT+1)
#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */
// stolen from https://wiki.osdev.org/PIC

void init_pic(u8, u8);
void fix_pic(void);

#endif /* _8259_PIC_H */
