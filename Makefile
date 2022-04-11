LFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC=src/main.c src/actors.c  src/collections.c src/game.c
HEADERS= src/actors.h src/defaults.h src/collections.h src/types.h src/game.h
CC=gcc
CFLAGS=-Wall -Wextra
BIN=bin/void



$(BIN): $(SRC) $(HEADERS)
	$(CC) -o $(BIN) $(CFLAGS) $(SRC) $(LFLAGS)

run: $(SRC) $(HEADERS) $(BIN)
	$(BIN)

clean: 
	rm $(BIN)
