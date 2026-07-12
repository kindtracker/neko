#include "neko.h"

int neko_quit(lua_State *L) {
  uint8_t s = luaL_checknumber(L, 1);
  char buffer[256];
  sprintf(buffer, "exit %d", s);
  luas = buffer;
  return 0;
}

static int neko_launch(lua_State *L) {
  const char *fname = luaL_optstring(L, 1, running_fname);
  char buffer[256];
  sprintf(buffer, "launch %s", fname);
  luas = buffer;
  return 0;
}

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

  lua_pushcfunction(L, neko_launch);
  lua_setfield(L, -2, "launch");
  lua_pushcfunction(L, neko_quit);
  lua_setfield(L, -2, "quit");
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
