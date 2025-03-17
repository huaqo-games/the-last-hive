#ifndef MENU_H
#define MENU_H

#include "../engine/gui.h"

typedef struct {
    Button startButton;
} MenuState;

void initMenu(MenuState *t){
    initButton(&t->startButton, "Start Game", GetScreenWidth() / 10, GetScreenHeight() / 20, GetScreenWidth() / 2, GetScreenHeight() / 2);
}

void updateMenu(MenuState *t, Screen *currentScreen){
    if (isButtonClicked(&t->startButton)) {
        *currentScreen = GAMEPLAY;
    }
}

void renderMenu(MenuState *t){
    BeginDrawing();
        ClearBackground(WHITE);
        renderButton(&t->startButton);
    EndDrawing();
}

#endif // MENU_H
