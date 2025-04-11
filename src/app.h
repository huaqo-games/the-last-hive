#ifndef APP_H
#define APP_H

#include "engine/applicationstate.h"
#include "engine/display.h"
#include "engine/screen.h"
#include "game/logo.h"
#include "game/menu.h"
#include "game/game.h"

typedef struct {
    State state;
    Display display;
    Font font;
    LogoState logo;
    GameState game;
    MenuState menu;
} Application;

void InitApp(Application* app){
    app->state.currentScreen = LOGO;
    app->state.running = true;
    app->state.gameStarted = false;
    app->state.flagFPS = true;
    app->display = (Display){
        .name = "The Last Hive",
        .width = 1280,
        .height = 720
    };
    app->font = LoadFont("assets/SproutLandsUI/fonts/pixelFont-7-8x14-sproutLands.fnt");
}

#endif //APP_H
