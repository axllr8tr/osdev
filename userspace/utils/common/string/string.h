#include "../include/defs.h"

void split_string_into_tokens(char *src, const char *delim, char **destv, size_t destc_max, size_t *destc_real);
bool char_matches_any(char c, const char *s);
int strcmp(const char *l, const char *r);
char *strchr(const char *s, int c);
size_t strlen(const char *s);
char *strcat(char *d, const char *s);
char *strtok(char *s, const char *del);
