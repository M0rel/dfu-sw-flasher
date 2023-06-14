CC = gcc
CCFLAGS = -Wall -Wpedantic
SRCS = core.c logger.c
LDFLAGS = -lusb-1.0
TARGET = dfu-sw-flasher

all:
	$(CC) $(SRCS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -rf $(TARGET)
