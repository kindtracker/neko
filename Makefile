CC = cc
CFLAGS = -Wall -Wextra -Isrc
LIBS = -lm -lraylib

ASSETS = assets
SRC = src lua-5.5.0/src
BUILD = build
OUT = $(BUILD)/neko

CSRC = $(shell find $(SRC) -type f -name '*.c' | grep -v -E '(lua|luac)\.c')
COBJ = $(patsubst %.c,$(BUILD)/%.o,$(CSRC))

PREFIX ?= $(HOME)/.neko
INSTALL_BIN = $(PREFIX)/bin
INSTALL_DATA = $(PREFIX)/

all: compile install

clean:
	mkdir -p $(BUILD)
	rm -rf $(BUILD)/*

compile: $(OUT)
	cp -R $(ASSETS) $(BUILD)/.

install: $(OUT)
	mkdir -p $(INSTALL_BIN) $(INSTALL_DATA)
	cp $(OUT) $(INSTALL_BIN)/neko
	cp -R $(ASSETS) $(INSTALL_DATA)/.

	@echo ""
	@echo "Installation complete!"
	@echo "Add this to your shell profile:"
	@echo "  export PATH=\$$HOME/.neko/bin:\$$PATH"
	@echo ""

uninstall:
	rm -f $(INSTALL_BIN)/neko
	rm -rf $(INSTALL_DATA)

$(OUT): $(COBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(COBJ) $(LIBS)

$(BUILD)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
