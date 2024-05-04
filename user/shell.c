#include "include/api.h"
#include "include/escape.h"
#include "string/string.h"

char prompt_command[1000];

char kbd_character = 0;
bool prompt = true;

void memfillb(u8 val, u8p addr, size_t lim) {
  for (size_t idx = 0; idx < lim; idx++) {
    addr[idx] = val;
  }
} // to be made a syscall later!

void execute_command(char *cmd) {
  if(!strcmp(cmd, "halt")) {
    asm volatile ("int $0x7e");
  }
  cprintf(0x0a, "\nYou entered `%s`", prompt_command);
}

void irq_keyboard(x86_extended_interrupt_frame_t *iframe) {
  iframe = iframe; // to silence GCC
  kbd_character = getch();
}

extern void test_v8086();

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
  memfillb(0, (u8p)&prompt_command[0], 1000); 
  cprintf(0x02, "$ ");
  while(true) {
    switch (kbd_character) {
      case 0: { // no keyboard input yet
        continue;
      }
      case '\x04' : { // ^D
        kbd_character = 0;
        unsyscall(0, 0, 0, 0); // halt
        break;
      }
      case '\x03' : { // ^C
        kbd_character = 0;
        prompt_command[idx] = 0;
        kbd_character = 0;
        idx = 0;
        ucputc('\n');
        return;
      }
      case '\x1a' : { // ^Z
        prompt = false;
        return;
      }
      case '\x83' : { // ^[C
        asm volatile ("int $0x7e");
        break;
      }
      case '\x84' : { // ^[D
        asm volatile (
          "mov %0, %%edi\n"
          "int $0xff"
          : // none
          : "g" ((u32)test_v8086)
          : // none
        );
        break;
      }
      case '\x85' : { // ^[E
        asm volatile ("int $0xfe");
        break;
      }
      case '\n' : {
        prompt_command[idx] = 0;
        kbd_character = 0;
        idx = 0;
        if(*prompt_command)
          execute_command(prompt_command);
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
  printf("You are now in userspace!\n"
         "(Try to) think about just local APIs from now on.\n" // not "just local APIs" yet
  );
  unsyscall(1, 1, (u32)irq_keyboard, 0); // setup keyboard handler for IRQ1
  cprintf(0x0b, "Set up IRQ handler for keyboard on IRQ1\n");

  while (prompt)
    shell_prompt();
}


