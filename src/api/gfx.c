#include "neko.h"

int gfx_text(lua_State *L) {
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

  lua_pushcfunction(L, gfx_text);
  lua_setfield(L, -2, "text");

  return 0;
}
