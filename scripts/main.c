#include <raylib.h> 
// WHITE, Color,
// KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, IsKeyDown(), 
// InitWindow(), SetTargetFPS(), WindowShouldClose(), GetFrameTime(), CloseWindow()
// Music, InitAudioDevice(), LoadMusicStream(), PlayMusicStream(), UpdateMusicStream(), UnloadMusicStream(), CloseAudioDevice(),
// Texture2D, Rectangle, Vector2, LoadTexture(), DrawTexturePro(), UnloadTexture(), 
// BeginDrawing(), EndDrawing(), ClearBackground(),
// Camera2D, BeginMode2D(), EndMode2D()
#include <raymath.h> // Vector2Length(), Vector2Normalize(), Vector2Add(), Vector2Scale(), Lerp()
#include <stdlib.h> // rand(), srand()
#include <time.h> // time()
#include <string.h> // memcpy()
#include <stdio.h>

// Structs

typedef struct {
    Vector2 *data;
    size_t count;
} Vector2Array;

typedef struct {
    Texture2D texture;      // Texture for the sprite
    Rectangle sourceRec;    // Source rectangle for the texture
    Rectangle destRec;      // Destination rectangle for the texture
    Vector2 frameSize;      // Size of the frame in the texture
    Vector2 origin;         // Origin point for rotation and positioning
    float rotation;         // Rotation angle
    Color color;
} Sprite;

typedef struct {
    Sprite sprite;
    Rectangle bounds;
} TileSprite;

typedef struct {
    Sprite sprite;    // Base sprite for rendering
    int currentFrame;       // Current animation frame
    int maxFrame;           // Total number of frames
    int framesCounter;      // Counter to control frame speed
    int framesSpeed;        // Speed of the animation (frames per second)
    float animTimer;
    bool isVertical;        // Whether the animation frames are arranged vertically
} AnimSprite;

typedef struct {
    Sprite sprite;
    Vector2 position;
} Object;

typedef struct {
    Object *data;
    const Object *prototype;
    size_t count;
} ObjectArray;

typedef struct {
    AnimSprite animSprite;
    Vector2 position;
    Vector2 direction;
    float velocity;
} Entity;

// Pure functions

float GetRandomFloat(const float min, const float max){
    return min + (float)rand() / (float)(RAND_MAX / (max - min));
}

Vector2 GetRandomVector(const Rectangle bounds){
    return (Vector2){
        GetRandomFloat(bounds.x, bounds.x + bounds.width),
        GetRandomFloat(bounds.y, bounds.y + bounds.height)
    };
}

