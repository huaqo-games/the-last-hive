COMPILER = clang
C_FLAGS = -std=c99 -g -Wall -Werror -Wpedantic -Wconversion -Wshadow -Wstrict-prototypes -fsanitize=address,undefined -O0 
RAYLIB_FLAGS = $(shell pkg-config --libs --cflags raylib)
SRC = scripts/main.c 
TARGET = bin/game

build: $(TARGET)
$(TARGET): $(SRC)
	$(COMPILER) $(FLAGS) $(RAYLIB_FLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: clean build
	./$(TARGET)