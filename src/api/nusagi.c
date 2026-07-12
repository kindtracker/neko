#include "neko.h"

int neko_init(lua_State *L) {
  lua_pushnumber(L, DEFAULT_WIDTH);
  lua_setfield(L, -2, "GAME_W");
  lua_pushnumber(L, DEFAULT_HEIGHT);
  lua_setfield(L, -2, "GAME_H");

  lua_pushnumber(L, DEFAULT_WIDTH * 2);
  lua_setfield(L, -2, "WINDOW_H");
  lua_pushnumber(L, DEFAULT_HEIGHT * 2);
  lua_setfield(L, -2, "WINDOW_H");

  lua_pushstring(L, "linux");
  lua_setfield(L, -2, "PLATFORM");
  return 0;
}

int usagi_init(lua_State *L) {
  nlog("Loading: nusagi API");

  lua_newtable(L);
  neko_init(L);
  lua_setglobal(L, "neko");

  lua_newtable(L);
  neko_init(L);
  lua_setglobal(L, "usagi");
  return 0;
}
