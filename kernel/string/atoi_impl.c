#include "../include/defs.h"
#include "../string/string.h"
#include "../baseio/printf.h"
#include "conv.h"

static u32 spow(u32 base, u32 power) {
  u32 ret = 1;
  if (power == 0)
    return 1;
  if (power > 32) // ridiculous
    return 0;
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

int atoi_k(char *src) {
  // printf("Start ascii to int conversion of \"%s\"\n", src);

  char *start = src;
  while(*start == ' ') {
    start++;
  }; // skip whitespaces
  // printf("Start = %x\n", (u32)start);

  // printf("deref Start = %x\n", *start);

  char *end = src;
  while (*end)
    if(!char_matches_any_k(*src, "0123456789abcdefABCDEFxX")) {
      break; // find end of number (possibly)
    }
    else 
      ++end;

  start -= 2;
  end -= 1; // can't have that NUL

  // printf("End = %x\n", (u32)end);
  // printf("deref End = %x\n", *end);
  
  bool is_negative = *src == '-';
  int ret = 0;
  size_t idx  = 0;

  for(; end > start; --end) {
    // printf("ret += %u (%x) * 10^%u\n", ctoi(*end, 10), *end, idx);
    ret += ctoi(*end, 10) * spow(10, idx++);
  }

  if (is_negative) ret = 0 - ret;
  
  return ret;
}
