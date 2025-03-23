#ifndef MENU_H
#define MENU_H

#include "../engine/gui.h"
#include "../engine/applicationstate.h"
#include "../engine/asset.h"
#include "../engine/gamegui.h"
#include "menuassets.h"

typedef struct {
    Assets assets;
    Texture2D textures[MENU_TEX_COUNT];
    Button startButton;
    Button quitButton;
    ImageButton newStartButton;
    ImageButton newQuitButton;
} MenuState;

void InitMenu(MenuState *m){
    m->assets = (Assets){
        .textureAssets = menuTextureAssets
    };
    for (int i = 0; i < MENU_TEX_COUNT; i++){
        m->textures[i] = LoadTexture(m->assets.textureAssets[i].path);
    }

    Rectangle startButtonBounds = {
        GetScreenWidth() / 2 - (GetScreenWidth() / 10) / 2,
        GetScreenHeight() / 2 - (GetScreenHeight() / 20) / 2,
        GetScreenWidth() / 10,
        GetScreenHeight() / 20
    };

    Rectangle quitButtonBounds = {
        GetScreenWidth() / 2 - (GetScreenWidth() / 10) / 2,
        GetScreenHeight() / 2 + (GetScreenHeight() / 10) / 2,
        GetScreenWidth() / 10,
        GetScreenHeight() / 20
    };

    Rectangle playTexRecs[2] = {
        { 0.0f, 96.0f, m->assets.textureAssets[BIG_BUTTONS].frameWidth, m->assets.textureAssets[BIG_BUTTONS].frameHeight },
        { m->assets.textureAssets[BIG_BUTTONS].frameWidth, 96.0f, m->assets.textureAssets[BIG_BUTTONS].frameWidth, m->assets.textureAssets[BIG_BUTTONS].frameHeight }
    };

    Rectangle emptyTexRecs[2] = {
        { 0.0f, 0.0f, m->assets.textureAssets[BIG_BUTTONS].frameWidth, m->assets.textureAssets[BIG_BUTTONS].frameHeight },
        { m->assets.textureAssets[BIG_BUTTONS].frameWidth, 0.0f, m->assets.textureAssets[BIG_BUTTONS].frameWidth, m->assets.textureAssets[BIG_BUTTONS].frameHeight }
    };

    initImageButton(&m->newStartButton, playTexRecs, startButtonBounds, m->textures[BIG_BUTTONS]);
    initImageButton(&m->newQuitButton, emptyTexRecs, quitButtonBounds, m->textures[BIG_BUTTONS]);
    // initButton(&m->startButton, "Start Game", GetScreenWidth() / 10, GetScreenHeight() / 20, GetScreenWidth() / 2, GetScreenHeight() / 2);
    // initButton(&m->quitButton, "Quit Game", GetScreenWidth() / 10, GetScreenHeight() / 20, GetScreenWidth() / 2,
    //         GetScreenHeight() / 2 + (GetScreenHeight() / 20 * 2));
}

void UpdateMenu(MenuState *m, State *state){

    if (isImageButtonClicked(&m->newStartButton)){
        state->gameStarted = true;
        m->startButton.text = "Continue";
        state->currentScreen = GAMEPLAY;
    }

    if (isImageButtonClicked(&m->newQuitButton) || (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))) {
        state->running = false;
    }


    // if (isButtonClicked(&m->startButton)) {
    //     state->gameStarted = true;
    //     m->startButton.text = "Continue";
    //     state->currentScreen = GAMEPLAY;
    // }
    // if (isButtonClicked(&m->quitButton) || (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))) {
    //     state->running = false;
    // }

    // if (state->gameStarted){
    //     if (IsKeyPressed(KEY_ESCAPE)){
    //         state->currentScreen = GAMEPLAY;
    //     }
    // }

}

void RenderMenu(MenuState *m){
    BeginDrawing();
        ClearBackground(WHITE);
        // renderButton(&m->startButton);
        // renderButton(&m->quitButton);
        renderImageButton(&m->newStartButton);
        renderImageButton(&m->newQuitButton);
        DrawFPS(10, 10);
    EndDrawing();
}

void CleanupMenu(MenuState *m){
    for (int i = 0; i < MENU_TEX_COUNT; i++){ if (m->textures[i].id > 0) { UnloadTexture(m->textures[i]); } }
}

#endif // MENU_H
