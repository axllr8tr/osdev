#include "include/api.h"
#include "include/defs.h"
#include "include/escape.h"
#include "string/string.h"
#include "string/conv.h"
#include "ansi_test.h"
#include "compat.h"

#define initial_command(u) if(!strcmp(argv[0], u)) 
#define command(u)  else if(!strcmp(argv[0], u)) // not too bad, eh?


char prompt_command[1000];
char *command_tokens[256];

u8 command_ret = 0;

char kbd_character = 0;
bool prompt = true;

u32 pit_ticks = 0;

void fetch() {
  printf((char *)noofetch, pit_ticks);
}

void memsetb(u8p addr, u8 val, size_t lim) {
  for (size_t idx = 0; idx < lim; idx++) {
    addr[idx] = val;
  } 
}

void memsetw(u16p addr, u16 val, size_t lim) {
  for (size_t idx = 0; idx < lim; idx++) {
    addr[idx] = val;
  } 
}

void memsetl(u32p addr, u32 val, size_t lim) {
  for (size_t idx = 0; idx < lim; idx++) {
    addr[idx] = val;
  } 
}


int execute_command(u32 argc, char **argv) {
  initial_command ("halt") {
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
    if (argc != 5) {
      printf("Usage: `syscall [no, dec] [ebx, hex] [ecx, hex] [edx, hex]\n");
      return 2;
    }
    unsyscall(atoi_b(argv[1], 10), atoi_b(argv[2], 16), atoi_b(argv[3], 16), atoi_b(argv[4], 16));
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

  command ("peekb") {
    if (argc != 2) {
      printf("Usage: `peekb [addr, hex]`\n");
      return 2;
    }
    u32 addr = atoi_b(argv[1], 16);
    printf("%x: %x\n", addr, *(u8p)addr);
    return 0;
  }

  command ("peekw") {
    if (argc != 2) {
      printf("Usage: `peekw [addr, hex]`\n");
      return 2;
    }
    u32 addr = atoi_b(argv[1], 16);
    printf("%x: %x\n", addr, *(u16p)addr);
    return 0;
  }
 
  command ("peekl") {
    if (argc != 2) {
      printf("Usage: `peekb [addr, hex]`\n");
      return 2;
    }
    u32 addr = atoi_b(argv[1], 16);
    printf("%x: %x\n", addr, *(u32p)addr);
    return 0;
  }

  command ("pokeb") {
    if (argc != 3) {
      printf("Usage: `pokeb [addr, hex] [val, hex]`\n");
      return 2;
    }
    u32 addr = atoi_b(argv[1], 16);
    u8 val = atoi_b(argv[2], 16);
    *(u8p)addr = val;
    return 0;
  }
  command ("pokew") {
    if (argc != 3) {
      printf("Usage: `pokew [addr, hex] [val, hex]`\n");
      return 2;
    }
    u32 addr = atoi_b(argv[1], 16);
    u16 val = atoi_b(argv[2], 16);
    *(u16p)addr = val;
    return 0;
  }

  command ("pokel") {
    if (argc != 3) {
      printf("Usage: `pokel [addr, hex] [val, hex]`\n");
      return 2;
    }
    u32 addr = atoi_b(argv[1], 16);
    u32 val = atoi_b(argv[2], 16);
    *(u32p)addr = val;
    return 0;
  }

  command ("memsetb") {
    if (argc != 4) {
      printf("Usage: `memsetb [addr, hex] [val, hex] [lim, hex]`\n");
      return 2;
    }

    u8p addr = (u8p)atoi_b(argv[1], 16);
    u8 val = atoi_b(argv[2], 16) & 0xff;
    size_t lim = atoi_b(argv[3], 16);

    memsetb(addr, val, lim);
    return 0;
  }

  command ("memsetw") {
    if (argc != 4) {
      printf("Usage: `memsetw [addr, hex] [val, hex] [lim, hex]`\n");
      return 2;
    }

    u16p addr = (u16p)atoi_b(argv[1], 16);
    u16 val = atoi_b(argv[2], 16) & 0xffff;
    size_t lim = atoi_b(argv[3], 16);

    memsetw(addr, val, lim);
    return 0;
 }

  command ("memsetl") {
    if (argc != 4) {
      printf("Usage: `memsetl [addr, hex] [val, hex] [lim, hex]`\n");
      return 2;
    }

    u32p addr = (u32p)atoi_b(argv[1], 16);
    u32 val = atoi_b(argv[2], 16) & 0xffffffff;
    size_t lim = atoi_b(argv[3], 16);

    memsetl(addr, val, lim);
    return 0;
  }

  command ("echo") {
    cprintf(0x0e, "warning: echo function is really broken as it discards extra spaces\033[0m\n");
    for (size_t idx = 1; idx < argc; idx++) {
      printf("%s ", argv[idx]); // alright
    }
    printf("\n");
    return 0;
  }

  command ("call") {
    if (argc != 2) {
      printf("Usage: `call [function addr, hex]`\n");
      return 2;
    }
    u32 addr = atoi_b(argv[1], 16);
    asm volatile (
      "call *%0"
      : // none
      : "r" (addr)
      : "eax"
    );
  }

  command ("neofetch") {
    fetch();
    return 0;
  }
  
  command ("loglevel") {
    if (argc != 2) {
      printf("Usage: `loglevel [1-9]`\n");
      return 2;
    }
    extern u8 min_loglevel;
    min_loglevel = atoi(argv[1]);
    return 0;
  }

  cprintf(0x04, "No such command: `%s`\n", argv[0]);
  return 127;
}

void irq_keyboard(x86_extended_interrupt_frame_t *iframe) {
  iframe = iframe; // to silence GCC
  kbd_character = getch();
}

void irq_pit() {
  pit_ticks++;
}

void putc_wrapper(u8 chr, u8 col) { // only for characters inputted using a keyboard
  if (chr < 0x20 && (chr != '\r' || chr != '\n' || chr != '\t' || chr != '\033' || chr != '\b')) { // noooo 
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
  memsetb((u8p)&prompt_command[0], 0, 1000); 
  u32 idx = 0;
  if (!command_ret) { 
    cprintf(0x02, "$ ", command_ret);
  } else {
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

void shell_entry(void) {
  cprintf(0x0b, "You are now in userspace!\n"
                "(Try to) think about just local APIs from now on.\n" // not "just local APIs" yet
  );
  unsyscall(1, 0, (u32)irq_pit, 0); // set up timer
  unsyscall(1, 1, (u32)irq_keyboard, 0); // set up keyboard

  while (prompt)
    shell_prompt();
}


