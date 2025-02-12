#include <raylib.h> 
#include "sprite.h"
#include "animation.h"
#include "tilesprite.h"
#include "vector.h"
#include "object.h"
#include "physics.h"
#include "camera.h"
#include "input.h"

// Structs

typedef struct {
    Sprite sprite;
    Animation animation;
    Physics physics;
} Player;

typedef struct {
    Sprite sprite;
    Animation animation;
    Physics physics;
    Object target;
    Object hive;
    int flowerCount;
} Bee;

int main(void)
{
    // Load
    InitWindow(1280, 720, "The Last Hive"); 

    InitAudioDevice(); 
    Music music = LoadMusicStream("assets/beez.mp3"); 
    PlayMusicStream(music);

    Texture2D flowerTexture = LoadTexture("assets/flower.png");
    Texture2D beeTexture = LoadTexture("assets/character_bee.png");
    Texture2D floorTexture = LoadTexture("assets/grass.png");
    Texture2D hiveTexture = LoadTexture("assets/hive.png");

    TileSprite floor = {
        .sprite = {
            .texture = floorTexture,
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
            .texture = hiveTexture,
            .frameSize = {32.0f,32.0f},
            .sourceRec = {0.0f, 0.0f, 32.0f, 32.0f},
            .destRec = {0.0f, 0.0f, 32.0f, 32.0f},
            .origin = {16.0f, 16.0f},
            .rotation = 0.0f,
            .color = WHITE 
        },
        .position = (Vector2){0.0f,0.0f}
    };

    ObjectArray flowers = CreateObjectArray(&(Object){
        .sprite = {
            .texture = flowerTexture,
            .frameSize = {16.0f, 16.0f},
            .sourceRec = {0.0f, 0.0f, 16.0f, 16.0f},
            .destRec = {0.0f, 0.0f, 16.0f, 16.0f},
            .origin = {8.0f, 8.0f},
            .rotation = 45.0f,
            .color = WHITE
        },
        .position = {0.0f, 0.0f}
    }, 10);
    if (!flowers.data) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    Rectangle flowerField = {-50.0f, -50.0f, 100.0f, 100.0f};
    SetRandomPositionForObjectArray(&flowers, flowerField);

    Player player = {
        .sprite = {
            .texture = beeTexture,
            .frameSize = {16.0f, 16.0f},
            .sourceRec = {0.0f, 0.0f, 16.0f, 16.0f},
            .destRec = {0.0f, 0.0f, 16.0f, 16.0f},
            .origin = {8.0f, 8.0f},
            .rotation = 0.0f,
            .color = WHITE
        },
        .animation = {
            .currentFrame = 0,
            .maxFrame = 4,
            .framesCounter = 0,
            .framesSpeed = 10,
            .animTimer = 0.0f
        },
        .physics = {
            .position = hive.position,
            .direction = (Vector2){0.0f,0.0f},
            .speed = 50.0f
        }
    };

    Bee bee1 = {
        .sprite = {
            .texture = beeTexture,
            .frameSize = {16.0f, 16.0f},
            .sourceRec = {0.0f, 0.0f, 16.0f, 16.0f},
            .destRec = {0.0f, 0.0f, 16.0f, 16.0f},
            .origin = {8.0f, 8.0f},
            .rotation = 0.0f,
            .color = WHITE
        },
        .animation = {
            .currentFrame = 0,
            .maxFrame = 4,
            .framesCounter = 0,
            .framesSpeed = 10,
            .animTimer = 0.0f
        },
        .physics = {
            .position = hive.position,
            .direction = (Vector2){0.0f,0.0f},
            .speed = 10.0f
        },
        .target = *GetRandomObject(&flowers),
        .hive = hive
    };

    Camera2D camera = {
        .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target = player.physics.position,
        .rotation = 0.0f,
        .zoom = 10.0f
    };

    Mouse mouse = {
        .zoomSpeed = 0.10f,
        .minZoom = 5.0f,
        .maxZoom = 10.0f
    };

    // Update & Render
    while (!WindowShouldClose())
    {
        // Update
        UpdateMusicStream(music);

        UpdateTileSpriteBounds(&floor, &camera);

        UpdateMouse(&mouse, &camera);

        if (mouse.leftButton) {
            AddObjectToArray(&flowers, flowers.prototype, mouse.worldPosition);
        }

        UpdateVectorOnInput(&player.physics.direction);
        Move(&player.physics.position, &player.physics.direction, &player.physics.speed);
        UpdateSpriteRotation(&player.sprite, &player.physics.direction);
        UpdateSpriteDestRec(&player.sprite, &player.physics.position);
        UpdateAnimation(&player.animation, GetFrameTime());
        UpdateSpriteSourceRec(&player.sprite, &(Vector2){player.sprite.frameSize.x, player.sprite.frameSize.x * player.animation.currentFrame});

        const float tolerance = 1.0f; 

        if (bee1.flowerCount < 4){
            if (fabs(bee1.physics.position.x - bee1.target.position.x) < tolerance &&
                fabs(bee1.physics.position.y - bee1.target.position.y) < tolerance) {
                bee1.target = *GetRandomObject(&flowers);
                bee1.flowerCount++;
            } else {
                Move(&bee1.physics.position, &bee1.physics.direction, &bee1.physics.speed);
                UpdateSpriteRotation(&bee1.sprite, &bee1.physics.direction);
                bee1.physics.direction = GetDirectionToObject(&bee1.target, bee1.physics.position);
            }
        } else {
            bee1.target = hive;
            if (fabs(bee1.physics.position.x - bee1.target.position.x) < tolerance &&
                fabs(bee1.physics.position.y - bee1.target.position.y) < tolerance) {
                bee1.physics.speed = 0.0f;
            } else {
                Move(&bee1.physics.position, &bee1.physics.direction, &bee1.physics.speed);
                UpdateSpriteRotation(&bee1.sprite, &bee1.physics.direction);
                bee1.physics.direction = GetDirectionToObject(&bee1.target, bee1.physics.position);
            }
        }

        UpdateSpriteDestRec(&bee1.sprite, &bee1.physics.position);
        UpdateAnimation(&bee1.animation, GetFrameTime());
        UpdateSpriteSourceRec(&bee1.sprite, &(Vector2){bee1.sprite.frameSize.x, bee1.sprite.frameSize.x * bee1.animation.currentFrame});
        
        UpdateCamera2DTarget(&camera, &player.physics.position, 5.0f);

        if (mouse.wheelMove != 0)
        {
            UpdateCamera2DZoom(&camera, &mouse.scaleFactor, &mouse.minZoom, &mouse.maxZoom);
        }

        // Render
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                RenderTileSprite(&floor);
                RenderSprite(&hive.sprite);
                RenderObjectArray(&flowers);
                RenderSprite(&bee1.sprite);
                RenderSprite(&player.sprite);  
            EndMode2D();
            DrawFPS(10,10);
        EndDrawing();
    }
    // Unload
    UnloadTexture(floorTexture);
    UnloadTexture(hiveTexture);
    UnloadTexture(flowerTexture);
    UnloadTexture(beeTexture);
    UnloadMusicStream(music);
    free(flowers.data);
    // Close
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
