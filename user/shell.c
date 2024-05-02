#include "include/api.h"
#include "include/escape.h"

char prompt_command[1000];
char kbd_character = 0;
bool prompt = true;


void irq_keyboard(x86_extended_interrupt_frame_t *iframe) {
  iframe = iframe; // to silence GCC
  kbd_character = getch();
}

void putc_wrapper(u8 chr, u8 col) { // only for characters inputted using a keyboard
  if (chr < 0x20 && (chr != '\r' || chr != '\n' || chr != '\t' || chr != '\e' || chr != '\b')) { // noooo 
    cprintf(col, "^%c", chr + 0x40);
    return;
  }
  if (chr >= 0x80) {
    cprintf(col, "^[%c", chr - 0x40);
    return;
  }
  cprintf(col, "%c", chr);
}
void shell_prompt() {
  u32 idx = 0;
  cprintf(0x02, "$ ");
  while(true) {
    switch (kbd_character) {
      case 0: {
        continue;
      }
      case '\x04' : {
        kbd_character = 0;
        unsyscall(0, 0, 0, 0); // halt
        break;
      }
      case '\x03' : {
        kbd_character = 0;
        prompt_command[idx] = 0;
        kbd_character = 0;
        idx = 0;
        ucputc('\n');
        return;
      }
      case '\x83' : {
        asm volatile ("hlt");
        break;
      }
      case '\n' : {
        prompt_command[idx] = 0;
        kbd_character = 0;
        idx = 0;
        if(*prompt_command)
          cprintf(0x0a, "\nString entered: %s", prompt_command);
        ucputc('\n');
        return;
      }
      case '\xc0' : {
        break; // kludge for ctrl keys
      }
      case '\b' : {
        if (idx <= 0) break; // the `<` is here just in case
        if (prompt_command[idx] < 0x20 && prompt_command[idx] != 0) {
          putc(ASCII_CLF, 0);
          putc(ASCII_CLF, 0);
          prompt_command[idx--] = 0;
          ucputc(' ');
          ucputc(' ');
          putc(ASCII_CLF, 0);
          putc(ASCII_CLF, 0);
          break;
        } else if ((u8)prompt_command[idx] >= 0x80u) {
          prompt_command[idx--] = 0;
          putc(ASCII_CLF, 0);
          putc(ASCII_CLF, 0);
          putc(ASCII_CLF, 0);
          ucputc(' ');
          ucputc(' ');
          ucputc(' ');
          putc(ASCII_CLF, 0);
          putc(ASCII_CLF, 0);
          putc(ASCII_CLF, 0);
          break;
        } else {
          putc(ASCII_CLF, 0);
          prompt_command[idx--] = 0;
          ucputc(' ');
          putc(ASCII_CLF, 0);
          break;
        }
        break; // TODO: make it look less awful
      }
      default : {
        putc_wrapper(kbd_character, 0x07);
        prompt_command[idx++] = kbd_character;
        kbd_character = 0;
        break;
      }
    }
    kbd_character = 0;
    continue;
  }
}

void shell_entry() {
  printf("You are now in userspace (kinda)!\n"
         "Think about just local APIs from now.\n"
  );
  unsyscall(1, 1, (u32)irq_keyboard, 0); // setup keyboard handler for IRQ1
  cprintf(0x0b, "Set up IRQ handler for keyboard on IRQ1\n");

  while (prompt)
    shell_prompt();
}


