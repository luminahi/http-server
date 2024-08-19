CC = gcc
BIN = main.out
MAIN_SRC = ./src/main.c
HTTP_SRC = ./src/lib/http.c

# default target
all: $(BIN)

# build main
$(BIN): $(MAIN_SRC) $(HTTP_SRC)
	$(CC) $^ -o $@
