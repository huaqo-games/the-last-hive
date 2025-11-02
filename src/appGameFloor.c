#include "appTypes.h"

Floor CreateFloor(void)
{

	Texture2D base = LoadTexture("assets/water_base.png");
	Texture2D caustic = LoadTexture("assets/water_caustics.png");
	Texture2D causticHighlight = LoadTexture("assets/water_caustics_highlights.png");
	Texture2D noise = LoadTexture("assets/water_noise.png");
	Texture2D cloud = LoadTexture("assets/water_cloudnoise.png");
	Texture2D voronoise = LoadTexture("assets/water_voronoise.png");

	float textureWidth = 64.0f;

    Floor floor = {
        .sprite = {
            .texture = base,
            .frameSize = {textureWidth, textureWidth},
            .sourceRec = {0.0f, 0.0f, textureWidth, textureWidth},
            .destRec = {0.0f, 0.0f, textureWidth, textureWidth},
            .origin = {textureWidth / 2, textureWidth / 2},
            .rotation = 0.0f,
            .color = WHITE},
        .bounds = {0},
        .shader = LoadShader("shaders/water.vs", "shaders/water.fs"),
        .time = 0.0f
    };

	float worldTileSize = 128.0f;
	float textureSize = 32.0f;

	floor.sprite.frameSize = (Vector2){worldTileSize, worldTileSize}; 
	floor.sprite.sourceRec = (Rectangle){0, 0, textureSize, textureSize}; 
	floor.sprite.destRec = (Rectangle){0, 0, worldTileSize, worldTileSize}; 
	floor.sprite.origin = (Vector2){0, 0};

	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "causticTexture"), caustic);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "causticHighlightTexture"), causticHighlight);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "causticNoiseTexture"), noise);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "causticFadeNoiseTexture"), cloud);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "specularNoiseTexture"), voronoise);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "specularMovementLeftNoiseTexture"), voronoise);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "specularMovementRightNoiseTexture"), cloud);

    float aspect = (float)GetScreenHeight() / (float)GetScreenWidth();
    float pixelization = 2048.0f;
    int aspectLoc = GetShaderLocation(floor.shader, "aspectRatio");
    int pixelLoc = GetShaderLocation(floor.shader, "pixelization");
    SetShaderValue(floor.shader, aspectLoc, &aspect, SHADER_UNIFORM_FLOAT);
    SetShaderValue(floor.shader, pixelLoc, &pixelization, SHADER_UNIFORM_FLOAT);
	
	floor.sprite.texture = base;

    return floor;
}

void UpdateFloor(Floor *floor, const Camera2D *camera)
{
    floor->bounds.x = (int)((camera->target.x - (GetScreenWidth() / 2.0f / camera->zoom)) / floor->sprite.frameSize.x) - 1;
    floor->bounds.width = (int)((camera->target.x + (GetScreenWidth() / 2.0f / camera->zoom)) / floor->sprite.frameSize.x) + 1;
    floor->bounds.y = (int)((camera->target.y - (GetScreenHeight() / 2.0f / camera->zoom)) / floor->sprite.frameSize.y) - 1;
    floor->bounds.height = (int)((camera->target.y + (GetScreenHeight() / 2.0f / camera->zoom)) / floor->sprite.frameSize.y) + 1;

    floor->time += GetFrameTime();
    int timeLoc = GetShaderLocation(floor->shader, "time");
    SetShaderValue(floor->shader, timeLoc, &floor->time, SHADER_UNIFORM_FLOAT);
}

void RenderFloor(Floor *floor)
{
    BeginShaderMode(floor->shader);

    for (int y = (int)floor->bounds.y; y <= (int)floor->bounds.height; y++)
    {
        for (int x = (int)floor->bounds.x; x <= (int)floor->bounds.width; x++)
        {
            Vector2 floorPosition = {x * floor->sprite.frameSize.x, y * floor->sprite.frameSize.y};
            UpdateSpriteDestRec(&floor->sprite, &floorPosition);
            RenderSprite(&floor->sprite);
        }
    }

    EndShaderMode();
}

void UnloadFloor(Floor *floor)
{
    UnloadShader(floor->shader);
}

