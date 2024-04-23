#include "../include/defs.h"

volatile u16p vga_textmode_mmio = (u16p)0xb8000;

u16 width  = 80;
u16 height = 25;

u16 x = 0;
u16 y = 0;

u8 default_color = 0x07;

u32 coord_to_offs(u16 _x, u16 _y) { 
  return _x + (_y * width);
}

void vga_put_entry(u16 ent, u32 offs) {
  vga_textmode_mmio[offs] = ent;
}

void vga_put_entry_at(u16 ent, u16 _x, u16 _y) {
  vga_textmode_mmio[coord_to_offs(_x, _y)] = ent;
}

u16 vga_gen_entry(u8 ch, u8 co) {
  return (co << 8) | ch;
}

void vga_fill_screen(u16 ent) {
  for (u16 j = 0; j < height; j++)
    for (u16 i = 0; i < width; i++)
      vga_put_entry_at(ent, i, j);
}

void vga_init_term() {
  vga_fill_screen(0);
  x = 0;
  y = 0;
}

void putc(u8 ch, u8 co) {
  switch (ch) {
    case '\n' : {
      x = 0;
      y++;
      break;
    }
    default : {
      vga_put_entry_at(vga_gen_entry(ch, co), x, y);
      if (x < (width - 1)) { x++; }
      else { x = 0; y++; }
      if (y > (height - 1)) y = 0;
      break;
    }
  }
}
