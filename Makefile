COMPILER = clang
C_FLAGS = -std=c99 -g -Wall -Werror -Wpedantic -Wconversion -Wshadow -Wstrict-prototypes -fsanitize=address,undefined -O0 -I../include
SUPPRESSED_FLAGS = -Wno-conversion -Wno-sign-conversion -Wno-unused-variable -Wno-unused-but-set-variable
RAYLIB_FLAGS = $(shell pkg-config --libs --cflags raylib)
SRC = src/main.c 
TARGET = bin/game

build: $(TARGET)
$(TARGET): $(SRC)
	$(COMPILER) $(C_FLAGS) $(RAYLIB_FLAGS) $(SRC) -o $(TARGET) $(SUPPRESSED_FLAGS)

clean:
	rm -f $(TARGET)

run: clean build
	./$(TARGET)