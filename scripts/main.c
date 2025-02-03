#include <raylib.h> 
// WHITE, Color,
// KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, IsKeyDown(), 
// InitWindow(), SetTargetFPS(), WindowShouldClose(), GetFrameTime(), CloseWindow()
// Music, InitAudioDevice(), LoadMusicStream(), PlayMusicStream(), UpdateMusicStream(), UnloadMusicStream(), CloseAudioDevice(),
// Texture2D, Rectangle, Vector2, LoadTexture(), DrawTexturePro(), UnloadTexture(), 
// BeginDrawing(), EndDrawing(), ClearBackground(),
// Camera2D, BeginMode2D(), EndMode2D()
#include <raymath.h> // Vector2Length(), Vector2Normalize(), Vector2Add(), Vector2Scale(), Lerp()
#include <stdlib.h> // rand(), srand(), malloc()
#include <time.h> // time()
#include <string.h> // memcpy()

#include "sprite.h"
#include "animsprite.h"
#include "tilesprite.h"
#include "vector.h"
#include "object.h"
// Structs

typedef struct {
    AnimSprite animSprite;
    Vector2 position;
    Vector2 direction;
    float velocity;
} Player;

typedef struct {
    AnimSprite animSprite;
    Vector2 position;
    Vector2 direction;
    float velocity;
    Object targetFlower;
    Object hive;
} Bee;

// Pure functions


void Move(Vector2 *position, Vector2 *direction, float *velocity, float *rotation) {
    if(Vector2Length(*direction) <= 0.0f){
        return;
    }
    float targetRotation = (float)atan2(direction->y, direction->x) * (180.0f / PI) + 90.0f;
    *rotation = Lerp(*rotation, targetRotation, 0.1f); 
    *position = Vector2Add(*position, Vector2Scale(*direction, *velocity * GetFrameTime()));
}

// Mutator Functions

void GetDirectionFromInput(Vector2 *direction){
    *direction = (Vector2){0.0f, 0.0f};
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){ direction->x += 1.0f; }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){ direction->x -= 1.0f; }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){ direction->y += 1.0f; }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){ direction->y -= 1.0f; }
    if (Vector2Length(*direction) > 0.0f) { *direction = Vector2Normalize(*direction); }
}

void UpdateCamera2DTarget(Camera2D *camera, Vector2 *position, const float smoothness){
    camera->target = Vector2Lerp(camera->target, *position, smoothness * GetFrameTime());
}

// Main

