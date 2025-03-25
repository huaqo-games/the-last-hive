#include <raylib.h>
#include "../include/raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include "engine/screen.h"
#include "engine/display.h"
#include "engine/applicationstate.h"
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

int main(void)
{
    Display display = {
        .name = "The Last Hive",
        .width = 1280,
        .height = 720
    };

    InitWindow(display.width, display.height, display.name); 
    InitAudioDevice(); 

    Application app;
    app.state.currentScreen = MENU;
    app.state.running = true;
    app.state.gameStarted = false;
    app.display = display;
    app.font = LoadFont("assets/SproutLandsUI/fonts/pixelFont-7-8x14-sproutLands.fnt");

    SetTextureFilter(app.font.texture, TEXTURE_FILTER_POINT);
    SetTraceLogLevel(LOG_NONE);
    
    InitLogo(&app.logo);
    InitMenu(&app.menu);
    InitGame(&app.game,&app.display);

    while (app.state.running)
    {
        switch (app.state.currentScreen)
        {
            case LOGO:
            {
                UpdateLogo(&app.logo, &app.state);
                RenderLogo(&app.logo);
            }break;
            case MENU:
            {
                UpdateMenu(&app.menu, &app.state);
                RenderMenu(&app.menu, &app.font, app.display.name);
            }break;
            case GAMEPLAY:
            {
                UpdateGame(&app.game, &app.state);
                RenderGame(&app.game);
            }break;
            default: break;
        } 
    }
    CleanupGame(&app.game);
    UnloadFont(app.font);
    CloseWindow();
    return 0;
}
