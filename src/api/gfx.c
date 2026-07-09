#include <stdlib.h> 
#include <string.h>
#include "neko.h"

int scale_x = 2;
int scale_y = 2;
int scale = 2;

gfx_color sel_color = {0, 0, 0}; 

gfx_color default_color_pal[] = {
  [0]  = { 255, 255, 255 }, // COLOR_TRUE_WHITE
  [1]  = { 0,   0,   0   }, // COLOR_BLACK
  [2]  = { 29,  43,  83  }, // COLOR_DARK_BLUE
  [3]  = { 126, 37,  83  }, // COLOR_DARK_PURPLE
  [4]  = { 0,   135, 81  }, // COLOR_DARK_GREEN
  [5]  = { 171, 82,  54  }, // COLOR_BROWN
  [6]  = { 95,  87,  79  }, // COLOR_DARK_GRAY
  [7]  = { 194, 195, 199 }, // COLOR_LIGHT_GRAY
  [8]  = { 255, 241, 232 }, // COLOR_WHITE
  [9]  = { 255, 0,   77  }, // COLOR_RED
  [10] = { 255, 163, 0   }, // COLOR_ORANGE
  [11] = { 255, 236, 39  }, // COLOR_YELLOW
  [12] = { 0,   228, 54  }, // COLOR_GREEN
  [13] = { 41,  173, 255 }, // COLOR_BLUE
  [14] = { 131, 118, 156 }, // COLOR_INDIGO
  [15] = { 255, 119, 168 }, // COLOR_PINK
  [16] = { 255, 204, 170 }, // COLOR_PEACH
};

gfx_color *color_pal = NULL;

size_t color_pal_size = 17;

gfx_color get_color(int num) {
  if (num < -1) {
    nerror("get_color: invalid index %d", num);
    return (gfx_color){255, 0, 255};
  }
  if (num == -1) {
    return sel_color;
  }
  return color_pal[num];
}

int gfx_clear(lua_State *L) {
  int color = (int)luaL_optnumber(L, 1, -1);
  gfx_color c = get_color(color);
  gclear(c.r, c.g, c.b);
  return 0;
}

