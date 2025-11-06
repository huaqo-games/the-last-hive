#include "engine.h"
#include "appTypes.h"

const ShaderAsset shaderAssets[SHADER_COUNT] = {
    {"shaders/postfx.fs"}
};

const SoundtrackAsset soundtrackAssets[SOUNDTRACK_COUNT] = {
    {"assets/sea.mp3"}
};


void InitGame(App *app)
{
	
  SetRandomSeed(1234);
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
  CreateCamera(g->player.physics.position, 10.0f);
  g->birds = CreateBirds();
  g->islands = CreateIslands();
  g->floor = CreateFloor();

  Texture2D mouseTexture = LoadTexture("assets/mouse.png");
  g->mouse = CreateMouse(0.10f, 5.0f, 10.0f, &mouseTexture);
}

void StartGame(App *app)
{
	if(!app->state.gameStarted){
		app->state.gameStarted = true;
	}
}


void UpdateGame(App *app)
{
	GameState *g = &app->game;
	
    SetTargetFPS(0);

	StartGame(app);

	OnEscapeChangeView(app, MENU);
	OnWindowClosedStoppApp(app);

	for (int i = 0; i < SHADER_COUNT; i++)
    {
        UpdatePostFX(&g->postFX[i]);
    }
    for (int i = 0; i < SOUNDTRACK_COUNT; i++)
    {
        UpdateSoundtrack(&g->soundtracks[i], app->flags.soundtrackOn);
    }

    UpdateMouse(&g->mouse);
    UpdateCamera2D(&g->player.physics.position, &g->mouse);
    UpdateFloor(&g->floor);
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
	Camera2D *camera = GetCamera();
    BeginMode2D(*camera);
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

