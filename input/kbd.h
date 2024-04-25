#ifndef _KBD_H
#define _KBD_H

#include "../include/defs.h"


#define MODIFIER_CTRL   0b10000000 
#define MODIFIER_SHIFT  0b01000000 
#define MODIFIER_ALT    0b00100000 
#define MODIFIER_SUPER  0b00010000
#define MODIFIER_RCTRL  0b00001000
#define MODIFIER_RSHIFT 0b00000100
#define MODIFIER_RALT   0b00000010
#define MODIFIER_RSUPER 0b00000001

#define MOD_CTRL        (globalModifiers >> 7) & 1
#define MOD_SHIFT       (globalModifiers >> 6) & 1
#define MOD_ALT         (globalModifiers >> 5) & 1
#define MOD_SUPER       (globalModifiers >> 4) & 1
#define MOD_RCTRL       (globalModifiers >> 3) & 1
#define MOD_RSHIFT      (globalModifiers >> 2) & 1
#define MOD_RALT        (globalModifiers >> 1) & 1
#define MOD_RSUPER      globalModifiers & 1

// mod keys 
#define KEY_CTRL        0x1d
#define KEY_SHIFT       0x2a
#define KEY_ALT         0x38
#define KEY_SUPER       0 
#define KEY_RCTRL       0 
#define KEY_RSHIFT      0x36 
#define KEY_RALT        0 
#define KEY_RSUPER      0 // not doing extended keys for now
#define KEY_CAPSLOCK    0x3a 
// func keys
#define KEY_F1          0x3b
#define KEY_F2          0x3c
#define KEY_F3          0x3d
#define KEY_F4          0x3e
#define KEY_F5          0x3f
#define KEY_F6          0x40
#define KEY_F7          0x41
#define KEY_F8          0x42
#define KEY_F9          0x43
#define KEY_F10         0x44
#define KEY_F11         0x57

extern const char kbd_layout_us_qwerty[128];

struct scode_t {
  u32 rawScancode;
  u8 bit0; 
  u8 bit1;
  u8 bit2; // 0x45: pause, 0xe0: prtscr
  u8 bit3;
   
  bool extended; // bit0 == 0xe0
  bool released; // bit0 > 0x60 && bit0 != 0xe0
};

struct keyEvent {
  struct scode_t scancode;
  bool pressed;  // 0 for released, 1 for pressed
  bool printable;
  char pchar;
  u8 modifiers;  // (msb first) ctrl, shift, alt, super, rctrl, rshift, ralt, rsuper
  u8 locks;      // (msb first) caps, scroll, num
} __attribute__((packed));

extern char scancodeChars[];

#endif /* _KBD_H */
