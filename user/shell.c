#include "include/api.h"

char prompt_command[1000];
bool prompt = true;
char kbd_char = '\0';
bool kbd_delta0 = false;
bool kbd_delta1 = true;

void keyboard_handler_userspace() {

}

void shell_prompt() {
  char a;
  cprintf(0x02, "$ ");
  while (true) {
    a = getch();
    printf("%c", a);
    if (a == 0x04) {
      unsyscall(0, 0, 0, 0, 0, 0, 0);
    }
  }
}

void shell_entry() {
  printf("You are now in userspace (kinda)!\n"
         "Think about just local APIs from now.\n"
  );
  while (prompt)
    shell_prompt();
}


