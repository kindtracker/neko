#include "neko.h"

int input_pressed(lua_State *L) {
  int key = luaL_checknumber(L, 1);
  lua_pushboolean(L, IsKeyPressed(key));
  return 1;
}

int input_held(lua_State *L) {
  int key = luaL_checknumber(L, 1);
  lua_pushboolean(L, IsKeyDown(key));
  return 1;
}

int input_released(lua_State *L) {
  int key = luaL_checknumber(L, 1);
  lua_pushboolean(L, IsKeyReleased(key));
  return 1;
}

int input_init(lua_State *L) {
  nlog("Loading: input API");

  lua_newtable(L);

  for (int i = 0; i < key_table_len; i++) {
    lua_pushnumber(L, key_table[i].key);
    lua_setfield(L, -2, key_table[i].name);
  }

  lua_pushcfunction(L, input_pressed);
  lua_setfield(L, -2, "pressed");
  lua_pushcfunction(L, input_held);
  lua_setfield(L, -2, "held");
  lua_pushcfunction(L, input_released);
  lua_setfield(L, -2, "released");

  lua_setglobal(L, "input");
  return 0;
}
