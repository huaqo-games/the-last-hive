#ifndef APP_H
#define APP_H

#include <raylib.h>

#include <config.h>
#include <window.h>
#include "view.h"
#include "state.h"
#include "flags.h"
#include "font.h"
#include "logo.h"
#include "menu.h"
#include "game.h"

typedef struct {
    Config config;
    State state;
    Flags flags;
    Window window;
    Font font;
    LogoState logo;
    GameState game;
    MenuState menu;
} App;

void ConfigApp(App* app){
    InitConfig(&app->config, "config/config.ini");
    app->state.currentView = GetConfigInt(&app->config, "startView");
    app->state.running = true;
    app->state.gameStarted = false;
    app->flags.showFPS =  GetConfigInt(&app->config, "showFPS");
    app->window.title = GetConfigString(&app->config, "window_title");
    app->window.width = GetConfigInt(&app->config, "window_width");
    app->window.height = GetConfigInt(&app->config, "window_height");
    SetTraceLogLevel(GetConfigInt(&app->config, "log_level") );

    for (int i = 0; i < sizeof(raylibFlags) / sizeof(raylibFlags[0]); i++){
        int flagValue = GetConfigInt(&app->config, raylibFlags[i]);
        if (flagValue != 0) {
            SetConfigFlags(flagValue);
        }
    }
}

void InitApp(App *app){
    InitWindow(app->window.width, app->window.height, app->window.title); 
    InitAudioDevice(); 
    InitFont(&app->font);
    InitLogo(&app->logo);
    InitMenu(&app->menu);
    InitGame(&app->game,&app->window);
}

void UpdateApp(App *app){
    while (app->state.running)
    {
        switch (app->state.currentView)
        {
            case LOGO:
            {
                UpdateLogo(&app->logo, &app->state.currentView, &app->state.running);
                RenderLogo(&app->logo, &app->flags.showFPS);
            }break;
            case MENU:
            {
                UpdateMenu(&app->menu, &app->state.currentView, &app->state.running);
                RenderMenu(&app->menu, &app->font, app->window.title, &app->flags);
            }break;
            case GAMEPLAY:
            {
                UpdateGame(&app->game, &app->state.currentView, &app->state.running);
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
    CloseWindow();
}

#endif //APP_H
