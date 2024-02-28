/* Non-formatted basic string print implementation */ 
#include "../include/strings.h"
#include "video.h" // putc(...) impl
#include "uprint.h"

void uprint(char *string) {
  while (*string) {
    putc(*string, default_color);
    string++;
  }
}
