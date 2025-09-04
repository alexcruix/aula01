PROJECT := pic16f876a_lcd_demo
CHIP := 16F876A
SRC_DIR := src
BUILD_DIR := build
OUT_HEX := firmware.hex

# Adjust XC8 v2 toolchain path if needed; assumes xc8-cc in PATH
CC := xc8-cc
CFLAGS := --chip=$(CHIP) -O1
LDFLAGS :=

SRCS := $(wildcard $(SRC_DIR)/*.c)

.PHONY: all clean dirs

all: dirs $(OUT_HEX)

dirs:
	mkdir -p $(BUILD_DIR)

$(OUT_HEX): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $(OUT_HEX)

clean:
	rm -rf $(BUILD_DIR) $(OUT_HEX)

