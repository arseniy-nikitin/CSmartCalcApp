#include "s21_strnstr.h"

char *s21_strnstr(const char *s, const char *find, size_t slen) {
  char c, sc;
  size_t len;
  if ((c = *find++) != '\0') {
    len = strlen(find);
    do {
      do {
        if ((sc = *s++) == '\0' || slen-- < 1) return (NULL);
      } while (sc != c);
      if (len > slen) return (NULL);
    } while (s21_strncmp(s, find, len) != 0);
    s--;
  }
  return ((char *)s);
}

int s21_strncmp(const char *s1, const char *s2, size_t n) {
  if (n == 0) return (0);
  do {
    if (*s1 != *s2++) return (*(unsigned char *)s1 - *(unsigned char *)--s2);
    if (*s1++ == 0) break;
  } while (--n != 0);
  return (0);
}