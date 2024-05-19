#include "../include/defs.h"
#include "../utils/io_ports.h"
#include "../baseio/printf.h"
#include "../video/video.h"
#include "../logging/log.h"
#include "kbd.h"

// #define EXTREME_KEYBOARD_DEBUGGING // <-- used for troubleshooting kbd on real hardware

const char kbd_layout_us_qwerty[128] = {
  0, '\033', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', // 0-f
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', // 10-1f
  'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', // 20-2f 
  'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, // 30-3f
  0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', // 40-4f 
  '2', '3', '0', '.', 0, 0, 0, 0, 0, // 50-58
};

volatile u8 key_flags = 0;
volatile u8 key_locks = 0;
scode_t global_keystroke;
keyevent_t global_keyevent; // getch()

void receive_keystroke(scode_t *target) {
  u32 scancode = inl(0x60); // ps/2 only
  target->rawScancode = scancode;
  target->extended = (scancode & 0xff) == 0xe0;
  target->released = (target->byte0 & 0x80) && scancode != 0xe0;
  #ifdef EXTREME_KEYBOARD_DEBUGGING
    kdebug_log(DEBUG "kbd: got keystroke: scancode %x", scancode);
  #endif
}

void keystroke_to_keyevent(scode_t *keystroke, keyevent_t *keyevent) {
  switch (keystroke->byte0 & 0x7f) {
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
  keyevent->printable = (((keystroke->byte0 & 0x7f) < 0x58) && kbd_layout_us_qwerty[keystroke->byte0 & 0x7f] >= 0x20) || (kbd_layout_us_qwerty[keystroke->byte0 & 0x7f] == '\n');
  keyevent->pchar = kbd_layout_us_qwerty[keystroke->byte0 & 0x7f]; // even more stupid
  keyevent->pressed = !keystroke->released; // nice
  #ifdef EXTREME_KEYBOARD_DEBUGGING
    kdebug_log(DEBUG "kbd: %x %x %x %x", keystroke->byte0, keystroke->byte1, keystroke->byte2, keystroke->byte3);
  #endif

}

char shift_character(char chr) {
  // BADCODE: didn't think of anything clever :(
  if (chr >= 0x41 && chr <= 0x5a) 
    return chr + 0x20;
  if (chr >= 0x61 && chr <= 0x7a) 
    return chr - 0x20;
  switch (chr) {
    case '1':
      return '!';
    case '2':
      return '@';
    case '3':
      return '#';
    case '4':
      return '$';
    case '5':
      return '%';
    case '6':
      return '^';
    case '7':
      return '&';
    case '8':
      return '*';
    case '9':
      return '(';
    case '0':
      return ')';
    case '-':
      return '_';
    case '+':
      return '=';
    case '[':
      return '{';
    case ']':
      return '}';
    case '\\':
      return '|';
    case ';':
      return ':';
    case '\'':
      return '"';
    case ',':
      return '<';
    case '.':
      return '>';
    case '/':
      return '?';
    case '`':
      return '~';
    default: {
      return 0;
    }
  }
}

static bool is_letter(char chr) {
  return (chr >= 0x41 && chr <= 0x5a) || (chr >= 0x61 && chr <= 0x7a);
}

// BADCODE: mess
char handle_keyevent(keyevent_t *keyevent) {
  if (keyevent->pressed && (keyevent->printable || keyevent->pchar == '\b' || keyevent->pchar == '\033') && !keyevent->modifiers) {
    return keyevent->pchar;
  }
  if (keyevent->pressed && keyevent->printable && keyevent->modifiers & MODIFIER_SHIFT && !(keyevent->modifiers & MODIFIER_CTRL)) {
    return shift_character(keyevent->pchar);
  }
  if (keyevent->pressed && keyevent->printable && !keyevent->modifiers && key_locks & LOCK_CAPS && is_letter(keyevent->pchar)) {
    return shift_character(keyevent->pchar);
  }
  if (keyevent->pressed && keyevent->modifiers & MODIFIER_CTRL && !(keyevent->modifiers & MODIFIER_SHIFT)) {
    return shift_character(keyevent->pchar) - 0x40; // Ctrl-c -> ^C -> \x03
  }
  if (keyevent->pressed && keyevent->modifiers & MODIFIER_CTRL && keyevent->modifiers & MODIFIER_SHIFT) {
    return shift_character(keyevent->pchar) + 0x40; // Ctrl-Shift-c -> ^[C -> \033C -> \x83 
  }
  return 0;
}

char getch() {
  receive_keystroke(&global_keystroke);
  keystroke_to_keyevent(&global_keystroke, &global_keyevent);
  return handle_keyevent(&global_keyevent); // bad idea probably
}
