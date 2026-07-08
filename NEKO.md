### Cheatsheet

```lua
-- Info
neko.GAME_W -- default: 320 
neko.GAME_H -- default: 200
neko.WINDOW_W -- default: 676
neko.WINDOW_H -- default: 724
neko.PLATFORM -- "linux"

-- Callbacks
_config()
_init()
_update()
_draw()

-- Graphics

gfx.clear(color)
gfx.text(text, x, y, color, alpha?)
gfx.text_ex(text, x, y, scale, rotation, color, alpha)
gfx.rect(x, y, w, h, color, alpha?)
gfx.rect_fill(x, y, w, h, color, alpha?)
gfx.rect_ex(x, y, w, h, thickness, color, alpha?)
gfx.circ(x, y, r, color, alpha?)
gfx.circ_fill(x, y, r, color, alpha?)
gfx.circ_ex(x, y, r, thickness, color, alpha?)
gfx.line(x1, y1, x2, y2, color, alpha?)
gfx.line_ex(x1, y1, x2, y2, thickness, color, alpha?)
gfx.tri(x1, y1, x2, y2, x3, y3, color, alpha?)
gfx.tri_fill(x1, y1, x2, y2, x3, y3, color, alpha?)
gfx.px(x, y, color, alpha?)

-- Palette (PICO-8, 16 colors)

gfx.COLOR_TRUE_WHITE
gfx.COLOR_BLACK, gfx.COLOR_DARK_BLUE, gfx.COLOR_DARK_PURPLE, gfx.COLOR_DARK_GREEN
gfx.COLOR_BROWN, gfx.COLOR_DARK_GRAY, gfx.COLOR_LIGHT_GRAY, gfx.COLOR_WHITE
gfx.COLOR_RED,   gfx.COLOR_ORANGE,    gfx.COLOR_YELLOW,     gfx.COLOR_GREEN
gfx.COLOR_BLUE,  gfx.COLOR_INDIGO,    gfx.COLOR_PINK,       gfx.COLOR_PEACH

```
