#include "neko.h"

Font font;

void ginit_window(const char *title) {
  InitWindow(640, 400, title);
}

void gclose_window() {
  CloseWindow();
}

float gdelta_time() {
  return GetFrameTime(); 
}

double gelapsed() {
  return GetTime(); 
}

void gset_fps(int fps) {
  SetTargetFPS(fps);
}

bool gshould_stop() {
  return WindowShouldClose();
}

void gtext(const char *text, int x, int y, int fs, int ro, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  Vector2 origin = (Vector2){0, 0};
  if (ro != 0.0f) {
    Vector2 textsz = MeasureTextEx(font, text, fs * 10, 6);
    origin = (Vector2){textsz.x / 2.0f, textsz.y / 2.0f};
  }
  DrawTextPro(font, text, (Vector2){x, y}, origin, ro, fs * 10, 6, c);
} 

void grect(int x, int y, int w, int h, int t, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  Rectangle rect = {x, y, w, h};
  DrawRectangleLinesEx(rect, t, c);
}

void grect_fill(int x, int y, int w, int h, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawRectangle(x, y, w, h, c);
}

void gcirc(int x, int y, int t, int ra, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  for (int i = 0; i < t; i++) {
    DrawCircleLines(x, y, ra - i, c);
  }
}

void gcirc_fill(int x, int y, int ra, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawCircle(x, y, ra, c);
}

void gline(int x1, int y1, int x2, int y2, int t, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawLineEx((Vector2){x1, y1}, (Vector2){x2, y2}, t, c);
}

void gtri(int x1, int y1, int x2, int y2, int x3, int y3, int t, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawLineEx((Vector2){x1, y1}, (Vector2){x2, y2}, t, c);
  DrawLineEx((Vector2){x2, y2}, (Vector2){x3, y3}, t, c);
  DrawLineEx((Vector2){x3, y3}, (Vector2){x1, y1}, t, c);
}

void gtri_fill(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  Vector2 v1 = (Vector2){x1, y1};
  Vector2 v2 = (Vector2){x2, y2};
  Vector2 v3 = (Vector2){x3, y3};
  DrawTriangle(v1, v2, v3, c);
}

void gclear(int r, int g, int b){
  Color c = {r, g, b, 255};
  ClearBackground(c);
}

void gbegin() {
  BeginDrawing();
}

void gend() {
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
