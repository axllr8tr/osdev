#ifndef _ESCAPE_H
#define _ESCAPE_H

#include "../include/defs.h"

#define ASCII_NUL 0x00 // null (^@)                // string terminator
#define ASCII_SOH 0x01 // start of heading
#define ASCII_STX 0x02 // start of text
#define ASCII_ETX 0x03 // end of text (^C)         // interrupt signal
#define ASCII_EOT 0x04 // end of transmission (^D) // EOF
#define ASCII_ENQ 0x05 // end of query
#define ASCII_ACK 0x06 // acknowledge
#define ASCII_BEL 0x07 // bell ('\a')
#define ASCII_BS  0x08 // backspace ('\b')
#define ASCII_HT  0x09 // horizontal tabulation ('\t')
#define ASCII_LF  0x0a // linefeed ('\n')
#define ASCII_VT  0x0b // vertical tabulation ('\v')
#define ASCII_FF  0x0c // formfeed ('\f', ^L)      // clear screen
#define ASCII_CR  0x0d // carriage return ('\r')
#define ASCII_SO  0x0e // shift out
#define ASCII_SI  0x0f // shift in
#define ASCII_DLE 0x10 // data link escape
#define ASCII_DC1 0x11 // device control 1
#define ASCII_DC2 0x12 // device control 2
#define ASCII_DC3 0x13 // device control 3
#define ASCII_DC4 0x14 // device control 4
#define ASCII_NAK 0x15 // negative ack
#define ASCII_SYN 0x16 // synchronize
#define ASCII_ETB 0x17 // end tx block
#define ASCII_CAN 0x18 // cancel
#define ASCII_EM  0x19 // end of medium
#define ASCII_SUB 0x1a // substitute
#define ASCII_ESC 0x1b // escape ('\e', ^[)
#define ASCII_FS  0x1c // file separator
#define ASCII_CRT 0x1c // (or cursor right)
#define ASCII_GS  0x1d // group separator
#define ASCII_CLF 0x1d // (or cursor left)
#define ASCII_RS  0x1e // record separator
#define ASCII_CUP 0x1e // (or cursor up)
#define ASCII_US  0x1f // unit separator
#define ASCII_CDN 0x1f // (or cursor down)
#define ASCII_DEL 0x7f // delete
#define ASCII_CSI 0x9b // control sequence introducer (same as \e[)
#define ASCII_DCS 0x90 // device control string (same as \eP)
#define ASCII_OSC 0x9d // os command (same as \e])

// ansi escape sequence prefixes
#define ANSI_CSI '['
#define ANSI_OSC ']'
#define ANSI_DCS 'P'


#define ANSI_ED_END    0
#define ANSI_ED_START  1
#define ANSI_ED_ENTIRE 2

#define ANSI_EL_END    0
#define ANSI_EL_START  1
#define ANSI_EL_ENTIRE 2

#define ANSI_SGR_RESET        0
#define ANSI_SGR_INTENSITY    1
#define ANSI_SGR_COLOR_FG(u)  30 + (u & 7)
#define ANSI_SGR_COLOR_BG(u)  40 + (u & 7)
#define ANSI_SGR_SWAP         7
#define ANSI_SGR_HIDDEN       8
#define ANSI_SGR_INTENSITY_BG 5 // aka blinking


// for now, no support for civis and cnorm



// ansi escape sequence suffixes
#define ANSI_CUU 'A'
#define ANSI_CUD 'B'
#define ANSI_CUF 'C'
#define ANSI_CUB 'D'
#define ANSI_CNL 'E'
#define ANSI_CPL 'F'
#define ANSI_CHA 'G'
#define ANSI_CUP 'H'
#define ANSI_ED  'J'
#define ANSI_EL  'K'
#define ANSI_SU  'S'
#define ANSI_SD  'T'
#define ANSI_HVP 'f'
#define ANSI_SGR 'm'
#define ANSI_SCP 's'
#define ANSI_RCP 'u'

#endif /* _ESCAPE_H */

