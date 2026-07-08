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
int ginit();
int gbegin();
int gend();
int gtext(const char *text, int x, int y, int fs, int ro, int r, int g, int b, int a);

int gfx_init(lua_State *L);

extern Font font;
