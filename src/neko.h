#pragma once
#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "raylib.h"

#define RELEASE_STRING "v0.1.0"

#define DEFAULT_WIDTH  320
#define DEFAULT_HEIGHT 240

typedef struct { int r, g, b; } gfx_color;

typedef struct { 
  const char* name;
  int key;
} key_mapping_t;

void nlog(const char *format, ...);
void nwarning(const char *format, ...);
void nerror(const char *format, ...);
void nfatal(const char *format, ...);

int ginit();
int ginit_platform();
void ginit_window(const char *title);
void gclose_window();
void gset_fps(int fps);
float gdelta_time();
double gelapsed();
bool gshould_stop();
void gbegin();
void gend();
Vector2 gmeasure_text(const char *text, int fs);
void gclear(int r, int g, int b);
void gtext(const char *text, int x, int y, int fs, int ro, int r, int g, int b, int a);
void grect(int x, int y, int w, int h, int thick, int r, int g, int b, int a);
void grect_fill(int x, int y, int w, int h, int r, int g, int b, int a);
void gcirc(int x, int y, int t, int ra, int r, int g, int b, int a);
void gcirc_fill(int x, int y, int ra, int r, int g, int b, int a);
void gline(int x1, int y1, int x2, int y2, int t, int r, int g, int b, int a);
void gtri(int x1, int y1, int x2, int y2, int x3, int y3, int t, int r, int g, int b, int a);
void gtri_fill(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a);

int gfx_init(lua_State *L);
int nusagi_init(lua_State *L);
int input_init(lua_State *L);
int nusagi_update(lua_State *L);

extern Font font;
extern bool is_dev;
extern char *luas;
extern char *running_fname;
extern const key_mapping_t key_table[];
extern const size_t key_table_len;

static char* expand_path(const char *path) {
  if (path[0] != '~') return (char*)path;
  
  const char *home = getenv("HOME");
  if (!home) return (char*)path;
  
  static char expanded[256];
  snprintf(expanded, sizeof(expanded), "%s%s", home, path + 1);
  return expanded;
}
