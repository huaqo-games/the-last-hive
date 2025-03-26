#ifndef MENU_H
#define MENU_H

#include "../engine/gui.h"
#include "../engine/applicationstate.h"
#include "../engine/asset.h"
#include "../engine/gamegui.h"
#include "menuassets.h"
#include "colors.h"
#include "../engine/input.h"
#include "background.h"
#include "../engine/soundtrack.h"

typedef struct {
    Assets assets;
    Mouse mouse;
    Texture2D textures[MENU_TEX_COUNT];
    Sound sounds[MENU_SOUND_COUNT];
    Soundtrack soundtracks[MENU_SOUNDTRACK_COUNT];
    ImageElement board;
    ImageButton playButton;
    ImageButton quitButton;
    int menuScale;
    Background background;
    Background midground;
    Background foreground;
} MenuState;

void InitMenu(MenuState *m){

    m->assets = (Assets){
        .textureAssets = menuTextureAssets,
        .soundAssets = menuSoundAssets,
        .soundtrackAssets = menuSoundtrackAssets
    };

    for (int i = 0; i < MENU_TEX_COUNT; i++){
        m->textures[i] = LoadTexture(m->assets.textureAssets[i].path);
    }

    for (int i = 0; i < MENU_SOUND_COUNT; i++){
        m->sounds[i] = LoadSound(m->assets.soundAssets[i].path);
    }

    for (int i = 0; i < MENU_SOUNDTRACK_COUNT; i++){
        m->soundtracks[i] = LoadSoundtrack(m->assets.soundtrackAssets[i].path);
    }

    InitBackground(0.1f, &m->background, &m->textures[MENU_CLOUD_BACKGROUND], &m->assets.textureAssets[MENU_CLOUD_BACKGROUND]);
    InitBackground(0.2f, &m->midground, &m->textures[MENU_CLOUD_MIDGROUND], &m->assets.textureAssets[MENU_CLOUD_MIDGROUND]);
    InitBackground(0.3f, &m->foreground, &m->textures[MENU_CLOUD_FOREGROUND], &m->assets.textureAssets[MENU_CLOUD_FOREGROUND]);

    m->mouse = CreateMouse(0.10f, 5.0f, 10.0f, &m->textures[MENU_CURSOR_TEX]);

    m->menuScale = 4;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Vector2 screenCenter = {screenWidth / 2, screenHeight / 2};



    int boardWidth = screenWidth / m->menuScale * 2.5f;
    float boardScaleFactor = (float)boardWidth / m->assets.textureAssets[MENU_BOARD_TEX].frameWidth;
    int boardHeight = (int)(m->assets.textureAssets[MENU_BOARD_TEX].frameHeight * boardScaleFactor);
    
    Vector2 boardSource = {128.0f,0.0f};
    Rectangle boardDestRec = {
        .x = screenCenter.x - (boardWidth / 2),
        .y = screenCenter.y - (boardHeight / 2),
        .width = boardWidth,
        .height = boardHeight
    };

    m->board = CreateImageElement(&m->textures[MENU_BOARD_TEX], &m->assets.textureAssets[MENU_BOARD_TEX], &boardSource, &boardDestRec);
    
    int buttonWidth = screenWidth / m->menuScale;
    float buttonScaleFactor = (float)buttonWidth / m->assets.textureAssets[MENU_BIG_BUTTONS_TEX].frameWidth;
    int buttonHeight = (int)(m->assets.textureAssets[MENU_BIG_BUTTONS_TEX].frameHeight * buttonScaleFactor);
    int buttonSpacing = buttonHeight;

    Vector2 playButtonNotPressed = { 0.0f, 96.0f};
    Vector2 quitButtonNotPressed = { 0.0f, 0.0f};
    Vector2 playButtonHover = { 96.0f, 96.0f};
    Vector2 quitButtonHover = { 96.0f, 0.0f};
    Vector2 playButtonPressed = { 192.0f, 96.0f};
    Vector2 quitButtonPressed = { 192.0f, 0.0f};

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

    m->playButton = CreateImageButton(NOT_CLICKED, &m->textures[MENU_BIG_BUTTONS_TEX], &m->assets.textureAssets[MENU_BIG_BUTTONS_TEX], &playButtonNotPressed, &playButtonPressed, &playButtonHover, &playButtonDestRec);
    m->quitButton = CreateImageButton(NOT_CLICKED, &m->textures[MENU_BIG_BUTTONS_TEX], &m->assets.textureAssets[MENU_BIG_BUTTONS_TEX], &quitButtonNotPressed, &quitButtonPressed, &quitButtonHover, &quitButtonDestRec);
}

void UpdateMenu(MenuState *m, State *state){

    for (int i = 0; i < MENU_SOUNDTRACK_COUNT; i++){ UpdateSoundtrack(&m->soundtracks[i]); }

    UpdateBackground(&m->background);
    UpdateBackground(&m->midground);
    UpdateBackground(&m->foreground);

    UpdateMouseScreen(&m->mouse);

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
        RenderBackground(&m->background);
        RenderBackground(&m->midground);
        RenderBackground(&m->foreground);
        renderImageElement(&m->board);
        renderImageButton(&m->playButton);
        renderImageButton(&m->quitButton);
        int textWidth = MeasureText(name, font->baseSize);
        DrawTextEx(*font, name, (Vector2){ GetScreenWidth() / 2 - textWidth / 2, textWidth / 4}, (float)font->baseSize, 2, WHITE);
        DrawTexturePro(
            m->mouse.cursorTexture, 
            (Rectangle){ 0, 0, m->mouse.cursorTexture.width, m->mouse.cursorTexture.height}, 
            (Rectangle){m->mouse.screenPosition.x, m->mouse.screenPosition.y, m->mouse.cursorTexture.width, m->mouse.cursorTexture.height}, 
            (Vector2){0.0f, 0.0f},
            0.0f,
            WHITE
        );        
        DrawFPS(10, 10);
    EndDrawing();
}

void CleanupMenu(MenuState *m){
    for (int i = 0; i < MENU_SOUND_COUNT; i++){ UnloadSound(m->sounds[i]); }
    for (int i = 0; i < MENU_TEX_COUNT; i++){ if (m->textures[i].id > 0) { UnloadTexture(m->textures[i]); } }
    for (int i = 0; i < MENU_SOUNDTRACK_COUNT; i++){ UnloadMusicStream(m->soundtracks[i].music); }

}

#endif // MENU_H
