LFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC=src/main.c src/actors.c  src/collections.c src/game.c src/misc.c
HEADERS= src/include/actors.h src/include/defaults.h src/include/collections.h src/include/types.h src/include/game.h src/include/misc.h
CC=gcc
CFLAGS=-Wall -Wextra
BIN=bin/void



$(BIN): $(SRC) $(HEADERS)
	$(CC) -o $(BIN) $(CFLAGS) $(SRC) $(LFLAGS)

run: $(SRC) $(HEADERS) $(BIN)
	$(BIN)

clean: 
	rm $(BIN)
