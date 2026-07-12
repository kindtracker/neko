#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "neko.h"

bool is_dev = false;
char *running_fname;
char *luas;

int lua_run(lua_State *L, int narg, int nret) {
  int ret = lua_pcall(L, narg, nret, 0);
  
  if (ret != 0) {
    const char *err = lua_tostring(L, -1);
    nerror(err);
    lua_pop(L, 1);
  }
  
  return ret;
}

/*static int traceback_handler(lua_State *L) {
  lua_getglobal(L, "debug");
  lua_getfield(L, -1, "traceback");
  lua_pushvalue(L, 1);
  lua_call(L, 1, 1);
  return 1;
}

int lua_run(lua_State *L, int narg, int nret) {
  int hpos = lua_gettop(L) - narg;
  lua_pushcfunction(L, traceback_handler);
  lua_insert(L, hpos);

  int ret = lua_pcall(L, narg, nret, hpos);  
  if (ret != 0) {
    const char *err = lua_tostring(L, -1);
    nerror(err);
    lua_pop(L, 1);
  }
  lua_remove(L, hpos);
  return ret;
}*/

int neko_launch(const char *fname) {
  nlog("Launching: %s", fname);
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  
  int ret = luaL_loadfile(L, fname);
  if (ret != 0) {
    const char *err = lua_tostring(L, -1);
    nerror(err);
    lua_pop(L, 1);
  }

  gfx_init(L);
  nusagi_init(L);
  input_init(L);
  
  nlog("Initializing Lua state");
  lua_run(L, 0, 0);
  nlog("Lua loaded");

  nlog("Searching for _init function");
  lua_getglobal(L, "_init");
  if (lua_isfunction(L, -1)) {
    nlog("Found _init function, running it");
    lua_run(L, 0, 0);
  } else {
    nlog("_init function not found");
  }
  lua_pop(L, 1);

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
    // nusagi_update(L);
    if (_updatee) {
      lua_getglobal(L, "_update");
      lua_run(L, 0, 0);
    }
    if (_drawe) {
      lua_getglobal(L, "_draw");
      lua_run(L, 0, 0);
    }

    if (luas) {
      char lfname[256];
      uint8_t status;
      if (sscanf(luas, "launch %255s", lfname) == 1) {
        gclose_window();
        neko_launch(lfname);
        ginit_window("Neko");
        gset_fps(24);
      } else if (sscanf(luas, "exit %d", &status) == 1) {
        gend();
        lua_close(L);
        gclose_window();
        return status;
      }

      luas = NULL;
    }
    running_fname = NULL;
    gend();
  }

  lua_close(L);
  gclose_window();
  return 0;
}

void usage(int ret) {
  printf("Usage: neko [COMMAND]\n");
  printf("\n");
  printf("Commands:\n");
  printf("  run            Run a game (default: main.lua)\n");
  printf("  dev            Run a game with developer mode (default: main.lua)\n");
  printf("\n");
  printf("Options:\n");
  printf("  -h, --help     Print help\n");
  printf("  -v, --version  Print version\n");
  exit(ret);
}

int main(int argc, char **argv) {
  nlog("Neko %s", RELEASE_STRING);

  char *fname = "main.lua";
  if (argc == 3) {
    if (strcmp(argv[1], "run") == 0) {
      fname = argv[2];
    } else if (strcmp(argv[1], "dev") == 0) {
      fname = argv[2];
      is_dev = true;
    }
  } else if (argc == 2) {
    if (strcmp(argv[1], "run") == 0) {
      fname = "main.lua";
    } else if (strcmp(argv[1], "dev") == 0) {
      fname = "main.lua";
      is_dev = true;
    } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
      usage(0);
    } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
      return 0;
    }
  } else {
    usage(0);
  }
  running_fname = fname;

  ginit();
  neko_launch(fname);
  return 0;
}
