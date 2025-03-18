#ifndef GAME_H
#define GAME_H
#include "../engine/object.h"
#include "../engine/camera.h"
#include "../engine/input.h"
#include "../engine/postfx.h"
#include "../engine/musicmanager.h"
#include "../engine/asset.h"
#include "floor.h"
#include "player.h"
#include "bee.h"
#include "hive.h"
#include "flowers.h"

typedef enum {
    FLOWER,
    BEE,
    GRASS,
    HIVE,
    TEX_COUNT
} TextureID;

typedef struct {
    PostProcessing postFX;
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
    TextureAsset textureAssets[TEX_COUNT];
    Texture2D textures[TEX_COUNT];
} GameState;

void InitGame(GameState* g){

    InitAudioDevice(); 
    
    g->postFX = CreatePostFX("shaders/postfx.fs", 0.3f);
    
    g->ambient = CreateMusic("assets/beez.mp3");

    g->textureAssets[FLOWER] = (TextureAsset){"assets/flower.png", 16.0f, 16.0f, 45.0f};
    g->textureAssets[BEE] = (TextureAsset){"assets/character_bee.png", 16.0f, 16.0f, 0.0f};
    g->textureAssets[GRASS] = (TextureAsset){"assets/grass.png", 16.0f, 16.0f, 0.0f};
    g->textureAssets[HIVE] = (TextureAsset){"assets/hive.png", 32.0f, 32.0f, 0.0f};
    
    g->textures[FLOWER] = LoadTexture(g->textureAssets[FLOWER].path);
    g->textures[BEE] = LoadTexture(g->textureAssets[BEE].path);
    g->textures[GRASS] = LoadTexture(g->textureAssets[GRASS].path);
    g->textures[HIVE] = LoadTexture(g->textureAssets[HIVE].path);
    
    g->flowers = CreateFlowers(g->textures[FLOWER], g->textureAssets[FLOWER].frameWidth, g->textureAssets[FLOWER].rotation, 50.0f);    
    g->player = CreatePlayer(g->textures[BEE], g->textureAssets[BEE].frameWidth, 4, 10, g->hive.position, 50.0f);
    g->floor = CreateFloor(g->textures[GRASS], g->textureAssets[GRASS].frameWidth);
    g->hive = CreateHive(g->textures[HIVE], g->textureAssets[HIVE].frameWidth);
    g->bee1 = CreateBee(g->textures[BEE], g->textureAssets[BEE].frameWidth, 4, 10, g->hive.position, 10.0f, &g->flowers, &g->hive);

    g->camera = CreateCamera(GetScreenWidth(), GetScreenHeight(), g->player.physics.position, 10.0f);
    g->mouse = CreateMouse(0.10f, 5.0f, 10.0f);

    g->target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
}

void UpdateGame(GameState* g){
    UpdatePostFX(&g->postFX);
    UpdateMusic(&g->ambient);
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
    RenderSprite(&g->bee1.sprite);
    RenderSprite(&g->player.sprite);
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
        RenderPostFX(&g->postFX, &g->target);    
        DrawFPS(10, 10);
    EndDrawing();
}

void CleanupGame(GameState* g){
    UnloadPostFX(&g->postFX);
    UnloadRenderTexture(g->target);
    for (int i = 0; i < TEX_COUNT; i++){
        if (g->textures[i].id > 0) { UnloadTexture(g->textures[i]); }
    }
    UnloadMusicStream(g->ambient.music);
    free(g->flowers.data);
    CloseAudioDevice();
}

#endif // GAME_H
