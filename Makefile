CXX = clang
EMCC = emcc
FLAGS = -std=c99 -g -Wall -Werror -Wpedantic -Wconversion -Wshadow -Wstrict-prototypes -fsanitize=address,undefined -O0 $(shell pkg-config --libs --cflags raylib)
SRC = scripts/main.c 

# ARM Build
ARM_TARGET = bin/game
arm: $(ARM_TARGET)
$(ARM_TARGET): $(SRC)
	$(CXX) $(FLAGS) $(SRC) -o $(ARM_TARGET)

# Web Build
WEB_TARGET = bin/game.js
EMFLAGS = -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 \
          --preload-file assets -DPLATFORM_WEB -gsource-map -s ASSERTIONS=2
RAYLIB_WEB_PATH = web-includes
web: $(WEB_TARGET)
$(WEB_TARGET): $(SRC)
	$(EMCC) -Wall -std=c++17 -I/opt/homebrew/include -L$(RAYLIB_WEB_PATH) \
	-lraylib.web $(SRC) -o $(WEB_TARGET) $(EMFLAGS)

# Clean
clean:
	rm -f $(ARM_TARGET) $(WEB_TARGET)

# Run ARM Build
run: clean arm
	./$(ARM_TARGET)

# Serve Web Build
serve: web
	python3 -m http.server
