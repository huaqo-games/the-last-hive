#include <raylib.h>
#include <raymath.h>
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
    LogoState logo;
    GameState game;
    MenuState menu;
} Application;

int main(void)
{
    Application app;
    app.state.currentScreen = GAMEPLAY;
    app.state.running = true;
    app.state.gameStarted = false;
    app.display.name = "The Last Hive";
    app.display.width = 1280;
    app.display.height = 720;

    InitWindow(app.display.width, app.display.height, app.display.name); 

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
