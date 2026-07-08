#include <stdio.h>
#include <string.h>

#include "neko.h"

int neko_launch(const char *fname) {
  nlog("Launching: %s", fname);
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  luaL_loadfile(L, fname);
  gfx_init(L);

  ginit_window("Neko");
}

int main(int argc, char **argv) {
  nlog("Neko %s", RELEASE_STRING);

  char *fname = "main.lua";
  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];
    char *dot = strrchr(arg, '.');
    if (dot && !strcmp(dot, ".lua")) {
      fname = arg;   
    }
  }

  ginit();
  neko_launch("test");
  return 0;
}