ObjectArray CreateObjectArray(const Object *prototype, const size_t count) {
    ObjectArray objects = {0};

    if (count <= 0) {
        printf("Objects size must be greater than 0.\n");
        return objects;
    }

    objects.count = count;
    objects.data = malloc(count * sizeof(Object));

    if (!objects.data) {
        printf("Memory allocation of objects failed.\n");
        return objects;
    }

    objects.prototype = prototype;

    for (int i = 0; i < count; i++) {
        objects.data[i].position = prototype->position;
        objects.data[i].sprite = prototype->sprite;
    }
    return objects;
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

void SetPositionOnDirectionAndVelocity(const Vector2 *direction, const float *velocity, Vector2 *position) {
    *position = Vector2Add(*position, Vector2Scale(*direction, *velocity * GetFrameTime()));
}

void SetDestRecOnPosition(const Vector2 *position, Sprite *sprite){
    Rectangle newDestRec = {
        position->x, 
        position->y,
        sprite->frameSize.x,
        sprite->frameSize.y
    };
    sprite->destRec = newDestRec;
}

void SetAnimSpriteOnFrameTime(AnimSprite *animSprite) {
    animSprite->animTimer += GetFrameTime();
    float frameTime = 1.0f / animSprite->framesSpeed;

    if (animSprite->animTimer < frameTime) {
        return;
    }

    animSprite->animTimer -= frameTime;
    animSprite->currentFrame++;

    if (animSprite->currentFrame >= animSprite->maxFrame) {
        animSprite->currentFrame = 0;
    }

    if (animSprite->isVertical) {
        animSprite->sprite.sourceRec.y = animSprite->currentFrame * animSprite->sprite.frameSize.y;
    } else {
        animSprite->sprite.sourceRec.x = animSprite->currentFrame * animSprite->sprite.frameSize.x;
    }
}

void SetRotationOnDirection(const Vector2 *direction, float *rotationDegree){
    if(Vector2Length(*direction) <= 0.0f){
        return;
    }
    float targetRotationDegree = (float)atan2(direction->y, direction->x) * (180.0f / PI) + 90.0f;
    *rotationDegree = Lerp(*rotationDegree, targetRotationDegree, 0.1f); 
}

void SetPositionForObjectArray(ObjectArray *objects, const Vector2Array *positions) {
    if (positions->count != objects->count) {
        printf("Warning: Position array size (%zu) does not match ObjectArray size (%zu)\n", positions->count, objects->count);
        return;
    }

    for (size_t i = 0; i < objects->count; i++) {
        objects->data[i].position = positions->data[i];
        objects->data[i].sprite.destRec.x = positions->data[i].x;
        objects->data[i].sprite.destRec.y = positions->data[i].y;
    }
}

void SetRandomPositionForObjectArray(ObjectArray *objects, const Rectangle bounds){
    srand((unsigned int)time(NULL));
    for (int i = 0; i < objects->count; i++) {
        Vector2 position = GetRandomVector(bounds);
        objects->data[i].position = position;
        objects->data[i].sprite.destRec.x = position.x;
        objects->data[i].sprite.destRec.y = position.y;
    }
}

void UpdateEntity(Entity *entity) {
    GetDirectionFromInput(&entity->direction);
    SetRotationOnDirection(&entity->direction, &entity->animSprite.sprite.rotation);
    SetPositionOnDirectionAndVelocity(&entity->direction, &entity->velocity, &entity->position);
    SetDestRecOnPosition(&entity->position, &entity->animSprite.sprite);
    SetAnimSpriteOnFrameTime(&entity->animSprite);
}

void UpdateTileSprite(TileSprite *tileSprite, const Camera2D *camera){
    tileSprite->bounds.x = (int)((camera->target.x - (GetScreenWidth() / 2.0f / camera->zoom)) / tileSprite->sprite.frameSize.x) - 1;
    tileSprite->bounds.width = (int)((camera->target.x + (GetScreenWidth() / 2.0f / camera->zoom)) / tileSprite->sprite.frameSize.x) + 1;
    tileSprite->bounds.y = (int)((camera->target.y - (GetScreenHeight() / 2.0f / camera->zoom)) / tileSprite->sprite.frameSize.y) - 1;
    tileSprite->bounds.height = (int)((camera->target.y + (GetScreenHeight() / 2.0f / camera->zoom)) / tileSprite->sprite.frameSize.y) + 1;
}

void UpdateCamera2D(Camera2D *camera, const Entity *player, const float smoothness){
    camera->target = Vector2Lerp(camera->target, player->position, smoothness * GetFrameTime());
}

void SwapAndPopObjectsArrayOnCollision(ObjectArray *objects, const Rectangle rec){
    for (int i = 0; i < objects->count; i++){

        if (CheckCollisionRecs(rec, objects->data[i].sprite.destRec)){
            if (objects->count == 1) {
                objects->count = 0;
                break;
            }
            objects->data[i] = objects->data[objects->count - 1];
            objects->count--;
            i--;
        }
    }
}
 
void RenderSprite(const Sprite *sprite){
    DrawTexturePro(
        sprite->texture, 
        sprite->sourceRec, 
        sprite->destRec, 
        sprite->origin, 
        sprite->rotation, 
        sprite->color
    );
}

void RenderTileSprite(TileSprite *tileSprite){
    for (float y = tileSprite->bounds.y; y <= tileSprite->bounds.height; y++)
        {
            for (float x = tileSprite->bounds.x; x <= tileSprite->bounds.width; x++)
            {
                Vector2 tilePosition = {x * tileSprite->sprite.frameSize.x, y * tileSprite->sprite.frameSize.y};
                SetDestRecOnPosition(&tilePosition, &tileSprite->sprite);
                RenderSprite(&tileSprite->sprite);  
            }
        }
}

void RenderObjectArray(const ObjectArray *objects){
    for (int i = 0; i < objects->count; i++){
        RenderSprite(&objects->data[i].sprite);
    }
}

// Main

int main(void)
{
    // Load
    // SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Lazy Bee"); 
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
    }, 10);
    if (!flowers.data) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    Rectangle flowerField = {-50.0f, -50.0f, 100.0f, 100.0f};
    SetRandomPositionForObjectArray(&flowers, flowerField);
    Entity player = {
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
    Camera2D camera = {
        .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target = player.position,
        .rotation = 0.0f,
        .zoom = 10.0f
    };
    float followSmoothness = 5.0f;
    Vector2 mousePoint = { 0.0f, 0.0f};

    // Update & Render
    while (!WindowShouldClose())
    {
        // Update
        mousePoint = GetMousePosition();
        UpdateMusicStream(music);
        UpdateTileSprite(&floor, &camera);
        UpdateEntity(&player);
        UpdateCamera2D(&camera, &player, followSmoothness);
        SwapAndPopObjectsArrayOnCollision(&flowers, player.animSprite.sprite.destRec);
        // Render
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                RenderTileSprite(&floor);
                RenderSprite(&hive.sprite);
                RenderObjectArray(&flowers);
                RenderSprite(&player.animSprite.sprite);  
            EndMode2D();
            DrawFPS(10,10);
        EndDrawing();
    }
    // Unload
    UnloadTexture(floor.sprite.texture);
    UnloadTexture(hive.sprite.texture);
    UnloadTexture(flower);
    UnloadTexture(player.animSprite.sprite.texture);
    UnloadMusicStream(music);
    free(flowers.data);
    // Close
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
