#pragma once
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "raylib.h"

#define RELEASE_STRING "v0.1.0"

typedef struct { int r, g, b; } gfx_color;

void nlog(const char *format, ...);
void nwarning(const char *format, ...);
void nerror(const char *format, ...);
void nfatal(const char *format, ...);

int ginit_window(const char *title);
int gclose_window();
int gset_fps(int fps);
float gdelta_time();
double gelapsed();
bool gshould_stop();
int ginit();
int gbegin();
int gend();
int gclear(int r, int g, int b);
int gtext(const char *text, int x, int y, int fs, int ro, int r, int g, int b, int a);
int grect(int x, int y, int w, int h, int thick, int r, int g, int b, int a);
int grect_fill(int x, int y, int w, int h, int r, int g, int b, int a);
int gcirc(int x, int y, int t, int ra, int r, int g, int b, int a);
int gcirc_fill(int x, int y, int ra, int r, int g, int b, int a);
int gline(int x1, int y1, int x2, int y2, int t, int r, int g, int b, int a);
int gtri(int x1, int y1, int x2, int y2, int x3, int y3, int t, int r, int g, int b, int a);
int gtri_fill(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a);

int gfx_init(lua_State *L);

extern Font font;
