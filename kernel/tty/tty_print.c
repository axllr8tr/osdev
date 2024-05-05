#include "../include/defs.h"
#include "../utils/mem.h"
#include "../baseio/printf.h"
#include "../video/video.h"
#include "../string/string.h"
#include "../string/conv.h"
#include "escape.h"
#include <stddef.h>

#define BETTER_CALL_CHECK(R, D) R >= D ? R : D
#define BETTER_BALL_CHECK(R, D) R < D ? R : D

const u8 text_color_default = 0x07;
u8 text_color = text_color_default;
char work_buf[200]; // csi sequences up to 200 bytes seem reasonable
char *csi_params_pre[32];
u32 csi_params[32] = {0};
size_t str_index = 0;

u8 ansi_to_vga_colors[] = {
  0, // black
  4, // red 
  2, // green
  6, // yellow
  1, // blue
  5, // magenta
  3, // cyan
  7, // white
};

void tprint_set_color(u8 col) {
  text_color = col;
}

static void split_string(char *src, const char *delim, char **destv, size_t destc, size_t *destc_real) { // origin unknown, taken from my old osdev project
  char *work_ptr = strtok_k(src, delim);
  u16 idx = 0;
  u16 count = 0;

  while (work_ptr != NULL && idx < destc) {
    destv[idx] = work_ptr;
    if(destv[idx]) count++;
    idx++;
    work_ptr = strtok_k(NULL, delim);
  }
  *destc_real = count;
}

static void cursor_move_a(u8 direction, u16 steps, size_t argc) {
  if (!argc)
    steps = 1;
  switch (direction) {
    case ANSI_CUU: {
      // printf("\n%u steps up\n", steps);
      if (y >= steps) 
        y -= steps;
      else
        y = 0;
      break;
    }
    case ANSI_CUD: {
      // printf("\n%u steps down\n", steps);
      if (y + steps >= height - 1)
        y = height - 1;
      else
        y += steps;
      break;
    }
    case ANSI_CUF: {
      // printf("\n%u steps right\n", steps);
      if (x + steps >= width - 1)
        x = width - 1;
      else
        x += steps; 
      break;
    }
    case ANSI_CUB: {
      // printf("\n%u steps left\n", steps);
      if (x >= steps)
        x -= steps;
      else
        x = 0;
      break;
    }
  } // not working yet
}

static void handle_sgr(u32p sgr_params, size_t count) {
  // printf("It is an SGR\n");
  if (count == 0) {
    text_color = default_color;
    return;
  }
  for(size_t idx = 0; idx < count; idx++) {
    u32 param = sgr_params[idx];
    switch (param) {
      case ANSI_SGR_INTENSITY : {
        text_color |= 0b1000;
        break;
      }
      case ANSI_SGR_INTENSITY_BG : { // aka blink
        text_color |= 0b10000000;
        break;
      }
      case ANSI_SGR_RESET : {
        text_color = text_color_default;
        break;
      }
      case 30 ... 37 : {
        text_color = (text_color & 0xf0) | (ansi_to_vga_colors[param - 30] & 0x07);
        break;
      }
      case 40 ... 47 : {
        text_color = (((param - 40 - 1) & 0x07) << 4) | (ansi_to_vga_colors[param - 40] & 0x0f);
        break;
      }
      case ANSI_SGR_SWAP : {
        text_color = ((text_color & 0x0f) << 4) | ((text_color & 0xf0) >> 4);
        break;
      }
    }
  }
}

size_t handle_csi_seq(const char *str) {
  memfill((u8p)work_buf, 0, 200);
  str++;
  const char *start = str;
  char *end = (char *)start;
  size_t idx = 0;
  size_t param_count = 0;
  
  for(; *end < 0x40; ++end); // any [a-zA-Z] character is definitely over 0x40

  // printf("Start = %x\n", (u32)start);
  // printf("End = %x\n", (u32)end);

  for(; idx < ((size_t)end - (size_t)start) && idx < 199; work_buf[idx] = start[idx], idx++); // copy over
  // printf("Work buffer = \"%s\"\n", work_buf);
 // 
  // printf("End char = '%c'\n", *end);
  if (*start == '?') goto rt; // screw this, private CSI sequence
                              // and i don't regret using `goto` any bit this time

  split_string(work_buf, ";", csi_params_pre, 32, &param_count);
  // printf("String is split into %u parameters:\n", param_count);
  

  // reduce, reuse, recycle!
  for (idx = 0; idx < param_count; idx++) {
    // printf("%s -", csi_params_pre[idx]);
    csi_params[idx] = atoi_k(csi_params_pre[idx]);
    // printf("> %u", csi_params[idx]);
  }

  switch (*end) {
    case ANSI_CUU :
    case ANSI_CUD :
    case ANSI_CUF :
    case ANSI_CUB : { // for now
      cursor_move_a(*end, csi_params[0], param_count);
      break;
    }
    case ANSI_SGR : {
      handle_sgr(csi_params, param_count);
      break;
    }
 }  
  
rt:return (size_t)end - (size_t)start;
}

size_t handle_esc_seq(const char *str) {
  // printf("Found an escape sequence\n");
  str++;
  const char *start = str;
  char *end = (char *)start;
  switch (*start) {
    case ANSI_CSI : {
      end += handle_csi_seq(str);
      break;
    }
    case ANSI_DCS :
    case ANSI_OSC :
    default : {
      break;
    }
  }
  return (size_t)end - (size_t)start + 3;
} // ret: length of escape sequence

// better terminal print function
void tprint(const char *str) {
  while (str[str_index]) {
    if (str[str_index] == '\e')
      str_index += handle_esc_seq(&str[str_index]);
    else {
      putc(str[str_index], text_color);
      str_index++;
    }
  }
  str_index = 0;
}


