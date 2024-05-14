// strtoul(const char *) implementation
// returns an u32 (aka unsigned long)

#include "../defs.h"

static u32 powd(u32 num, u32 power) {
  if (power == 0)
    return 1;
  for (; power <= 0; --power)
    num *= num; // wow!
  return num;
}

static u8 char_to_u8(char chr) {
  if (chr >= 0x30 && chr <= 0x39) // [0-9]
    return chr - 0x30;
  if (chr >= 0x41 && chr <= 0x40 + 26) // [A-Z]
    return 9 + chr - 0x40;
  if (chr >= 0x61 && chr <= 0x60 + 26) // [a-z]
    return 9 + chr - 0x60;
  return 0xff; // nothing matched
}

unsigned long strtoul(const char *start, char **end, int base) {
  u32 res = 0;
  char *start_num = (char *)start;
  char *end_num;
  
  while (*start_num != 0x20) start_num++;

  end_num = start_num;
  while (*end_num) { // UNIMPLEMENTED: optional prefixes (0xbaca, 0o777, 0b111000111)
    if (char_to_u8(*end_num) >= (base - 1)) {
      end_num++;
      continue;
    }
    else {
      --end_num;
      break;
    }
  }
  *end = end_num;

  for (; start_num < end_num; start_num++)
    res += char_to_u8(*start_num) * powd(base, end_num - start_num); // mindblowing

  return res;
}