int main(void)
{
    // Load
    // SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "The Last Hive"); 
    InitAudioDevice(); 
    Music music = LoadMusicStream("assets/beez.mp3"); 
    PlayMusicStream(music);
    TileSprite floor = {
        .sprite = {
            .texture = LoadTexture("assets/grass.png"),
            .frameSize = {16.0f,16.0f},
            .sourceRec = { 0.0f, 0.0f, 16.0f, 16.0f},
            .destRec = {0.0f, 0.0f, 16.0f, 16.0f},
            .origin = {8.0f, 8.0f},
            .rotation = 0.0f,
            .color = WHITE
        },
        .bounds = {0.0f,0.0f,0.0f,0.0f}
    };
    Object hive = {
        .sprite = {
            .texture = LoadTexture("assets/hive.png"),
            .frameSize = {32.0f,32.0f},
            .sourceRec = {0.0f, 0.0f, 32.0f, 32.0f},
            .destRec = {0.0f, 0.0f, 32.0f, 32.0f},
            .origin = {16.0f, 16.0f},
            .rotation = 0.0f,
            .color = WHITE 
        },
        .position = (Vector2){0.0f,0.0f}
    };
    Texture2D flower = LoadTexture("assets/flower.png");
    ObjectArray flowers = CreateObjectArray(&(Object){
        .sprite = {
            .texture = flower,
            .frameSize = {16.0f, 16.0f},
            .sourceRec = {0.0f, 0.0f, 16.0f, 16.0f},
            .destRec = {0.0f, 0.0f, 16.0f, 16.0f},
            .origin = {8.0f, 8.0f},
            .rotation = 45.0f,
            .color = WHITE
        },
        .position = {0.0f, 0.0f}
    }, 300);
    if (!flowers.data) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    Rectangle flowerField = {-50.0f, -50.0f, 100.0f, 100.0f};
    SetRandomPositionForObjectArray(&flowers, flowerField);
    Player player = {
        .animSprite = {
            .sprite = {
                .texture = LoadTexture("assets/character_bee.png"),
                .frameSize = {16.0f, 16.0f},
                .sourceRec = {0.0f, 0.0f, 16.0f, 16.0f},
                .destRec = {0.0f, 0.0f, 16.0f, 16.0f},
                .origin = {8.0f, 8.0f},
                .rotation = 0.0f,
                .color = WHITE
            },
            .currentFrame = 0,
            .maxFrame = 4,
            .framesCounter = 0,
            .framesSpeed = 10,
            .isVertical = true,
            .animTimer = 0.0f
        },
        .position = hive.position,
        .direction = (Vector2){0.0f,0.0f},
        .velocity = 50.0f
    };
    Bee bee1 = {
        .animSprite = {
            .sprite = {
                .texture = LoadTexture("assets/character_bee.png"),
                .frameSize = {16.0f, 16.0f},
                .sourceRec = {0.0f, 0.0f, 16.0f, 16.0f},
                .destRec = {0.0f, 0.0f, 16.0f, 16.0f},
                .origin = {8.0f, 8.0f},
                .rotation = 0.0f,
                .color = WHITE
            },
            .currentFrame = 0,
            .maxFrame = 4,
            .framesCounter = 0,
            .framesSpeed = 10,
            .isVertical = true,
            .animTimer = 0.0f
        },
        .position = hive.position,
        .direction = (Vector2){0.0f,0.0f},
        .velocity = 5.0f,
        .targetFlower = *GetRandomObject(&flowers),
        .hive = hive
    };
    Camera2D camera = {
        .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target = player.position,
        .rotation = 0.0f,
        .zoom = 10.0f
    };

    // Update & Render
    while (!WindowShouldClose())
    {
        // Update
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            AddObjectToArray(&flowers, flowers.prototype, mouseWorldPos);
        }

        UpdateMusicStream(music);
        UpdateTileSpriteBounds(&floor, &camera);
        
        GetDirectionFromInput(&player.direction);
        Move(&player.position, &player.direction, &player.velocity, &player.animSprite.sprite.rotation);
        UpdateSpriteDestRec(&player.animSprite.sprite, &player.position);
        UpdateAnimSprite(&player.animSprite);

        const float tolerance = 1.0f; // Adjust as needed

        if (fabs(bee1.position.x - bee1.targetFlower.position.x) < tolerance &&
            fabs(bee1.position.y - bee1.targetFlower.position.y) < tolerance) {
            bee1.velocity = 0.0f;
        } else {
            Move(&bee1.position, &bee1.direction, &bee1.velocity, &bee1.animSprite.sprite.rotation);
            bee1.direction = GetDirectionToObject(&bee1.targetFlower, bee1.position);
        }

        UpdateSpriteDestRec(&bee1.animSprite.sprite, &bee1.position);
        UpdateAnimSprite(&bee1.animSprite);

        UpdateCamera2DTarget(&camera, &player.position, 5.0f);

        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            float zoomSpeed = 0.10f;
            float scaleFactor = 1.0f + (zoomSpeed*fabsf(wheel));
            if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
            float targetZoom = Clamp(camera.zoom*scaleFactor, 5.0f, 10.0f);
            camera.zoom = Lerp(camera.zoom, targetZoom, 0.1f);
        }

        // Render
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                RenderTileSprite(&floor);
                RenderSprite(&hive.sprite);
                RenderObjectArray(&flowers);
                RenderSprite(&bee1.animSprite.sprite);
                RenderSprite(&player.animSprite.sprite);  
            EndMode2D();
            DrawFPS(10,10);
        EndDrawing();
    }
    // Unload
    UnloadTexture(floor.sprite.texture);
    UnloadTexture(hive.sprite.texture);
    UnloadTexture(flower);
    UnloadTexture(bee1.animSprite.sprite.texture);
    UnloadTexture(player.animSprite.sprite.texture);
    UnloadMusicStream(music);
    free(flowers.data);
    // Close
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
