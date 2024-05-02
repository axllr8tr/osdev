#ifndef _VIDEO_H
#define _VIDEO_H

#include "../include/defs.h"

extern u16 width, height, x, y;
extern u8  default_color;

extern void vga_fill_screen(u16);
extern u16  vga_gen_entry(u8, u8);
extern void vga_init_term(void);
extern void putc(u8, u8);
extern void ucputc(u8);


#endif /* _VIDEO_H */
