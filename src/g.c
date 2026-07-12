#include "neko.h"

Font font;

void ginit_window(const char *title) {
  InitWindow(DEFAULT_WIDTH * 2, DEFAULT_HEIGHT * 2, title);
}

void gclose_window() {
  CloseWindow();
}

float gdelta_time() {
  return GetFrameTime(); 
}

double gelapsed() {
  return GetTime(); 
}

void gset_fps(int fps) {
  SetTargetFPS(fps);
}

bool gshould_stop() {
  return WindowShouldClose();
}

Vector2 gmeasure_text(const char *text, int fs) {
  return MeasureTextEx(font, text, 1000000.0f, 6);
}

void gtext(const char *text, int x, int y, int fs, int ro, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  Vector2 origin = (Vector2){0, 0};
  if (ro != 0.0f) {
    Vector2 textsz = gmeasure_text(text, fs);
    origin = (Vector2){textsz.x / 2.0f, textsz.y / 2.0f};
  }
  DrawTextPro(font, text, (Vector2){x, y}, origin, ro, fs * 10, 6, c);
} 

void grect(int x, int y, int w, int h, int t, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  Rectangle rect = {x, y, w, h};
  DrawRectangleLinesEx(rect, t, c);
}

void grect_fill(int x, int y, int w, int h, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawRectangle(x, y, w, h, c);
}

void gcirc(int x, int y, int t, int ra, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  for (int i = 0; i < t; i++) {
    DrawCircleLines(x, y, ra - i, c);
  }
}

void gcirc_fill(int x, int y, int ra, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawCircle(x, y, ra, c);
}

void gline(int x1, int y1, int x2, int y2, int t, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawLineEx((Vector2){x1, y1}, (Vector2){x2, y2}, t, c);
}

void gtri(int x1, int y1, int x2, int y2, int x3, int y3, int t, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  DrawLineEx((Vector2){x1, y1}, (Vector2){x2, y2}, t, c);
  DrawLineEx((Vector2){x2, y2}, (Vector2){x3, y3}, t, c);
  DrawLineEx((Vector2){x3, y3}, (Vector2){x1, y1}, t, c);
}

void gtri_fill(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a) {
  Color c = {r, g, b, a};
  Vector2 v1 = (Vector2){x1, y1};
  Vector2 v2 = (Vector2){x2, y2};
  Vector2 v3 = (Vector2){x3, y3};
  DrawTriangle(v1, v2, v3, c);
}

void gclear(int r, int g, int b){
  Color c = {r, g, b, 255};
  ClearBackground(c);
}

void gbegin() {
  BeginDrawing();
}

void gend() {
  EndDrawing();
}

Font load_font_from_file(const char *filepath, int fontSize) {
  // Read file into memory
  FILE *file = fopen(filepath, "rb");
  if (!file) {
    nerror("Can't open font file: %s", filepath);
    return GetFontDefault();
  }
  
  // Get file size
  fseek(file, 0, SEEK_END);
  long filesize = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  // Read into buffer
  unsigned char *buffer = malloc(filesize);
  fread(buffer, 1, filesize, file);
  fclose(file);
  
  // Load from memory
  Font font = LoadFontFromMemory(".ttf", buffer, (int)filesize, fontSize, NULL, 0);
  
  free(buffer);
  
  return font;
}

int ginit_platform() {
  SetTraceLogLevel(LOG_NONE);
  return 0;
}

int ginit() {
  SetTraceLogLevel(LOG_NONE);

  const char *expanded = expand_path("~/.neko/assets/monogram-extended.ttf");
  nlog("Loading: font: %s", expanded);
  font = LoadFont(expanded);

  if (font.texture.id == 0) {
    nerror("Couldn't load font: %s", expanded);
    nwarning("Loading default font: raylib font");
    font = GetFontDefault();
  }
  return 0;
}

