#include "include/api.h"

char prompt_command[1000];
char kbd_character = 0;
bool prompt = true;


void irq_keyboard(x86_extended_interrupt_frame_t *iframe) {
  kbd_character = getch();
}


void shell_prompt() {
  u32 idx = 0;
  cprintf(0x02, "$ ");
  unsyscall(1, 1, (u32)irq_keyboard, 0);
  while(true) {
    switch (kbd_character) {
      case 0: {
        continue;
      }
      case '\x04' : {
        kbd_character = 0;
        unsyscall(0, 0, 0, 0);
        break;
      }
      case '\n' : {
        prompt_command[idx] = 0;
        kbd_character = 0;
        idx = 0;
        cprintf(0x0a, "\nString entered: %s\n", prompt_command);
        return;
        break;
      }
      default : {
        printf("%c", kbd_character);
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
  while (prompt)
    shell_prompt();
}


