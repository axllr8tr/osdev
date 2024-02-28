#ifndef __INPUT_H
#define __INPUT_H

#include "defs.h"

extern u8 globalModifiers; 

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

#endif /* __INPUT_H */
