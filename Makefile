CC = cc
CFLAGS = -O0 -Wall -Wextra -Isrc
LIBS = -lm -lraylib

ASSETS = assets
SRC = src lua-5.5.0/src
BUILD = build
OUT = $(BUILD)/neko

CSRC = $(shell find $(SRC) -type f -name '*.c' | grep -v -E '(lua|luac)\.c')
COBJ = $(patsubst %.c,$(BUILD)/%.o,$(CSRC))

all: compile

clean:
	mkdir -p $(BUILD)
	rm -rf $(BUILD)/*

compile: $(OUT)
	cp -R $(ASSETS) $(BUILD)/.

run:
	./$(OUT) examples/hello.lua

$(OUT): $(COBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(COBJ) $(LIBS)

$(BUILD)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
