#include <stdlib.h> 
#include "neko.h"

int scale_x = 2;
int scale_y = 2;
int scale = 2;

gfx_color clr_pallete[] = {
  [0]  = { 255, 255, 255 }, // COLOR_TRUE_WHITE
  [1]  = { 0,   0,   0   }, // COLOR_BLACK
  [2]  = { 29,  43,  83  }, // COLOR_DARK_BLUE
  [3]  = { 126, 37,  83  }, // COLOR_DARK_PURPLE
  [4]  = { 0,   135, 81  }, // COLOR_DARK_GREEN
  [5]  = { 171, 82,  54  }, // COLOR_BROWN
  [6]  = { 95,  87,  79  }, // COLOR_DARK_GRAY
  [7]  = { 194, 195, 199 }, // COLOR_LIGHT_GRAY
  [8]  = { 255, 241, 232 }, // COLOR_WHITE
  [9]  = { 255, 0,   77  }, // COLOR_RED
  [10] = { 255, 163, 0   }, // COLOR_ORANGE
  [11] = { 255, 236, 39  }, // COLOR_YELLOW
  [12] = { 0,   228, 54  }, // COLOR_GREEN
  [13] = { 41,  173, 255 }, // COLOR_BLUE
  [14] = { 131, 118, 156 }, // COLOR_INDIGO
  [15] = { 255, 119, 168 }, // COLOR_PINK
  [16] = { 255, 204, 170 }, // COLOR_PEACH
};

gfx_color get_color(int num) {
  return clr_pallete[num];
}

int gfx_clear(lua_State *L) {
  int color = (int)luaL_checknumber(L, 1);
  gfx_color c = get_color(color);
  gclear(c.r, c.g, c.b);
}

int gfx_text(lua_State *L) {
  const char *text = luaL_checkstring(L, 1);
  float x = luaL_checknumber(L, 2) * scale_x;
  float y = luaL_checknumber(L, 3) * scale_y;
  int color = (int)luaL_checknumber(L, 4);
  int a = luaL_optnumber(L, 5, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  gtext(text, x, y, scale, 0, c.r, c.g, c.b, a);
  return 1;
}

int gfx_text_ex(lua_State *L) {
  const char *text = luaL_checkstring(L, 1);
  float x = luaL_checknumber(L, 2) * scale_x;
  float y = luaL_checknumber(L, 3) * scale_y;
  float s = luaL_checknumber(L, 4);
  float r = luaL_checknumber(L, 5);
  int color = (int)luaL_checknumber(L, 6);
  int a = luaL_optnumber(L, 7, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  float cr = r * 57.2958f;
  gtext(text, x, y, scale * s, cr, c.r, c.g, c.b, a);
  return 1;
}

int gfx_init(lua_State *L) {
  nlog("Loading: gfx API");
  lua_newtable(L);

  struct {
    const char *name;
    int idx;
  } colors[] = {
    { "COLOR_TRUE_WHITE", 0 },
    { "COLOR_BLACK", 1 },
    { "COLOR_DARK_BLUE", 2 },
    { "COLOR_DARK_PURPLE", 3 },
    { "COLOR_DARK_GREEN", 4 },
    { "COLOR_BROWN", 5 },
    { "COLOR_DARK_GRAY", 6 },
    { "COLOR_LIGHT_GRAY", 7 },
    { "COLOR_WHITE", 8 },
    { "COLOR_RED", 9 },
    { "COLOR_ORANGE", 10 },
    { "COLOR_YELLOW", 11 },
    { "COLOR_GREEN", 12 },
    { "COLOR_BLUE", 13 },
    { "COLOR_INDIGO", 14 },
    { "COLOR_PINK", 15 },
    { "COLOR_PEACH", 16 },
  };

  for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
    lua_pushnumber(L, colors[i].idx);
    lua_setfield(L, -2, colors[i].name);
  }

  lua_pushcfunction(L, gfx_clear);
  lua_setfield(L, -2, "clear");
  lua_pushcfunction(L, gfx_text);
  lua_setfield(L, -2, "text");
  lua_pushcfunction(L, gfx_text_ex);
  lua_setfield(L, -2, "text_ex");
  
  lua_setglobal(L, "gfx");
  return 0;
}
