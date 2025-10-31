#ifndef APP_H
#define APP_H

#include <engine.h>

#include "appState.h"
#include "appSettings.h"
#include "appColors.h"

#include "appLogo.h"
#include "appMenu.h"
#include "appGame.h"

typedef struct {
    Config config;
    State state;
    Flags flags;
    Window window;
    Font font;
    LogoState logo;	
    MenuState menu;
    GameState game;
} App;

void ConfigApp(App* app){
    InitConfig(&app->config, "config/config.ini");
    app->state.currentView = GetConfigInt(&app->config, "startView");
    app->flags.showFPS =  GetConfigInt(&app->config, "showFPS");
	app->flags.soundtrackOn = GetConfigInt(&app->config, "soundtrackOn");
    app->window.title = GetConfigString(&app->config, "window_title");
    app->window.width = GetConfigInt(&app->config, "window_width");
    app->window.height = GetConfigInt(&app->config, "window_height");
}

void InitApp(App *app){
    InitFont(&app->font, "assets/font.fnt");
    InitLogo(&app->logo);
    InitMenu(&app->menu);
    InitGame(&app->game,&app->window);
}

void UpdateApp(App *app){

    app->state.running = true;
    app->state.gameStarted = false;

    while (app->state.running)
    {
        switch (app->state.currentView)
        {
            case LOGO:
            {
                UpdateLogo(&app->logo, &app->state.currentView, &app->state.running);
                RenderLogo(&app->logo, &app->flags);
            }break;
            case MENU:
            {
                UpdateMenu(&app->menu, &app->state, &app->flags);
                RenderMenu(&app->menu, &app->font, app->window.title, &app->flags);
            }break;
            case GAMEPLAY:
            {
                UpdateGame(&app->game, &app->state, &app->flags);
                RenderGame(&app->game, &app->state, &app->flags);
            }break;
            default: break;
        } 
    }
}

void CleanupApp(App *app){
    CleanupMenu(&app->menu);
    CleanupGame(&app->game);
    CleanupFont(&app->font);
    CleanUpConfig(&app->config);
}

#endif //APP_H
