CC = gcc
CCFLAGS = -Wall -Wpedantic -fpic
LDFLAGS = -lusb-1.0

TARGET = dfu-usb
TARGET_SO = lib$(TARGET).so
TARGET_A = lib$(TARGET).a
SRCS = dfu_usb.c logger.c
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
	$(CC) $(CFLAGS) -c $< -o $(OUT)/$@

clean:
	rm -rf $(OUT)/*.o
	rm -rf $(OUT)/*.a
	rm -rf $(OUT)/*.so
