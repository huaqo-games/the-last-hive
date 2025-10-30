#ifndef APPGAME_H
#define APPGAME_H


#include "appGameFloor.h"
#include "appGamePlayer.h"
#include "appGameBirds.h"
#include "appGameAssets.h"

typedef struct
{
  	Assets assets;
    PostProcessing postFX[SHADER_COUNT];
    Soundtrack soundtracks[SOUNDTRACK_COUNT];
    RenderTexture2D target;
    Floor floor;
    Player player;
  	Birds birds;
    Camera2D camera;
    Mouse mouse;
    Image image;
} GameState;

void InitGame(GameState *g, Window *window)
{
  g->assets = (Assets){
      .shaderAssets = shaderAssets,
      .soundtrackAssets = soundtrackAssets
  };

  for (int i = 0; i < SHADER_COUNT; i++)
  {
      g->postFX[i] = CreatePostFX(g->assets.shaderAssets[i].path);
  }

  for (int i = 0; i < SOUNDTRACK_COUNT; i++)
  {
      g->soundtracks[i] = LoadSoundtrack(g->assets.soundtrackAssets[i].path);
  }

  g->target = LoadRenderTexture(window->width, window->height);
  g->player = CreatePlayer();
  g->birds = CreateBirds();
  g->floor = CreateFloor();
  g->camera = CreateCamera(g->player.physics.position, 10.0f);

  Texture2D mouseTexture = LoadTexture("assets/mouse.png");
  g->mouse = CreateMouse(0.10f, 5.0f, 10.0f, &mouseTexture);
}

void UpdateGame(GameState *g, State *state, Flags *flags)
{
	if(!state->gameStarted){
		state->gameStarted = true;
	}

    if (GetFPS() <= 60)
    {
        SetTargetFPS(0);
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        state->currentView = MENU;
    }

    if (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        state->running = false;
    }

	for (int i = 0; i < SHADER_COUNT; i++)
    {
        UpdatePostFX(&g->postFX[i]);
    }
    for (int i = 0; i < SOUNDTRACK_COUNT; i++)
    {
        UpdateSoundtrack(&g->soundtracks[i], flags->soundtrackOn);
    }

    UpdateMouse(&g->mouse, &g->camera);
    UpdateCamera2D(&g->camera, &g->player.physics.position, &g->mouse);
    UpdateFloor(&g->floor, &g->camera);
    UpdatePlayer(&g->player);
    UpdateBirds(&g->birds);
}

void RenderComponents(GameState *g)
{
    RenderFloor(&g->floor);
    RenderPlayer(&g->player);
    RenderBirds(&g->birds);
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
    for (int i = 0; i < SOUNDTRACK_COUNT; i++)
    {
        UnloadMusicStream(g->soundtracks[i].music);
    }
    UnloadRenderTexture(g->target);
}

#endif // APPGAME_H
