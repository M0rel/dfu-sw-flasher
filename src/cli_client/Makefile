CC = gcc
CCFLAGS = -Wall -Wpedantic
SRCS = cli_client.c
LDFLAGS =
TARGET = cli-dfu-sw-flasher

all:
	$(CC) $(SRCS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -rf $(TARGET)
