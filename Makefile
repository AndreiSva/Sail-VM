CC = gcc
CFLAGS = -Wall -O2

VERSION = \"2020.b\"
TARGET = sailvm

SRC = $(src/*.c)

all:
	$(CC) $(CFLAGS) -D VERSION=$(VERSION) -D INTERACTIVE=1 src/*.c -o $(TARGET)
minimal:
	$(CC) $(CFLAGS) -D VERSION=$(VERSION) src/*.c -o $(TARGET)
debug:
	$(CC) $(CFLAGS) -g -D INTERACTIVE=1 src/*.c -fsanitize=address -o $(TARGET)
clean:
	rm -rf $(TARGET)
	rm -rf *.o