const key_mapping_t key_table[] = {
    {"KEY_0", KEY_ZERO},
    {"KEY_1", KEY_ONE},
    {"KEY_2", KEY_TWO},
    {"KEY_3", KEY_THREE},
    {"KEY_4", KEY_FOUR},
    {"KEY_5", KEY_FIVE},
    {"KEY_6", KEY_SIX},
    {"KEY_7", KEY_SEVEN},
    {"KEY_8", KEY_EIGHT},
    {"KEY_9", KEY_NINE},

    {"KEY_A", KEY_A},
    {"KEY_B", KEY_B},
    {"KEY_C", KEY_C},
    {"KEY_D", KEY_D},
    {"KEY_E", KEY_E},
    {"KEY_F", KEY_F},
    {"KEY_G", KEY_G},
    {"KEY_H", KEY_H},
    {"KEY_I", KEY_I},
    {"KEY_J", KEY_J},
    {"KEY_K", KEY_K},
    {"KEY_L", KEY_L},
    {"KEY_M", KEY_M},
    {"KEY_N", KEY_N},
    {"KEY_O", KEY_O},
    {"KEY_P", KEY_P},
    {"KEY_Q", KEY_Q},
    {"KEY_R", KEY_R},
    {"KEY_S", KEY_S},
    {"KEY_T", KEY_T},
    {"KEY_U", KEY_U},
    {"KEY_V", KEY_V},
    {"KEY_W", KEY_W},
    {"KEY_X", KEY_X},
    {"KEY_Y", KEY_Y},
    {"KEY_Z", KEY_Z},
    
    {"KEY_F1", KEY_F1},
    {"KEY_F2", KEY_F2},
    {"KEY_F3", KEY_F3},
    {"KEY_F4", KEY_F4},
    {"KEY_F5", KEY_F5},
    {"KEY_F6", KEY_F6},
    {"KEY_F7", KEY_F7},
    {"KEY_F8", KEY_F8},
    {"KEY_F9", KEY_F9},
    {"KEY_F10", KEY_F10},
    {"KEY_F11", KEY_F11},
    {"KEY_F12", KEY_F12},
    
    {"KEY_SPACE", KEY_SPACE},
    {"KEY_ENTER", KEY_ENTER},
    {"KEY_ESCAPE", KEY_ESCAPE},
    {"KEY_TAB", KEY_TAB},
    {"KEY_BACKSPACE", KEY_BACKSPACE},
    {"KEY_DELETE", KEY_DELETE},

    {"KEY_LEFT", KEY_LEFT},
    {"KEY_RIGHT", KEY_RIGHT},
    {"KEY_UP", KEY_UP},
    {"KEY_DOWN", KEY_DOWN},
    
    {"KEY_LEFT", KEY_A},
    {"KEY_RIGHT", KEY_D},
    {"KEY_UP", KEY_W},
    {"KEY_DOWN", KEY_S},
    
    {"KEY_LSHIFT", KEY_LEFT_SHIFT},
    {"KEY_RSHIFT", KEY_RIGHT_SHIFT},
    {"KEY_LCTRL", KEY_LEFT_CONTROL},
    {"KEY_RCTRL", KEY_RIGHT_CONTROL},
    {"KEY_LALT", KEY_LEFT_ALT},
    {"KEY_RALT", KEY_RIGHT_ALT},
    {"KEY_BACKTICK", KEY_GRAVE},
    {"KEY_MINUS", KEY_MINUS},
    {"KEY_EQUAL", KEY_EQUAL},
    {"KEY_LBRACKET", KEY_LEFT_BRACKET},
    {"KEY_RBRACKET", KEY_RIGHT_BRACKET},
    {"KEY_BACKSLASH", KEY_BACKSLASH},
    {"KEY_SEMICOLON", KEY_SEMICOLON},
    {"KEY_APOSTROPHE", KEY_APOSTROPHE},
    {"KEY_COMMA", KEY_COMMA},
    {"KEY_PERIOD", KEY_PERIOD},
    {"KEY_SLASH", KEY_SLASH},
};
const size_t key_table_len = sizeof(key_table) / sizeof(key_table[0]);
