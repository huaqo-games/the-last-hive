COMPILER = gcc

C_FLAG_STD_C99             = -std=c99              # Use the C99 language standard
C_FLAG_DEBUG_INFO          = -g                    # Include debug information
# C_FLAG_HEADERS 		       = -H					   # Prints paths of all headers
C_FLAG_ALL_WARNINGS        = -Wall                 # Enable most common warning
C_FLAG_PEDANTIC            = -Wpedantic            # Enforce ISO C standard strictly
C_FLAG_SHADOW              = -Wshadow              # Warn if a local variable shadows another
C_FLAG_STRICT_PROTOS       = -Wstrict-prototypes   # Warn if function declarations are missing parameter types
C_FLAG_NO_UNKNOWN_PRAGMAS  = -Wno-unknown-pragmas  # Suppress warnings about unknown pragmas
C_FLAGS = \
    $(C_FLAG_STD_C99) \
    $(C_FLAG_DEBUG_INFO) \
	$(C_FLAG_HEADERS) \
    $(C_FLAG_ALL_WARNINGS) \
    $(C_FLAG_PEDANTIC) \
    $(C_FLAG_SHADOW) \
    $(C_FLAG_STRICT_PROTOS) \
    $(C_FLAG_NO_UNKNOWN_PRAGMAS)

INCLUDE_FLAGS = -Iinclude

EXTERNAL_ENGINE = -Iexternal/engine
EXTERNAL_RAYGUI = -Iexternal/raygui 
EXTERNAL_RINI = -Iexternal/rini
EXTERNAL_FLAGS = \
	$(EXTERNAL_ENGINE) \
	$(EXTERNAL_RINI) \
	$(EXTERNAL_RAYGUI)

GAME_NAME = the-last-hive


ifeq ($(OS), Windows_NT)
	SRC = src\main.c
	TARGET = bin\win\$(GAME_NAME).exe
	RAYLIB_FLAGS = -I%RAYLIB% -L%RAYLIB% -lraylib -lopengl32 -lgdi32 -lwinmm
else
	SRC = src/main.c 
	TARGET = bin/osx/$(GAME_NAME)
	RAYLIB_FLAGS = $(shell pkg-config --libs --cflags raylib)
endif

$(shell mkdir -p bin/osx bin/win)

build: $(SRC)
	$(COMPILER) $(SRC) -o $(TARGET) $(C_FLAGS) $(INCLUDE_FLAGS) $(EXTERNAL_FLAGS) $(RAYLIB_FLAGS) 

clean:
	rm -f $(TARGET)

run: clean build
	./$(TARGET)

stats:
	cloc . \
	--exclude-dir=raygui,rini,bin,assets,.vscode,.github \
	--not-match-f='(Makefile|\.gitignore)'
