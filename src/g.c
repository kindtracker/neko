#include "neko.h"

int ginit_window(const char *title) {
  InitWindow(676, 724, title);
}

int ginit() {
  SetTraceLogLevel(LOG_NONE);
}
