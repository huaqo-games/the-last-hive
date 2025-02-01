#include "raylib.h"
#include "Game.h"

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif

Game game;

void UpdateDrawFrame() {
    game.update();
    game.render();
}

int main() {
    InitWindow(1280, 720, "Lazy Bee");
    SetTargetFPS(60);
    game.init();
#ifdef PLATFORM_WEB
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    while (!WindowShouldClose()) { game.update(); game.render(); }
#endif
    game.close();
    return 0;
}
