#include "neko.h"

int neko_quit(lua_State *L) {
  uint8_t s = luaL_checknumber(L, 1);
  luas = malloc(256);
  sprintf(luas, "exit %d", s);
  return 0;
}

static int neko_launch(lua_State *L) {
  const char *fname = luaL_optstring(L, 1, running_fname);
  luas = malloc(256);
  sprintf(luas, "launch %s", fname);
  return 0;
}

int neko_measure_text(lua_State *L) {
  const char *text = luaL_checkstring(L, 1);
  float fs = luaL_optnumber(L, 2, 1.0f);
  Vector2 size = gmeasure_text(text, fs);
  lua_pushnumber(L, size.x);
  lua_pushnumber(L, size.y);
  return 2;
}

int neko_update(lua_State *L) {
  lua_pushnumber(L, gelapsed());
  lua_setfield(L, -2, "elapsed");
  return 0;
}

int nusagi_update(lua_State *L) {
  lua_getglobal(L, "neko");
  neko_update(L);
  lua_setglobal(L, "neko");
  
  lua_getglobal(L, "usagi");
  neko_update(L);
  lua_setglobal(L, "usagi");
  
  return 0;
}

int neko_init(lua_State *L) {
  lua_pushnumber(L, DEFAULT_WIDTH);
  lua_setfield(L, -2, "GAME_W");
  lua_pushnumber(L, DEFAULT_HEIGHT);
  lua_setfield(L, -2, "GAME_H");

  lua_pushnumber(L, DEFAULT_WIDTH * 2);
  lua_setfield(L, -2, "WINDOW_W");
  lua_pushnumber(L, DEFAULT_HEIGHT * 2);
  lua_setfield(L, -2, "WINDOW_H");

  lua_pushstring(L, "linux");
  lua_setfield(L, -2, "PLATFORM");

  lua_pushboolean(L, is_dev);
  lua_setfield(L, -2, "IS_DEV");
  lua_pushboolean(L, !is_dev);
  lua_setfield(L, -2, "IS_RELEASE");

  lua_pushcfunction(L, neko_measure_text);
  lua_setfield(L, -2, "measure_text");
  lua_pushcfunction(L, neko_launch);
  lua_setfield(L, -2, "launch");
  lua_pushcfunction(L, neko_quit);
  lua_setfield(L, -2, "quit");
  return 0;
}

int nusagi_init(lua_State *L) {
  nlog("Loading: nusagi API");

  lua_newtable(L);
  neko_init(L);
  lua_setglobal(L, "neko");

  lua_newtable(L);
  neko_init(L);
  lua_setglobal(L, "usagi");
  return 0;
}
