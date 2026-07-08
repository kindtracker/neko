#include "neko.h"

Font font;

int ginit_window(const char *title) {
  InitWindow(640, 400, title);
  return 0;
}

int gtext(const char *text, int x, int y, int fs, int ro, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawTextPro(font, text, (Vector2){x, y}, (Vector2){0, 0}, ro, fs * 10, 6, c);
  return 0;
}

int gbegin() {
  BeginDrawing();
}

int gend() {
  EndDrawing();
}

int ginit() {
  SetTraceLogLevel(LOG_NONE);
  nlog("Loading: font assets/monogram-extended.ttf");
  font = LoadFont("assets/monogram-extended.ttf");
  if (font.glyphCount == 0) {
    nfatal("Couldn't load default font: assets/monogram-extended.ttf");
  }
  return 0;
}
