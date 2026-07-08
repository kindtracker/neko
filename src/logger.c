#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "neko.h"

void nexit(int ret) {
  exit(ret);
}

void nlog(const char *format, ...) {
  printf("[neko] \x1b[92m");
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n\x1b[0m");
}

void nwarning(const char *format, ...) {
  printf("[neko] \x1b[93m");
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n\x1b[0m");
}

void nerror(const char *format, ...) {
  printf("[neko] \x1b[91m");
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n\x1b[0m");
}

void nfatal(const char *format, ...) {
  printf("[neko] \x1b[91m");
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n\x1b[0m");
  nexit(1);
}
