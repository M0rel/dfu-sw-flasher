CC = gcc
CCFLAGS = -Wall -Wpedantic
LDFLAGS = -ldfu-usb -lusb-1.0
LIB_PATH = ../dfu_usb_lib/out

SRCS = cli_client.c
INCV_PATH = ../dfu_usb_lib/public-inc
TARGET = cli-dfu-sw-flasher
OUT = out

all:
	$(CC) $(SRCS) $(CCFLAGS) -I$(INCV_PATH) -L$(LIB_PATH) $(LDFLAGS) -o $(OUT)/$(TARGET)

clean:
	rm -rf $(OUT)/$(TARGET)
