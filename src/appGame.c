#include "appTypes.h"

const ShaderAsset shaderAssets[SHADER_COUNT] = {
    {"shaders/postfx.fs"}};



const SoundtrackAsset soundtrackAssets[SOUNDTRACK_COUNT] = {
    {"assets/sea.mp3"}};


void InitGame(App *app)
{
   GameState *g = &app->game;
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

  g->target = LoadRenderTexture(app->window.width, app->window.height);
  g->player = CreatePlayer();
  g->birds = CreateBirds();
  g->islands = CreateIslands();
  g->floor = CreateFloor();
  g->camera = CreateCamera(g->player.physics.position, 10.0f);

  Texture2D mouseTexture = LoadTexture("assets/mouse.png");
  g->mouse = CreateMouse(0.10f, 5.0f, 10.0f, &mouseTexture);
}

void UpdateGame(App *app)
{
	GameState *g = &app->game;
	if(!app->state.gameStarted){
		app->state.gameStarted = true;
	}

    if (GetFPS() <= 60)
    {
        SetTargetFPS(0);
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        app->state.currentView = MENU;
    }

    if (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        app->state.running = false;
    }

	for (int i = 0; i < SHADER_COUNT; i++)
    {
        UpdatePostFX(&g->postFX[i]);
    }
    for (int i = 0; i < SOUNDTRACK_COUNT; i++)
    {
        UpdateSoundtrack(&g->soundtracks[i], app->flags.soundtrackOn);
    }

    UpdateMouse(&g->mouse, &g->camera);
    UpdateCamera2D(&g->camera, &g->player.physics.position, &g->mouse);
    UpdateFloor(&g->floor, &g->camera);
    UpdatePlayer(&g->player);
    UpdateBirds(&g->birds);
	UpdateIslands(&g->islands);
}

void RenderComponents(App *app)
{
	GameState *g = &app->game;
    RenderFloor(&g->floor);
    RenderPlayer(&g->player);
    RenderBirds(&g->birds);
	RenderIslands(&g->islands);
}

void RenderGame(App *app)
{
	GameState *g = &app->game;
	
    BeginTextureMode(g->target);
    ClearBackground(BLACK);
    BeginMode2D(g->camera);
    RenderComponents(app);
    EndMode2D();
    DrawTextureRec
	(
		g->mouse.cursorTexture, 
		(Rectangle){0, 0, g->mouse.cursorTexture.width, g->mouse.cursorTexture.height}, 
		(Vector2){g->mouse.screenPosition.x, g->mouse.screenPosition.y}, 
		WHITE
	);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < SHADER_COUNT; i++)
    {
        RenderPostFX(&g->postFX[i], &g->target);
    }

    if (app->flags.showFPS)
    {
        DrawFPS(10, 10);
    }

    EndDrawing();
}

void CleanupGame(App *app)
{
	GameState *g = &app->game;
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

