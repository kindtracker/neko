#include "neko.h"

int usagi_init(lua_State *L) {
  nlog("Loading: usagi API");
  lua_newtable(L);

  lua_setglobal(L, "usagi");
}
