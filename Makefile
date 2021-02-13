CC = gcc
CFLAGS = -Wall

TARGET = main.o

SRC = $(src/*.c)

all:
	$(CC) $(CFLAGS) src/*.c -o $(TARGET)
debug:
	$(CC) $(CFLAGS) -g -D DEBUG=1 src/*.c -o $(TARGET)
clean:
	rm -rf $(TARGET)
	rm -rf *.o
