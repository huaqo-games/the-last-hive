#ifndef APP_H
#define APP_H

#include <config.h>
#include <display.h>

#include "screen.h"
#include "applicationstate.h"
#include "font.h"
#include "logo.h"
#include "menu.h"
#include "game.h"

typedef struct {
    Config config;
    State state;
    Display display;
    Font font;
    LogoState logo;
    GameState game;
    MenuState menu;
} Application;

void ConfigApp(Application* app){
    InitConfig(&app->config, "config/config.ini");
    app->state.currentScreen = GetConfigInt(&app->config, "startScreen");
    app->state.running = true;
    app->state.gameStarted = false;
    app->state.flagFPS =  GetConfigInt(&app->config, "showFPS");
    app->display.title = GetConfigString(&app->config, "display_title");
    app->display.width = GetConfigInt(&app->config, "display_width");
    app->display.height = GetConfigInt(&app->config, "display_height");
}

void InitApp(Application *app){
    InitFont(&app->font);
    InitLogo(&app->logo);
    InitMenu(&app->menu);
    InitGame(&app->game,&app->display);
}

void UpdateApp(Application *app){
    while (app->state.running)
    {
        switch (app->state.currentScreen)
        {
            case LOGO:
            {
                UpdateLogo(&app->logo, &app->state);
                RenderLogo(&app->logo, &app->state);
            }break;
            case MENU:
            {
                UpdateMenu(&app->menu, &app->state);
                RenderMenu(&app->menu, &app->state, &app->font, app->display.title);
            }break;
            case GAMEPLAY:
            {
                UpdateGame(&app->game, &app->state);
                RenderGame(&app->game, &app->state);
            }break;
            default: break;
        } 
    }
}

void CleanupApp(Application *app){
    CleanupMenu(&app->menu);
    CleanupGame(&app->game);
    CleanupFont(&app->font);
}

#endif //APP_H
