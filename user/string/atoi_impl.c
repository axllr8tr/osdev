#include "../include/defs.h"
#include "../string/string.h"
#include "conv.h"

static u32 spow(u32 base, u32 power) {
  u32 ret = 1;
  if (power == 0)
    return 1;
  while (power--) {
    ret *= base;
  }

  return ret;
}

static u8 ctoi(char chr, u8 base) {
  u8 ret = 0;
  if (chr >= '0' && chr <= '9') ret = chr - '0';
  if (chr >= 'A' && chr <= 'F') ret = chr - 'A';
  if (chr >= 'a' && chr <= 'f') ret = chr - 'a';
  if (chr == 'x' || chr == 'X') ret = 0;
  if (ret > base - 1) return 0xff;
  return ret;
}

int atoi(char *src) {
  char *start = src;
  while(*start++ == ' '); // skip whitespaces
  char *end = src;
  while (*end++)
    if(!char_matches_any(*src, "0123456789abcdefABCDEFxX")) {
      break;
    }
  start -= 2;
  end -= 2; // can't have that NUL
  bool is_negative = *src == '-';
  int ret = 0;
  size_t idx  = 0;
  for(; end > start; --end) {
    ret += ctoi(*end, 10) * spow(10, idx++);
  }
  if (is_negative) ret = 0 - ret;  
  return ret;
}

int atoi_b(char *src, u8 base) {
  char *start = src;
  while(*start++ == ' '); // skip whitespaces
  char *end = src;
  while (*end++)
    if(!char_matches_any(*src, "0123456789abcdefABCDEFxX")) {
      break;
    }
  start -= 2;
  end -= 2; // can't have that NUL
  bool is_negative = *src == '-';
  int ret = 0;
  size_t idx  = 0;
  for(; end > start; --end) {
    ret += ctoi(*end, 10) * spow(base, idx++);
  }
  if (is_negative) ret = 0 - ret;  
  return ret;
}

