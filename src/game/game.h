#ifndef GAME_H
#define GAME_H
#include "../engine/object.h"
#include "../engine/camera.h"
#include "../engine/input.h"
#include "../engine/shader.h"
#include "../engine/musicmanager.h"
#include "floor.h"
#include "player.h"
#include "bee.h"
#include "hive.h"
#include "flowers.h"

typedef struct {
    VignetteShader vignetteShader;
    MyMusic ambient;
    RenderTexture2D target;
    Texture2D flowerTexture, beeTexture, floorTexture, hiveTexture;
    Floor floor;
    Object hive;
    ObjectArray flowers;
    Player player;
    Bee bee1;
    Camera2D camera;
    Mouse mouse;
} GameState;

void initGame(GameState* g){
    InitAudioDevice(); 
    
    g->vignetteShader = CreateShader("shaders/vignette.fs", 0.3f);
    
    g->ambient = CreateMusic("assets/beez.mp3");
    
    g->target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    g->flowerTexture = LoadTexture("assets/flower.png");
    g->beeTexture = LoadTexture("assets/character_bee.png");
    g->floorTexture = LoadTexture("assets/grass.png");
    g->hiveTexture = LoadTexture("assets/hive.png");

    g->floor = CreateFloor(g->floorTexture, 16.0f);
    g->flowers = CreateFlowers(g->flowerTexture, 16.0f, 45.0f, 50.0f);    
    g->hive = CreateHive(g->hiveTexture, 32.0f);
    g->player = CreatePlayer(g->beeTexture, 16.0f, 4, 10, g->hive.position, 50.0f);
    g->bee1 = CreateBee(g->beeTexture, 16.0f, 4, 10, g->hive.position, 10.0f, &g->flowers, &g->hive);

    g->camera = CreateCamera(GetScreenWidth(), GetScreenHeight(), g->player.physics.position, 10.0f);
    g->mouse = CreateMouse(0.10f, 5.0f, 10.0f);
}

void updateGame(GameState* g){
    UpdateShader(&g->vignetteShader);
    UpdateMusic(&g->ambient);
    UpdateMouse(&g->mouse, &g->camera);
    UpdateCamera2D(&g->camera, &g->player.physics.position, &g->mouse);
    UpdateFloor(&g->floor, &g->camera);
    UpdatePlayer(&g->player);
    UpdateBee(&g->bee1, &g->flowers, g->hive);
}

void renderGame(GameState* g){
    BeginTextureMode(g->target);
        ClearBackground(BLACK);
        BeginMode2D(g->camera);
            RenderFloor(&g->floor);
            RenderSprite(&g->hive.sprite);
            RenderObjectArray(&g->flowers);
            RenderSprite(&g->bee1.sprite);
            RenderSprite(&g->player.sprite);
        EndMode2D();
    EndTextureMode();
    BeginDrawing();
        ClearBackground(BLACK);
            BeginShaderMode(g->vignetteShader.shader);
                DrawTextureRec(g->target.texture, (Rectangle){ 0, 0, g->target.texture.width, -g->target.texture.height }, (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
        DrawFPS(10, 10);
    EndDrawing();
}

void cleanupGame(GameState* g){
    UnloadVignetteShader(&g->vignetteShader);
    UnloadRenderTexture(g->target);
    UnloadTexture(g->floorTexture);
    UnloadTexture(g->hiveTexture);
    UnloadTexture(g->flowerTexture);
    UnloadTexture(g->beeTexture);
    UnloadMusicStream(g->ambient.music);
    free(g->flowers.data);
    CloseAudioDevice();
}

#endif // GAME_H
