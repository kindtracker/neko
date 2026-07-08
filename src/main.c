#include <stdio.h>
#include <string.h>

#include "neko.h"

int lua_run(lua_State *L, int narg, int nret) {
  int ret = lua_pcall(L, narg, nret, 0);
  if (ret != 0) {
    const char *err = lua_tostring(L, -1);
    nerror(err);
  }
  return ret;
}

int neko_launch(const char *fname) {
  nlog("Launching: %s", fname);
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  luaL_loadfile(L, fname);
  gfx_init(L);
  
  nlog("Initializing Lua state");
  lua_run(L, 0, 0);
  nlog("Lua loaded");

  nlog("Searching for _init function");
  lua_getglobal(L, "_init");
  if (lua_isfunction(L, -1)) {
    nlog("Found _init function, running it");
    lua_run(L, 0, 0);
  } else {
    lua_pop(L, 1);
    nlog("_init function not found");
  }

  nlog("Searching for _update function");
  bool _updatee = false;
  lua_getglobal(L, "_update");
  if (lua_isfunction(L, -1)) {
    nlog("Found _update function");
    _updatee = true;
  } else {
    nlog("_update function not found");
  }
  lua_pop(L, 1);
  
  nlog("Searching for _draw function");
  bool _drawe = false;
  lua_getglobal(L, "_draw");
  if (lua_isfunction(L, -1)) {
    nlog("Found _draw function");
    _drawe = true;
  } else {
    nwarning("_draw function not found");
  }
  lua_pop(L, 1);

  ginit_window("Neko");
  gset_fps(24);
  while (!gshould_stop()) {
    gbegin();
    if (_drawe) {
      lua_getglobal(L, "_draw");
      lua_run(L, 0, 0);
    }
    gend();
  }
  lua_close(L);
  gclose_window();
  return 0;
}

int main(int argc, char **argv) {
  nlog("Neko %s", RELEASE_STRING);

  char *fname = "main.lua";
  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];
    const char *dot = strrchr(arg, '.');
    if (dot && !strcmp(dot, ".lua")) {
      fname = (char *)arg;   
    }
  }

  ginit();
  neko_launch(fname);
  return 0;
}
