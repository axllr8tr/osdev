#include "include/api.h"
#include "include/defs.h"
#include "include/escape.h"
#include "string/string.h"
#include "string/conv.h"

#define command(u) if(!strcmp(argv[0], u)) // not too bad, eh?


char prompt_command[1000];
char *command_tokens[256];

u8 command_ret = 0;

char kbd_character = 0;
bool prompt = true;

void memfillb(u8 val, u8p addr, size_t lim) {
  for (size_t idx = 0; idx < lim; idx++) {
    addr[idx] = val;
  } 
}

int execute_command(int argc, char **argv) {
  command ("halt") {
    asm volatile ("int $0x7e");
  }

  command ("dec2hex") {
    if (argc != 2)
      return 1;
    cprintf(0x0b, "%s -> %x\n", argv[1], atoi(argv[1]));
    return 0;
  }

  command ("hang") {
    while (true);
  }

  command ("syscall") {
    if (argc != 5)
      return 1;
    unsyscall(atoi_b(argv[1], 8), atoi_b(argv[2], 8), atoi_b(argv[3], 8), atoi_b(argv[4], 8));
    return 0;
  }

  command ("moni") {
    extern void monitor();
    extern void irq_keyboard(x86_extended_interrupt_frame_t *);
    monitor();
    unsyscall(1, 1, (u32)irq_keyboard, 0);
    return 0;
  }

  command ("clear") {
    printf("\f");
    return 0;
  }

  cprintf(0x04, "No such command: `%s`\n", argv[0]);
  return 127;
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
  memfillb(0, (u8p)&prompt_command[0], 1000); 
  u32 idx = 0;
  if (!command_ret) { // BUG: for some reason the command_ret always becomes 0 each time the scrollback is initiated. why?
    cprintf(0x02, "%u $ ", command_ret);
  } else {
    cprintf(0x04, "e!", command_ret);
    cprintf(0x04, "%u ", command_ret);
    cprintf(0x02, "$ ");
  }
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
        printf("\n");
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
      case '\f' : { // ^L
        printf("\f");
        return;
      }
      case '\n' : {
        prompt_command[idx] = 0;
        kbd_character = 0;
        idx = 0;
        size_t argc = 0;
        split_string_into_tokens(prompt_command, " ", command_tokens, 256, &argc);
        printf("\n");
        if(*prompt_command)
          command_ret = execute_command(argc, command_tokens);
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
  cprintf(0x0b, "You are now in userspace!\n"
                "(Try to) think about just local APIs from now on.\n" // not "just local APIs" yet
  );
  unsyscall(1, 1, (u32)irq_keyboard, 0); // setup keyboard handler for IRQ1
  cprintf(0x0a, "[hw] Set up IRQ handler for keyboard on IRQ1\n");

  while (prompt)
    shell_prompt();
}


