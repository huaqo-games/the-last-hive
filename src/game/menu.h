#ifndef MENU_H
#define MENU_H

#include "../engine/gui.h"

typedef struct {
    Button startButton;
    Button quitButton;
} MenuState;

void InitMenu(MenuState *t){
    initButton(&t->startButton, "Start Game", GetScreenWidth() / 10, GetScreenHeight() / 20, GetScreenWidth() / 2, GetScreenHeight() / 2);
    initButton(&t->quitButton, "Quit Game", GetScreenWidth() / 10, GetScreenHeight() / 20, GetScreenWidth() / 2, GetScreenHeight() / 2 + GetScreenHeight() / 20);
}

void UpdateMenu(MenuState *t, Screen *currentScreen, bool *running, bool *gameStarted){
    if (isButtonClicked(&t->startButton)) {
        *gameStarted = true;
        t->startButton.text = "Continue";
        *currentScreen = GAMEPLAY;
    }
    if (isButtonClicked(&t->quitButton)) {
        *running = false;
    }
}

void RenderMenu(MenuState *t){
    BeginDrawing();
        ClearBackground(WHITE);
        renderButton(&t->startButton);
        renderButton(&t->quitButton);
    EndDrawing();
}

#endif // MENU_H
