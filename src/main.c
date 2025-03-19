#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine/screen.h"
#include "engine/settings.h"
#include "engine/applicationstate.h"
#include "game/logo.h"
#include "game/menu.h"
#include "game/game.h"

typedef struct {
    State state;
    Settings settings;
    LogoState logo;
    GameState game;
    MenuState menu;
} Application;

int main(void)
{
    Application app;
    app.state.currentScreen = LOGO;
    app.state.running = true;
    app.state.gameStarted = false;
    app.settings = (Settings){
        .name = "The Last Hive",
        .screenWidth = 1280,
        .screenHeight = 720
    };

    InitWindow(app.settings.screenWidth, app.settings.screenHeight, app.settings.name); 

    InitLogo(&app.logo);
    InitMenu(&app.menu);
    InitGame(&app.game);

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
                RenderMenu(&app.menu);
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
    CloseWindow();
    return 0;
}
