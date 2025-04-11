#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/raymath.h"
#include "app.h"

int main(void)
{
    Application app;
    InitApp(&app);

    InitWindow(app.display.width, app.display.height, app.display.name); 
    InitAudioDevice(); 

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
                RenderLogo(&app.logo, &app.state);
            }break;
            case MENU:
            {
                UpdateMenu(&app.menu, &app.state);
                RenderMenu(&app.menu, &app.state, &app.font, app.display.name);
            }break;
            case GAMEPLAY:
            {
                UpdateGame(&app.game, &app.state);
                RenderGame(&app.game, &app.state);
            }break;
            default: break;
        } 
    }
    CleanupMenu(&app.menu);
    CleanupGame(&app.game);
    UnloadFont(app.font);
    CloseWindow();
    return 0;
}
