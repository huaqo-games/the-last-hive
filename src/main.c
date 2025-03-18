#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine/screen.h"
#include "engine/settings.h"
#include "game/logo.h"
#include "game/menu.h"
#include "game/game.h"

int main(void)
{

    typedef struct {
        Screen currentScreen;
        bool running;
        bool gameStarted;
        Settings settings;
        LogoState logo;
        GameState game;
        MenuState menu;
    } Application;

    Application app;
    app.currentScreen = LOGO;
    app.running = true;
    app.gameStarted = false;
    app.settings = (Settings){
        .name = "The Last Hive",
        .screenWidth = 1280,
        .screenHeight = 720
    };

    InitWindow(app.settings.screenWidth, app.settings.screenHeight, app.settings.name); 

    InitLogo(&app.logo);
    InitMenu(&app.menu);
    InitGame(&app.game);

    while (app.running)
    {
        switch (app.currentScreen)
        {
            case LOGO:
            {
                UpdateLogo(&app.logo,&app.currentScreen);
                RenderLogo(&app.logo);
            }break;
            case MENU:
            {
                UpdateMenu(&app.menu, &app.currentScreen, &app.running, &app.gameStarted);
                RenderMenu(&app.menu);
            }break;
            case GAMEPLAY:
            {
                UpdateGame(&app.game, &app.currentScreen, &app.running, &app.gameStarted);
                RenderGame(&app.game);
            }break;
            default: break;
        } 
    }
    CleanupGame(&app.game);
    CloseWindow();
    return 0;
}
