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
    
    Screen currentScreen = LOGO;
    LogoState logo;
    GameState game;
    MenuState menu;

    initLogo(&logo);
    initMenu(&menu);
    initGame(&game);

    while (!WindowShouldClose())
    {
        switch (currentScreen)
        {
            case LOGO:
            {
                updateLogo(&logo,&currentScreen);
                renderLogo(&logo);
            }break;
            case MENU:
            {
                updateMenu(&menu, &currentScreen);
                renderMenu(&menu);
            }break;
            case GAMEPLAY:
            {
                updateGame(&game);
                renderGame(&game);
            }break;
            default: break;
        } 
    }
    cleanupGame(&game);
    CloseWindow();
    return 0;
}
