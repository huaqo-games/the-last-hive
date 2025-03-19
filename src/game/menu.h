#ifndef MENU_H
#define MENU_H

#include "../engine/gui.h"
#include "../engine/applicationstate.h"

typedef struct {
    Button startButton;
    Button quitButton;
} MenuState;

void InitMenu(MenuState *t){
    initButton(&t->startButton, "Start Game", GetScreenWidth() / 10, GetScreenHeight() / 20, GetScreenWidth() / 2, GetScreenHeight() / 2);
    initButton(&t->quitButton, "Quit Game", GetScreenWidth() / 10, GetScreenHeight() / 20, GetScreenWidth() / 2, GetScreenHeight() / 2 + (GetScreenHeight() / 20 * 2));
}

void UpdateMenu(MenuState *t, State *state){
    if (isButtonClicked(&t->startButton)) {
        state->gameStarted = true;
        t->startButton.text = "Continue";
        state->currentScreen = GAMEPLAY;
    }
    if (isButtonClicked(&t->quitButton) || (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))) {
        state->running = false;
    }

    if (state->gameStarted){
        if (IsKeyPressed(KEY_ESCAPE)){
            state->currentScreen = GAMEPLAY;
        }
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
