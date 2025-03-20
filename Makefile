COMPILER = gcc
C_FLAGS = -std=c99 -g -Wall -Werror -Wpedantic -Wshadow -Wstrict-prototypes

ifeq ($(OS), Windows_NT)
	SRC = src\main.c
	TARGET = bin\win\game.exe
	RAYLIB_FLAGS = -I%RAYLIB% -L%RAYLIB% -lraylib -lopengl32 -lgdi32 -lwinmm
else
	SRC = src/main.c 
	TARGET = bin/osx/game
	RAYLIB_FLAGS = $(shell pkg-config --libs --cflags raylib)
endif

build: $(SRC)
	$(COMPILER) $(SRC) -o $(TARGET) $(C_FLAGS) $(RAYLIB_FLAGS)

clean:
	rm -f $(TARGET)

run: clean build
	.\$(TARGET)