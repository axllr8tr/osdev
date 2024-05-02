#include "include/api.h"

char prompt_command[1000];
bool prompt = true;
char kbd_char = '\0';

void irq_handler_local_test(x86_extended_interrupt_frame_t *iframe) {
  printf(".");
  return;
}

void shell_prompt() {
  unsyscall(1, 0, (u32)irq_handler_local_test, 0);
  while(true) {

  }
}

void shell_entry() {
  printf("You are now in userspace (kinda)!\n"
         "Think about just local APIs from now.\n"
  );
  while (prompt)
    shell_prompt();
}


