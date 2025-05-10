#ifndef GAME_H
#define GAME_H

#include <object.h>
#include <camera.h>
#include <input.h>
#include <postfx.h>
#include <soundtrack.h>
#include <asset.h>
#include <array.h>
#include <stdlib.h>

#include "gameassets.h"
#include "floor.h"
#include "player.h"
#include "bee.h"
#include "hive.h"
#include "flowers.h"

typedef struct
{
    Assets assets;
    Texture2D textures[TEX_COUNT];
    PostProcessing postFX[SHADER_COUNT];
    Soundtrack soundtracks[SOUNDTRACK_COUNT];
    RenderTexture2D target;
    Floor floor;
    Object hive;
    Array* flowers;
    Player player;
    Bee bee1;
    Camera2D camera;
    Mouse mouse;
    Image image;
} GameState;

void InitGame(GameState *g, Window *window)
{

    g->assets = (Assets){
        .textureAssets = texAssets,
        .shaderAssets = shaderAssets,
        .soundtrackAssets = soundtrackAssets};

    for (int i = 0; i < TEX_COUNT; i++)
    {
        g->textures[i] = LoadTexture(g->assets.textureAssets[i].path);
    }

    for (int i = 0; i < SHADER_COUNT; i++)
    {
        g->postFX[i] = CreatePostFX(g->assets.shaderAssets[i].path);
    }

    g->soundtracks[BACKGROUND_MUSIC] = LoadSoundtrack(g->assets.soundtrackAssets[BACKGROUND_MUSIC].path);
    g->soundtracks[BACKGROUND_MUSIC].playing = true;

    // Target texture
    g->target = LoadRenderTexture(window->width, window->height);

    // Static Entities
    g->flowers = CreateFlowers(g->textures[FLOWER], g->assets.textureAssets[FLOWER].frameWidth, g->assets.textureAssets[FLOWER].rotation, 50.0f);
    g->floor = CreateFloor(g->textures[GRASS], g->assets.textureAssets[GRASS].frameWidth);
    g->hive = CreateHive(g->textures[HIVE], g->assets.textureAssets[HIVE].frameWidth);

    // Animated Entities
    g->player = CreatePlayer(IDLE_DOWN, HOE, g->textures[PLAYER], g->assets.textureAssets[PLAYER].frameWidth, 4, 2, g->hive.position, g->assets.textureAssets[PLAYER].rotation, 50.0f);

    // I/O
    g->camera = CreateCamera(window->width, window->height, g->player.physics.position, 10.0f);
    g->mouse = CreateMouse(0.10f, 5.0f, 10.0f, &g->textures[CURSOR]);
}

void UpdateGame(GameState *g, View *currentView, bool *running)
{
    if (GetFPS() <= 60)
    {
        SetTargetFPS(0);
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        *currentView = MENU;
    }
    if (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        *running = false;
    }
    for (int i = 0; i < SHADER_COUNT; i++)
    {
        UpdatePostFX(&g->postFX[i]);
    }

    UpdateSoundtrack(&g->soundtracks[BACKGROUND_MUSIC]);
    UpdateMouse(&g->mouse, &g->camera);
    UpdateCamera2D(&g->camera, &g->player.physics.position, &g->mouse);
    UpdateFloor(&g->floor, &g->camera);
    UpdatePlayer(&g->player, g->flowers);
    UpdateArray(g->flowers, UpdateFlower);
    // UpdateBee(&g->bee1, g->flowers);
}

void RenderComponents(GameState *g)
{
    RenderFloor(&g->floor);
    RenderSprite(&g->hive.sprite);
    RenderArray(g->flowers, RenderFlower);
    RenderSprite(&g->player.sprite);
    RenderSprite(&g->bee1.sprite);
}

void RenderGame(GameState *g, const State *appState, Flags *flags)
{
    BeginTextureMode(g->target);
    ClearBackground(BLACK);
    BeginMode2D(g->camera);
    RenderComponents(g);
    EndMode2D();
    DrawTextureRec(g->mouse.cursorTexture, (Rectangle){0, 0, g->mouse.cursorTexture.width, g->mouse.cursorTexture.height}, (Vector2){g->mouse.screenPosition.x, g->mouse.screenPosition.y}, WHITE);
    EndTextureMode();
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < SHADER_COUNT; i++)
    {
        RenderPostFX(&g->postFX[i], &g->target);
    }
    DrawText(TextFormat("Flower Seeds: %d", g->player.inventar.flowerSeedCount), 10, 10, 50, WHITE);

    if (flags->showFPS)
    {
        DrawFPS(10, 10);
    }

    EndDrawing();
}

void CleanupGame(GameState *g)
{
    for (int i = 0; i < SHADER_COUNT; i++)
    {
        UnloadPostFX(&g->postFX[i]);
    }
    for (int i = 0; i < TEX_COUNT; i++)
    {
        if (g->textures[i].id > 0)
        {
            UnloadTexture(g->textures[i]);
        }
    }
    for (int i = 0; i < SOUNDTRACK_COUNT; i++)
    {
        UnloadMusicStream(g->soundtracks[i].music);
    }
    UnloadRenderTexture(g->target);
    FreeArray(&g->flowers);
}

#endif // GAME_H
