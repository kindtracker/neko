# Neko - an advanced version of [Usagi](https://codeberg.org/brettchalupa/usagi)

Neko is a small, cross-platform game framework for creating pixel art games. 
It provides a Lua API built on raylib.

## Features

- **Drop-in replacement for Usagi with additional features** You can use same API from Usagi and Neko at same time
- **Ports.** Write games once in Lua, run on desktop and 3DS without code changes. (You cant do this yet)

## Install

Linux:
```sh
cd /tmp/ 
git clone https://github.com/kindtracker/neko.git 
cd neko
make
```

## Getting started
### Hello world
Create `main.lua`:
```lua
function _draw()
  gfx.clear(gfx.COLOR_BLACK)
  gfx.text("Hello, World!", 10, 10, gfx.COLOR_WHITE)
end
```
### Run it 
```sh
neko main.lua
```

## Feedback and issues
Open an issue for feedback, requests, and bugs. You can make a pull request to other requests if possible.

## Platforms
- **Nintendo 3DS** - In 1 or 2 weeks

## Lua API 
This shows only changes from Usagi's API to Neko's API
Lua version: [Lua 5.5]((https://www.lua.org/manual/5.5/))

### Cheatsheet
Neko is not done yet

```lua
-- Info
-- You can use usagi API as neko API
-- usagi.GAME_W -> neko.GAME_W
neko.GAME_W -- default: 320 
neko.GAME_H -- default: 240
neko.WINDOW_W -- default: 640
neko.WINDOW_H -- default: 480
neko.PLATFORM -- "linux"

-- Callbacks
_config()
_init()
_update()
_draw()

-- Graphics

gfx.clear(color)
gfx.text(text, x, y, color?, alpha?)
gfx.text_ex(text, x, y, scale, rotation, color?, alpha?)
gfx.rect(x, y, w, h, color?, alpha?)
gfx.rect_fill(x, y, w, h, color?, alpha?)
gfx.rect_ex(x, y, w, h, thickness, color?, alpha?)
gfx.circ(x, y, r, color?, alpha?)
gfx.circ_fill(x, y, r, color?, alpha?)
gfx.circ_ex(x, y, r, thickness, color?, alpha?)
gfx.line(x1, y1, x2, y2, color?, alpha?)
gfx.line_ex(x1, y1, x2, y2, thickness, color?, alpha?)
gfx.tri(x1, y1, x2, y2, x3, y3, color?, alpha?)
gfx.tri_fill(x1, y1, x2, y2, x3, y3, color?, alpha?)
gfx.tri_ex(x1, y1, x2, y2, x3, y3, thickness, color?, alpha?)
gfx.px(x, y, color, alpha?)
gfx.get_px(x, y) -- removed (returns 0, 0, 0, 0)
gfx.pal(idx, r, g, b) 
gfx.get_pal(idx) -- returns (r, g, b)

-- Palette (PICO-8, 16 colors)

gfx.COLOR_TRUE_WHITE
gfx.COLOR_BLACK, gfx.COLOR_DARK_BLUE, gfx.COLOR_DARK_PURPLE, gfx.COLOR_DARK_GREEN
gfx.COLOR_BROWN, gfx.COLOR_DARK_GRAY, gfx.COLOR_LIGHT_GRAY, gfx.COLOR_WHITE
gfx.COLOR_RED,   gfx.COLOR_ORANGE,    gfx.COLOR_YELLOW,     gfx.COLOR_GREEN
gfx.COLOR_BLUE,  gfx.COLOR_INDIGO,    gfx.COLOR_PINK,       gfx.COLOR_PEACH

```

### `gfx`

- `color` argument - default is -1
- `gfx.tri_ex` same as `gfx.tri` but with thickness
- `gfx.pal` - set a custom color in the palette (below -1 is not allowed)
- `gfx.get_pal` - returns color from the palette

## Roadmap

- [ ] Add input API.
- [ ] Add image API.
- [ ] Add effects API.
- [ ] Add sfx API
- [ ] You can use same API from Usagi and Neko at same time.
- [ ] Write games once in Lua, run on desktop and 3DS without code changes.

## Credits
Neko is written in C.

- **Raylib** - Neko uses [Raylib](https://raylib.com) to make graphics, inputs, audio, etc

- **Lua** - [Lua](https://lua.org/) is the scripting language for Neko

- **monogram-extended** the bundled font (`assets/monogram-extended.ttf`)

(Un)license
Neko's source code is dedicated to the public domain. You can see the full details in [UNLICENSE](https://github.com/kindtracker/neko/blob/main/UNLICENSE).
