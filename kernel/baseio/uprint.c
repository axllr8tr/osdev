/* Non-formatted basic string print implementation */ 
#include "../include/strings.h"
#include "video.h" // putc(...) impl
#include "uprint.h"

void uprintc(char *string, u8 color) {
  while (*string) {
    putc(*string, color);
    string++;
  }
}

void uprint(char *string) {
  uprintc(string, default_color);
}
