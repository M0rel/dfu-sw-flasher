CC = gcc
CCFLAGS = -Wall -fpic -c
LDFLAGS = -lusb-1.0

THIRD_PARTY_PATH = ../../third-party
INCV_PATH = -I$(THIRD_PARTY_PATH)/list -I./public-inc

TARGET = dfu-usb
TARGET_SO = lib$(TARGET).so
TARGET_A = lib$(TARGET).a
SRCS = dfu_usb.c logger.c dfu_usb_error.c
OUT = out

# On MacOs there is issue when building with a -static flag
# (can't locate file for: -lcrt0.o)
# As so now redundant use just static library target
all: build-static #build-shared

build-shared: $(TARGET_SO)
build-static: $(TARGET_A)

#TODO: Use objects only from SRCS (not *.o)
$(TARGET_A): $(SRCS:.c=.o)
	ar rcs $(OUT)/$(TARGET_A) $(OUT)/*.o

$(TARGET_SO): $(SRCS:.c=.o)
	$(CC) -shared -o $(OUT)/$(TARGET_SO) $(OUT)/*.o

%.o: %.c
	$(CC) $(CCFLAGS) $(INCV_PATH) $< -o $(OUT)/$@

clean:
	rm -rf $(OUT)/*.o
	rm -rf $(OUT)/*.a
	rm -rf $(OUT)/*.so
