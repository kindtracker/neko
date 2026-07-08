#pragma once
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "raylib.h"

#define RELEASE_STRING "v0.1.0"

void nlog(const char *format, ...);
void nwarning(const char *format, ...);
void nerror(const char *format, ...);
void nfatal(const char *format, ...);

int ginit_window(const char *title);
int ginit();

int gfx_init(lua_State *L);
