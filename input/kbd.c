#include "../include/defs.h"
#include "../utils/io_ports.h"
#include "kbd.h"

const char kbd_layout_us_qwerty[128] = {
  0, '\e', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', // 0-f
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', // 10-1f
  'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', // 20-2f 
  'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, // 30-3f
  0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', // 40-4f 
  '2', '3', '0', '.', 0, 0, 0, 0, 0, // 50-58
};

volatile u8 key_flags = 0;
volatile u8 key_locks = 0;

void receive_keystroke(scode_t *target) {
  u32 scancode = inl(0x60); // ps/2 only
  target->rawScancode = scancode;
  target->extended = (scancode & 0xff) == 0xe0;
  target->released = (target->byte3 & 0x80) && scancode != 0xe0;
}

void keystroke_to_keyevent(scode_t *keystroke, keyevent_t *keyevent) {
  keyevent_t ret;
  switch (keystroke->byte3 & 0x7f) {
    case KEY_CAPSLOCK : {
      if (key_locks & LOCK_CAPS) {
        key_locks &= ~LOCK_CAPS;
      } else {
        key_locks |= LOCK_CAPS;
      }
      break;
    }
    case KEY_SHIFT : {
      if(keystroke->released) {
        key_flags &= ~MODIFIER_SHIFT;
      } else {
        key_flags |= MODIFIER_SHIFT;
      }
      break;
    };
    case KEY_CTRL : {
      if(keystroke->released) {
        key_flags &= ~MODIFIER_CTRL;
      } else {
        key_flags |= MODIFIER_CTRL;
      }
      break;
    }
  }
  keyevent->scancode = *keystroke;
  keyevent->locks = key_locks;
  keyevent->modifiers = key_flags;
  keyevent->printable = ((keystroke->byte0 & 0x7f) < 0x58) && kbd_layout_us_qwerty[keystroke->byte0 & 0x7f] >= 0x20;
  keyevent->pchar = kbd_layout_us_qwerty[keystroke->byte0 & 0x7f]; // even more stupid
  keyevent->pressed = !keystroke->released; // nice
}
