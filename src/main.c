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
    Settings settings = {
        .name = "The Last Hive",
        .screenWidth = 1280,
        .screenHeight = 720
    };

    InitWindow(settings.screenWidth, settings.screenHeight, settings.name); 
    
    Screen currentScreen = GAMEPLAY;
    LogoState logo;
    GameState game;
    MenuState menu;

    InitLogo(&logo);
    InitMenu(&menu);
    InitGame(&game);

    while (true)
    {
        switch (currentScreen)
        {
            case LOGO:
            {
                UpdateLogo(&logo,&currentScreen);
                RenderLogo(&logo);
            }break;
            case MENU:
            {
                UpdateMenu(&menu, &currentScreen);
                RenderMenu(&menu);
            }break;
            case GAMEPLAY:
            {
                UpdateGame(&game, &currentScreen);
                RenderGame(&game);
            }break;
            default: break;
        } 
    }
    CleanupGame(&game);
    CloseWindow();
    return 0;
}
