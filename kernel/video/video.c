#include "../include/defs.h"
#include "../utils/io_ports.h"
#include "../utils/mem.h"
#include "../tty/escape.h"
#include "../video/video.h"


#define VGA_WIDTH  80
#define VGA_HEIGHT 25

u16 width  = VGA_WIDTH;
u16 height = VGA_HEIGHT;


volatile u16p vga_textmode_mmio = (u16p)0xb8000;
volatile u16  vga_textmode_buffer[VGA_HEIGHT * VGA_WIDTH];


u16 x = 0;
u16 y = 0;

u8 default_color = 0x07;

void update_cursor_coords(u16 _x, u16 _y)
{
	u16 pos = _y * width + _x; 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (u8)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (u8)((pos >> 8) & 0xFF));
}

u32 coord_to_offs(u16 _x, u16 _y) { 
  return _x + (_y * width);
}

void vga_put_entry(u16 ent, u32 offs) {
  vga_textmode_buffer[offs] = ent;
  vga_textmode_mmio[offs] = ent;
}

void vga_put_entry_at(u16 ent, u16 _x, u16 _y) {
  vga_textmode_buffer[coord_to_offs(_x, _y)] = ent;
  vga_textmode_mmio[coord_to_offs(_x, _y)] = ent;
}

u16 vga_gen_entry(u8 ch, u8 co) {
  return (co << 8) | ch;
}

u16 vga_get_entry_at(u16 _x, u16 _y) {
  return vga_textmode_buffer[coord_to_offs(_x, _y)];
}

void vga_fill_screen(u16 ent) {
  for (u16 j = 0; j < height; j++)
    for (u16 i = 0; i < width; i++)
      vga_put_entry_at(ent, i, j);
}

void vga_init_term() {
  vga_fill_screen(vga_gen_entry(0, 0x07));
  x = 0;
  y = 0;
}

void ucputc(u8 ch) {
  putc(ch, vga_get_entry_at(x, y) >> 8);
}

void vga_flush_buffer() {
  memcpyw((u16p)vga_textmode_mmio, (const u16p)vga_textmode_buffer, width * height);
}

void _loc_scrollback(u16 ht) {
  if (ht < y) {
    memcpyw((u16p)&vga_textmode_buffer[0], (const u16p)&vga_textmode_buffer[ht * width], (height - ht) * width * 2);
    // memfillw((u16p)&vga_textmode_buffer[(height + ht) * width], 0xff00, (height - ht) * width);
    memfillw((u16p)&vga_textmode_buffer[coord_to_offs(0, height - ht)], (default_color << 8) | 0, width);
    vga_flush_buffer();
    y = height - ht;
  }
  else {
    y = 0;
    vga_init_term();
  }
  x = 0;
}

void putc(u8 ch, u8 co) {
  switch (ch) {
    case '\n' : {
      x = 0;
      if (y < height - 1)
        y++;
      else
        _loc_scrollback(1);
      break;
    }
    case '\f' : {
      vga_init_term();
      break;
    }
    case ASCII_CLF : {
      if (x > 0) x--;
      break;
    }
    case ASCII_CRT : {
      if (x < width - 1) x++;
      break;
    }
    case ASCII_CUP : {
      if (y > 0) y--;
      break;
    }
    case ASCII_CDN : {
      if (y < height - 1) y++;
      break;
    }
    default : {
      if (x < (width - 1)) {
        vga_put_entry_at(vga_gen_entry(ch, co), x, y);
        x++;
        break;
      } else {
        vga_put_entry_at(vga_gen_entry(ch, co), x, y);
        y++;
        x = 0;
      }
      if (y > (height - 1)) {
        x = 0;
        _loc_scrollback(1);
        vga_put_entry_at(vga_gen_entry(ch, co), x, y);
      }
      else {
        vga_put_entry_at(vga_gen_entry(ch, co), x, y);
      }
    }
  }
  update_cursor_coords(x, y);
}
