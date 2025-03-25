#ifndef MENU_H
#define MENU_H

#include "../engine/gui.h"
#include "../engine/applicationstate.h"
#include "../engine/asset.h"
#include "../engine/gamegui.h"
#include "menuassets.h"
#include "colors.h"

typedef struct {
    Assets assets;
    Texture2D textures[MENU_TEX_COUNT];
    Sound sounds[MENU_SOUND_COUNT];
    ImageElement board;
    ImageButton playButton;
    ImageButton quitButton;
} MenuState;

void InitMenu(MenuState *m){

    m->assets = (Assets){
        .textureAssets = menuTextureAssets,
        .soundAssets = menuSoundAssets
    };

    for (int i = 0; i < MENU_TEX_COUNT; i++){
        m->textures[i] = LoadTexture(m->assets.textureAssets[i].path);
    }

    for (int i = 0; i < MENU_SOUND_COUNT; i++){
        m->sounds[i] = LoadSound(m->assets.soundAssets[i].path);
    }

    int menuScale = 4;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Vector2 screenCenter = {screenWidth / 2, screenHeight / 2};

    int boardWidth = screenWidth / menuScale * 3.0f;
    float boardScaleFactor = (float)boardWidth / m->assets.textureAssets[BOARD].frameWidth;
    int boardHeight = (int)(m->assets.textureAssets[BOARD].frameHeight * boardScaleFactor);
    
    Vector2 boardSource = {128.0f,0.0f};
    Rectangle boardDestRec = {
        .x = screenCenter.x - (boardWidth / 2),
        .y = screenCenter.y - (boardHeight / 2),
        .width = boardWidth,
        .height = boardHeight
    };

    m->board = CreateImageElement(&m->textures[BOARD], &m->assets.textureAssets[BOARD], &boardSource, &boardDestRec);
    
    int buttonWidth = screenWidth / menuScale;
    float buttonScaleFactor = (float)buttonWidth / m->assets.textureAssets[BIG_BUTTONS].frameWidth;
    int buttonHeight = (int)(m->assets.textureAssets[BIG_BUTTONS].frameHeight * buttonScaleFactor);
    int buttonSpacing = buttonHeight;

    Vector2 playButtonNotPressed = { 0.0f, 96.0f};
    Vector2 quitButtonNotPressed = { 0.0f, 0.0f};
    Vector2 playButtonPressed = { 96.0f, 96.0f};
    Vector2 quitButtonPressed = { 96.0f, 0.0f};

    Rectangle playButtonDestRec = {
        .x = screenCenter.x - (buttonWidth / 2),
        .y = screenCenter.y - (buttonHeight / 2),
        .width = buttonWidth,
        .height = buttonHeight 
    };

    Rectangle quitButtonDestRec = {
        .x = screenCenter.x - (buttonWidth / 2),
        .y = screenCenter.y - (buttonHeight / 2) + buttonSpacing,
        .width = buttonWidth,
        .height = buttonHeight
    };


    m->playButton = CreateImageButton(NOT_CLICKED, &m->textures[BIG_BUTTONS], &m->assets.textureAssets[BIG_BUTTONS], &playButtonNotPressed, &playButtonPressed, &playButtonDestRec);
    m->quitButton = CreateImageButton(NOT_CLICKED, &m->textures[BIG_BUTTONS], &m->assets.textureAssets[BIG_BUTTONS], &quitButtonNotPressed, &quitButtonPressed, &quitButtonDestRec);
}

void UpdateMenu(MenuState *m, State *state){

    if (isImageButtonClicked(&m->playButton, m->sounds[HOVER_SOUND], m->sounds[CLICK_SOUND])){
        state->gameStarted = true;
        state->currentScreen = GAMEPLAY;
    }

    if (isImageButtonClicked(&m->quitButton, m->sounds[HOVER_SOUND], m->sounds[CLICK_SOUND]) || (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))) {
        state->running = false;
    }

}

void RenderMenu(MenuState *m, Font *font, const char* name){
    BeginDrawing();
        ClearBackground(WHITE);
        renderImageElement(&m->board);
        renderImageButton(&m->playButton);
        renderImageButton(&m->quitButton);
        int textWidth = MeasureText(name, font->baseSize);
        DrawTextEx(*font, name, (Vector2){ GetScreenWidth() / 2 - textWidth / 2, textWidth / 4}, (float)font->baseSize, 2, WHITE);
        DrawFPS(10, 10);
    EndDrawing();
}

void CleanupMenu(MenuState *m){
    for (int i = 0; i < MENU_SOUND_COUNT; i++){ UnloadSound(m->sounds[i]); }
    for (int i = 0; i < MENU_TEX_COUNT; i++){ if (m->textures[i].id > 0) { UnloadTexture(m->textures[i]); } }
}

#endif // MENU_H
