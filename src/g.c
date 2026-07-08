#include "neko.h"

Font font;

int ginit_window(const char *title) {
  InitWindow(640, 400, title);
  return 0;
}

int gtext(const char *text, int x, int y, int fs, int ro, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  Vector2 origin = (Vector2){0, 0};
  if (ro != 0.0f) {
    Vector2 textsz = MeasureTextEx(font, text, fs * 10, 6);
    origin = (Vector2){textsz.x / 2.0f, textsz.y / 2.0f};
  }
  DrawTextPro(font, text, (Vector2){x, y}, origin, ro, fs * 10, 6, c);
  return 0;
} 

int grect(int x, int y, int w, int h, int thick, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  Rectangle rect = {x, y, w, h};
  DrawRectangleLinesEx(rect, thick, c);
  return 0;
}

int grect_fill(int x, int y, int w, int h, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawRectangle(x, y, w, h, c);
  return 0;
}

int gclear(int r, int g, int b){
  Color c = {r, g, b, 255};
  ClearBackground(c);
  return 0;
}

int gbegin() {
  BeginDrawing();
  return 0;
}

int gend() {
  EndDrawing();
  return 0;
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