int gfx_text(lua_State *L) {
  const char *text = luaL_checkstring(L, 1);
  float x = luaL_checknumber(L, 2) * scale_x;
  float y = luaL_checknumber(L, 3) * scale_y;
  int color = (int)luaL_optnumber(L, 4, -1);
  int a = luaL_optnumber(L, 5, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  gtext(text, x, y, scale, 0, c.r, c.g, c.b, a);
  return 0;
}

int gfx_text_ex(lua_State *L) {
  const char *text = luaL_checkstring(L, 1);
  float x = luaL_checknumber(L, 2) * scale_x;
  float y = luaL_checknumber(L, 3) * scale_y;
  float s = luaL_checknumber(L, 4);
  float r = luaL_checknumber(L, 5);
  int color = (int)luaL_optnumber(L, 6, -1);
  int a = luaL_optnumber(L, 7, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  float cr = r * 57.2958f;
  gtext(text, x, y, scale * s, cr, c.r, c.g, c.b, a);
  return 0;
}

int gfx_rect(lua_State *L) {
  float x = luaL_checknumber(L, 1) * scale_x;
  float y = luaL_checknumber(L, 2) * scale_y;
  float w = luaL_checknumber(L, 3) * scale_x;
  float h = luaL_checknumber(L, 4) * scale_y;
  int color = (int)luaL_optnumber(L, 5, -1);
  int a = luaL_optnumber(L, 6, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  grect(x, y, w, h, scale, c.r, c.g, c.b, a);
  return 0;
}

int gfx_rect_fill(lua_State *L) {
  float x = luaL_checknumber(L, 1) * scale_x;
  float y = luaL_checknumber(L, 2) * scale_y;
  float w = luaL_checknumber(L, 3) * scale_x;
  float h = luaL_checknumber(L, 4) * scale_y;
  int color = (int)luaL_optnumber(L, 5, -1);
  int a = luaL_optnumber(L, 6, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  grect_fill(x, y, w, h, c.r, c.g, c.b, a);
  return 0;
}

int gfx_rect_ex(lua_State *L) {
  float x = luaL_checknumber(L, 1) * scale_x;
  float y = luaL_checknumber(L, 2) * scale_y;
  float w = luaL_checknumber(L, 3) * scale_x;
  float h = luaL_checknumber(L, 4) * scale_y;
  float t = luaL_checknumber(L, 5);
  int color = (int)luaL_optnumber(L, 6, -1);
  int a = luaL_optnumber(L, 7, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  grect(x, y, w, h, t, c.r, c.g, c.b, a);
  return 0;
}

int gfx_circ(lua_State *L) {
  float x = luaL_checknumber(L, 1) * scale_x;
  float y = luaL_checknumber(L, 2) * scale_y;
  float r = luaL_checknumber(L, 3) * scale;
  int color = (int)luaL_optnumber(L, 4, -1);
  int a = luaL_optnumber(L, 5, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  gcirc(x, y, scale, r, c.r, c.g, c.b, a);
  return 0;
}

int gfx_circ_fill(lua_State *L) {
  float x = luaL_checknumber(L, 1) * scale_x;
  float y = luaL_checknumber(L, 2) * scale_y;
  float r = luaL_checknumber(L, 3) * scale;
  int color = (int)luaL_optnumber(L, 4, -1);
  int a = luaL_optnumber(L, 5, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  gcirc_fill(x, y, r, c.r, c.g, c.b, a);
  return 0;
}

int gfx_circ_ex(lua_State *L) {
  float x = luaL_checknumber(L, 1) * scale_x;
  float y = luaL_checknumber(L, 2) * scale_y;
  float r = luaL_checknumber(L, 3) * scale;
  float t = luaL_checknumber(L, 4) * scale;
  int color = (int)luaL_optnumber(L, 5, -1);
  int a = luaL_optnumber(L, 6, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  gcirc(x, y, t, r, c.r, c.g, c.b, a);
  return 0;
}

int gfx_line(lua_State *L) {
  float x1 = luaL_checknumber(L, 1) * scale_x;
  float y1 = luaL_checknumber(L, 2) * scale_y;
  float x2 = luaL_checknumber(L, 3) * scale_x;
  float y2 = luaL_checknumber(L, 4) * scale_y;
  int color = (int)luaL_optnumber(L, 5, -1);
  int a = luaL_optnumber(L, 6, 1.0f) * 255.0f;
  gfx_color c = get_color(color);
  
  gline(x1, y1, x2, y2, scale, c.r, c.g, c.b, a);
  return 0;
}

int gfx_line_ex(lua_State *L) {
  float x1 = luaL_checknumber(L, 1) * scale_x;
  float y1 = luaL_checknumber(L, 2) * scale_y;
  float x2 = luaL_checknumber(L, 3) * scale_x;
  float y2 = luaL_checknumber(L, 4) * scale_y;
  float t = luaL_checknumber(L, 5) * scale;
  int color = (int)luaL_optnumber(L, 6, -1);
  int a = luaL_optnumber(L, 7, 1.0f) * 255.0f;
  gfx_color c = get_color(color);
  
  gline(x1, y1, x2, y2, t, c.r, c.g, c.b, a);
  return 0;
}

int gfx_tri(lua_State *L) {
  float x1 = luaL_checknumber(L, 1) * scale_x;
  float y1 = luaL_checknumber(L, 2) * scale_y;
  float x2 = luaL_checknumber(L, 3) * scale_x;
  float y2 = luaL_checknumber(L, 4) * scale_y;
  float x3 = luaL_checknumber(L, 5) * scale_x;
  float y3 = luaL_checknumber(L, 6) * scale_y;
  int color = (int)luaL_optnumber(L, 7, -1);
  int a = luaL_optnumber(L, 8, 1.0f) * 255.0f;
  gfx_color c = get_color(color);
  
  gtri(x1, y1, x2, y2, x3, y3, scale, c.r, c.g, c.b, a);
  return 0;
}

int gfx_tri_fill(lua_State *L) {
  float x1 = luaL_checknumber(L, 1) * scale_x;
  float y1 = luaL_checknumber(L, 2) * scale_y;
  float x2 = luaL_checknumber(L, 3) * scale_x;
  float y2 = luaL_checknumber(L, 4) * scale_y;
  float x3 = luaL_checknumber(L, 5) * scale_x;
  float y3 = luaL_checknumber(L, 6) * scale_y;
  int color = (int)luaL_optnumber(L, 7, -1);
  int a = luaL_optnumber(L, 8, 1.0f) * 255.0f;
  gfx_color c = get_color(color);
  
  gtri_fill(x1, y1, x2, y2, x3, y3, c.r, c.g, c.b, a);
  return 0;
}

int gfx_tri_ex(lua_State *L) {
  float x1 = luaL_checknumber(L, 1) * scale_x;
  float y1 = luaL_checknumber(L, 2) * scale_y;
  float x2 = luaL_checknumber(L, 3) * scale_x;
  float y2 = luaL_checknumber(L, 4) * scale_y;
  float x3 = luaL_checknumber(L, 5) * scale_x;
  float y3 = luaL_checknumber(L, 6) * scale_y;
  float t = luaL_checknumber(L, 7) * scale;
  int color = (int)luaL_optnumber(L, 8, -1);
  int a = luaL_optnumber(L, 9, 1.0f) * 255.0f;
  gfx_color c = get_color(color);
  
  gtri(x1, y1, x2, y2, x3, y3, t, c.r, c.g, c.b, a);
  return 0;
}

int gfx_px(lua_State *L) {
  float x = luaL_checknumber(L, 1) * scale_x;
  float y = luaL_checknumber(L, 2) * scale_y;
  int color = (int)luaL_optnumber(L, 3, -1);
  int a = luaL_optnumber(L, 4, 1.0f) * 255.0f;
  gfx_color c = get_color(color);

  grect_fill(x, y, scale_x, scale_y, c.r, c.g, c.b, a);
  return 0;
}

int gfx_get_px(lua_State *L) {
  float x = luaL_checknumber(L, 1) * scale_x;
  float y = luaL_checknumber(L, 2) * scale_y;
  lua_pushnumber(L, 0);
  lua_pushnumber(L, 0);
  lua_pushnumber(L, 0);
  lua_pushnumber(L, 0);
  return 4;
}

int gfx_pal(lua_State *L) {
  int idx = luaL_checknumber(L, 1);
  int r = luaL_checknumber(L, 2);
  int g = luaL_checknumber(L, 3);
  int b = luaL_checknumber(L, 4);
  
  if (idx == -1) {
    sel_color = (gfx_color){r, g, b};
  } else if (idx > -1) {
    if (idx > (int)color_pal_size) {
      int new_size = (color_pal_size + 1) * 2; 
      gfx_color *temp = realloc(color_pal, new_size * sizeof(gfx_color));
      if (!temp) {
        nerror("gfx.pal: memory allocation failed (%d -> %d)", color_pal_size, new_size);
        return 0;
      }

      for (int i = color_pal_size; i < new_size; i++) {
        temp[i] = (gfx_color){255, 0, 255};
      }
      color_pal = temp;
      color_pal_size = new_size;
    }
    color_pal[idx] = (gfx_color){r, g, b};
  } else {
    nerror("gfx.pal: color index below -1 is not allowed");
  }
  return 0;
}

int gfx_get_pal(lua_State *L) {
  int idx = luaL_checknumber(L, 1);
  if (idx == -1) {
    lua_pushnumber(L, sel_color.r);
    lua_pushnumber(L, sel_color.g);
    lua_pushnumber(L, sel_color.b);
    return 3; 
  } else if (idx > -1) {
    if (idx > (int)color_pal_size) {
      nerror("gfx.get_pal: index %d out of bounds (max %d)", idx, color_pal_size-1);
      lua_pushnumber(L, 255);
      lua_pushnumber(L, 0);
      lua_pushnumber(L, 255);
      return 3;
    }
    lua_pushnumber(L, color_pal[idx].r);
    lua_pushnumber(L, color_pal[idx].g);
    lua_pushnumber(L, color_pal[idx].b);
    return 3;
  } else {
    nerror("gfx.get_pal: color index below -1 is not allowed");
    lua_pushnumber(L, 255);
    lua_pushnumber(L, 0);
    lua_pushnumber(L, 255);
    return 3;
  }
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

  for (int i = 0; i < (int)(sizeof(colors) / sizeof(colors[0])); i++) {
    lua_pushnumber(L, colors[i].idx);
    lua_setfield(L, -2, colors[i].name);
  }

  color_pal = malloc(color_pal_size * sizeof(gfx_color));
  if (!color_pal) {
    nerror("Failed to allocate color palette");
    return 1;
  }
  memcpy(color_pal, default_color_pal, color_pal_size * sizeof(gfx_color));

  lua_pushcfunction(L, gfx_clear);
  lua_setfield(L, -2, "clear");
  lua_pushcfunction(L, gfx_text);
  lua_setfield(L, -2, "text");
  lua_pushcfunction(L, gfx_text_ex);
  lua_setfield(L, -2, "text_ex");
  lua_pushcfunction(L, gfx_rect);
  lua_setfield(L, -2, "rect");
  lua_pushcfunction(L, gfx_rect_fill);
  lua_setfield(L, -2, "rect_fill");
  lua_pushcfunction(L, gfx_rect_ex);
  lua_setfield(L, -2, "rect_ex");
  lua_pushcfunction(L, gfx_circ);
  lua_setfield(L, -2, "circ");
  lua_pushcfunction(L, gfx_circ_fill);
  lua_setfield(L, -2, "circ_fill");
  lua_pushcfunction(L, gfx_circ_ex);
  lua_setfield(L, -2, "circ_ex");
  lua_pushcfunction(L, gfx_line);
  lua_setfield(L, -2, "line");
  lua_pushcfunction(L, gfx_line_ex);
  lua_setfield(L, -2, "line_ex");
  lua_pushcfunction(L, gfx_tri);
  lua_setfield(L, -2, "tri");
  lua_pushcfunction(L, gfx_tri_fill);
  lua_setfield(L, -2, "tri_fill");
  lua_pushcfunction(L, gfx_tri_ex);
  lua_setfield(L, -2, "tri_ex");
  lua_pushcfunction(L, gfx_px);
  lua_setfield(L, -2, "px");
  lua_pushcfunction(L, gfx_pal);
  lua_setfield(L, -2, "pal");
  lua_pushcfunction(L, gfx_get_pal);
  lua_setfield(L, -2, "get_pal");
  
  lua_setglobal(L, "gfx");
  return 0;
}
