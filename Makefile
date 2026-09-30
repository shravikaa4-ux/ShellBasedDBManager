kCC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = src/main.c \
      src/input.c \
      src/parser.c

TARGET = bin/dbmanager

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -rf bin/*

.PHONY: all run clean
