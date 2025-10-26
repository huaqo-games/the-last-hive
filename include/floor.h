#ifndef Floor_H
#define Floor_H

#include <raylib.h>
#include <sprite.h>

typedef struct
{
    Sprite sprite;
    Rectangle bounds;
    Shader shader;
    float time;
} Floor;

// ----------------------------------------------------
// Create floor (loads shader and sets defaults)
// ----------------------------------------------------
Floor CreateFloor()
{


	Texture2D base = LoadTexture("assets/ocean_base.png");
	Texture2D caustic = LoadTexture("assets/CausticTexture.png");
	Texture2D causticHighlight = LoadTexture("assets/CausticTextureHighlights.png");
	Texture2D noise = LoadTexture("assets/noiseTexture.png");
	Texture2D cloud = LoadTexture("assets/cloudnoise_1.png");
	Texture2D voronoise = LoadTexture("assets/voronoise_3.png");

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

	float worldTileSize = 128.0f; // one tile covers 128x128 world units
	float textureSize = 32.0f;    // texture is 32x32 pixels

	floor.sprite.frameSize = (Vector2){worldTileSize, worldTileSize}; 
	floor.sprite.sourceRec = (Rectangle){0, 0, textureSize, textureSize}; 
	floor.sprite.destRec = (Rectangle){0, 0, worldTileSize, worldTileSize}; 
	floor.sprite.origin = (Vector2){0, 0};


    // Optional: load your extra water textures here and bind them
    // Example:


	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "causticTexture"), caustic);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "causticHighlightTexture"), causticHighlight);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "causticNoiseTexture"), noise);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "causticFadeNoiseTexture"), cloud);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "specularNoiseTexture"), voronoise);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "specularMovementLeftNoiseTexture"), voronoise);
	SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "specularMovementRightNoiseTexture"), cloud);


    // Texture2D caustic = LoadTexture("resources/caustic.png");
    // SetShaderValueTexture(floor.shader, GetShaderLocation(floor.shader, "causticTexture"), caustic);

    // Setup aspect ratio and pixelization uniforms once
    float aspect = (float)GetScreenHeight() / (float)GetScreenWidth();
    float pixelization = 2048.0f;
    int aspectLoc = GetShaderLocation(floor.shader, "aspectRatio");
    int pixelLoc = GetShaderLocation(floor.shader, "pixelization");
    SetShaderValue(floor.shader, aspectLoc, &aspect, SHADER_UNIFORM_FLOAT);
    SetShaderValue(floor.shader, pixelLoc, &pixelization, SHADER_UNIFORM_FLOAT);
	
	floor.sprite.texture = base;

    return floor;
}

// ----------------------------------------------------
// Update visible area (same logic as before)
// ----------------------------------------------------
void UpdateFloor(Floor *floor, const Camera2D *camera)
{
    floor->bounds.x = (int)((camera->target.x - (GetScreenWidth() / 2.0f / camera->zoom)) / floor->sprite.frameSize.x) - 1;
    floor->bounds.width = (int)((camera->target.x + (GetScreenWidth() / 2.0f / camera->zoom)) / floor->sprite.frameSize.x) + 1;
    floor->bounds.y = (int)((camera->target.y - (GetScreenHeight() / 2.0f / camera->zoom)) / floor->sprite.frameSize.y) - 1;
    floor->bounds.height = (int)((camera->target.y + (GetScreenHeight() / 2.0f / camera->zoom)) / floor->sprite.frameSize.y) + 1;

    // Update time uniform
    floor->time += GetFrameTime();
    int timeLoc = GetShaderLocation(floor->shader, "time");
    SetShaderValue(floor->shader, timeLoc, &floor->time, SHADER_UNIFORM_FLOAT);
}

// ----------------------------------------------------
// Render floor tiles using the shader
// ----------------------------------------------------
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

// ----------------------------------------------------
// Cleanup
// ----------------------------------------------------
void UnloadFloor(Floor *floor)
{
    UnloadShader(floor->shader);
}

#endif // Floor_H
