#ifndef GAME_H
#define GAME_H
#include "../engine/object.h"
#include "../engine/camera.h"
#include "../engine/input.h"
#include "../engine/postfx.h"
#include "../engine/soundtrack.h"
#include "../engine/asset.h"
#include "../engine/applicationstate.h"
#include "gameassets.h"
#include "floor.h"
#include "player.h"
#include "bee.h"
#include "hive.h"
#include "flowers.h"

typedef struct {
    Assets assets;
    Texture2D textures[TEX_COUNT];
    PostProcessing postFX[SHADER_COUNT];
    Soundtrack soundtracks[SOUNDTRACK_COUNT];
    RenderTexture2D target;
    Floor floor;
    Object hive;
    ObjectArray flowers;
    Player player;
    Bee bee1;
    Camera2D camera;
    Mouse mouse;
    Image image;
} GameState;

void InitGame(GameState* g, Display *display){ 

    g->assets = (Assets){
        .textureAssets = texAssets,
        .shaderAssets = shaderAssets,
        .soundtrackAssets = soundtrackAssets
    };

    for (int i = 0; i < TEX_COUNT; i++){
        g->textures[i] = LoadTexture(g->assets.textureAssets[i].path);
    }

    for (int i = 0; i < SHADER_COUNT; i++){
        g->postFX[i] = CreatePostFX(g->assets.shaderAssets[i].path);
    }

    for (int i = 0; i < SOUNDTRACK_COUNT; i++){
        g->soundtracks[i] = LoadSoundtrack(g->assets.soundtrackAssets[i].path);
    }

    // Target texture
    g->target = LoadRenderTexture(display->width, display->height);
 
    // Static Entities
    g->flowers = CreateFlowers(g->textures[FLOWER], g->assets.textureAssets[FLOWER].frameWidth, g->assets.textureAssets[FLOWER].rotation, 50.0f);    
    g->floor = CreateFloor(g->textures[GRASS], g->assets.textureAssets[GRASS].frameWidth);
    g->hive = CreateHive(g->textures[HIVE], g->assets.textureAssets[HIVE].frameWidth);
    
    // Animated Entities
    g->player = CreatePlayer(IDLE_DOWN, HOE, g->textures[PLAYER], g->assets.textureAssets[PLAYER].frameWidth, 4, 2, g->hive.position, g->assets.textureAssets[PLAYER].rotation, 50.0f);
    g->bee1 = CreateBee(FLYING, g->textures[BEE], g->assets.textureAssets[BEE].frameWidth, 4, 10, g->hive.position, 10.0f, &g->flowers, &g->hive);
    
    // I/O
    g->camera = CreateCamera(display->width, display->height, g->player.physics.position, 10.0f);
    g->mouse = CreateMouse(0.10f, 5.0f, 10.0f);

}

void UpdateGame(GameState* g, State *state){
    if (GetFPS() <= 60){ SetTargetFPS(0); }
    if (IsKeyPressed(KEY_ESCAPE)){ state->currentScreen = MENU; }
    if (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) { state->running = false; }
    for (int i = 0; i < SHADER_COUNT; i++){ UpdatePostFX(&g->postFX[i]); }
    for (int i = 0; i < SOUNDTRACK_COUNT; i++){ UpdateSoundtrack(&g->soundtracks[i]); }

    UpdateMouse(&g->mouse, &g->camera);
    UpdateCamera2D(&g->camera, &g->player.physics.position, &g->mouse);
    UpdateFloor(&g->floor, &g->camera);
    UpdatePlayer(&g->player);
    UpdateBee(&g->bee1, &g->flowers, &g->hive);

}

void RenderComponents(GameState* g){
    RenderFloor(&g->floor);
    RenderSprite(&g->hive.sprite);
    RenderObjectArray(&g->flowers);
    RenderSprite(&g->player.sprite);
    RenderSprite(&g->bee1.sprite);
}

void RenderGame(GameState* g){
    BeginTextureMode(g->target);
        ClearBackground(BLACK);
        BeginMode2D(g->camera);
            RenderComponents(g);
        EndMode2D();
    EndTextureMode();
    BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < SHADER_COUNT; i++){
            RenderPostFX(&g->postFX[i], &g->target);    
        }
        DrawFPS(10, 10);
    EndDrawing();
}

void CleanupGame(GameState* g){
    for (int i = 0; i < SHADER_COUNT; i++){ UnloadPostFX(&g->postFX[i]); }
    for (int i = 0; i < TEX_COUNT; i++){ if (g->textures[i].id > 0) { UnloadTexture(g->textures[i]); } }
    for (int i = 0; i < SOUNDTRACK_COUNT; i++){ UnloadMusicStream(g->soundtracks[i].music); }
    UnloadRenderTexture(g->target);
    free(g->flowers.data);
}

#endif // GAME_H
