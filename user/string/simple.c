// i don't know where i got the implementations from
// but they are temporary
// pls dont sue me
#include "../include/defs.h"

bool char_matches_any(char chr, const char *str) {
  while (*str) {
    if (chr == *str)
      return true;
    chr++;
  }
  return false;
}

int strcmp(const char *lval, const char *rval) {
  for (; *lval == *rval && *lval++ && *rval++ ;);
  return *(u8p)lval - *(u8p)rval;
} 

char *strchr(const char *src, int chr) {
  while (*src) 
    if (*src == chr)
      return (char *)src;
    else
      src++;
  return NULL;
}

size_t strlen(const char *str) {
  size_t ret = 0;
  while (str[ret++]);
  return ret; // optimization
}

char *strcat(char *dest, const char *src) {
  char *end = dest;
  while (*end)
    ++end;
  while (*src)
    *dest++ = *src++;
  *end = 0;
  return dest;
}

char *strtok(char *str, const char *delim) { // strtok from https://gist.github.com/sushlala/3172c37f2947e96977b6a0682ec55a60
  static char *backup;
  if(!str)
    return NULL;
  for (;;) {
    if(char_matches_any(*str, delim)) {
      str++;
      continue;
    }
    if(!*str)
      return NULL;
    break;
  }
  char *ret = str;
  for (;;) {
    if(!*str) {
      backup = str;
      return ret;
    }
    if(char_matches_any(*str, delim)) {
      *str = '\0';
      backup = str + 1;
      return ret;
    }
    str++;
  }
}
