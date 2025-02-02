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

typedef struct {
    Entity entity;
    Object targetFlower;
    Object hive;
} Bee;

// Pure functions

bool IsVectorZero(Vector2 v) {
    float epsilon = 0.01f;
    return (fabs(v.x) < epsilon && fabs(v.y) < epsilon);
}

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

void AddObjectToArray(ObjectArray *objects, const Object *prototype, Vector2 position) {
    Object *newData = realloc(objects->data, (objects->count + 1) * sizeof(Object));
    if (newData) {
        objects->data = newData;
        objects->data[objects->count] = *prototype;
        objects->data[objects->count].position = position;
        objects->data[objects->count].sprite.destRec.x = position.x;
        objects->data[objects->count].sprite.destRec.y = position.y;
        objects->count++;
    } else {
        printf("Memory allocation failed while adding an object.\n");
    }
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

Object* GetRandomObject(ObjectArray *objects){
    if (objects->count == 0) {
        return NULL;
    }
    return &objects->data[GetRandomValue(0, (int)objects->count-1)];
}

Vector2 GetDirectionToObject(Object *object, Vector2 position){
    return Vector2Normalize(Vector2Subtract(object->position, position));
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

void UpdatePlayer(Entity *player) {
    GetDirectionFromInput(&player->direction);
    SetRotationOnDirection(&player->direction, &player->animSprite.sprite.rotation);
    SetPositionOnDirectionAndVelocity(&player->direction, &player->velocity, &player->position);
    SetDestRecOnPosition(&player->position, &player->animSprite.sprite);
    SetAnimSpriteOnFrameTime(&player->animSprite);
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

void SwapAndPopObjectsArrayOnRecCollision(ObjectArray *objects, const Rectangle rec){
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

void SwapAndPopObjectsArrayOnPointCollision(ObjectArray *objects, const Vector2 point){
    for (int i = 0; i < objects->count; i++){

        if (CheckCollisionPointRec(point, objects->data[i].sprite.destRec)){
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
    }, 1);
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

    Bee bee1 = {
        .entity = {
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
            .velocity = 5.0f
        },
        .targetFlower = *GetRandomObject(&flowers),
        .hive = hive
    };
    Camera2D camera = {
        .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target = player.position,
        .rotation = 0.0f,
        .zoom = 10.0f
    };
    float followSmoothness = 5.0f;

    // Update & Render
    while (!WindowShouldClose())
    {
        // Update
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            AddObjectToArray(&flowers, flowers.prototype, mouseWorldPos);
        }

        UpdateMusicStream(music);
        UpdateTileSprite(&floor, &camera);
        UpdatePlayer(&player);

        const float tolerance = 1.0f; // Adjust as needed

        if (fabs(bee1.entity.position.x - bee1.targetFlower.position.x) < tolerance &&
            fabs(bee1.entity.position.y - bee1.targetFlower.position.y) < tolerance) {
            bee1.entity.velocity = 0.0f;
        } else {
            SetPositionOnDirectionAndVelocity(&bee1.entity.direction, &bee1.entity.velocity, &bee1.entity.position);
            bee1.entity.direction = GetDirectionToObject(&bee1.targetFlower, bee1.entity.position);
        }

        SetRotationOnDirection(&bee1.entity.direction, &bee1.entity.animSprite.sprite.rotation);
        SetDestRecOnPosition(&bee1.entity.position, &bee1.entity.animSprite.sprite);
        SetAnimSpriteOnFrameTime(&bee1.entity.animSprite);

        UpdateCamera2D(&camera, &player, followSmoothness);

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
                RenderSprite(&bee1.entity.animSprite.sprite);
                // RenderSprite(&player.animSprite.sprite);  
            EndMode2D();
            DrawFPS(10,10);
        EndDrawing();
    }
    // Unload
    UnloadTexture(floor.sprite.texture);
    UnloadTexture(hive.sprite.texture);
    UnloadTexture(flower);
    UnloadTexture(bee1.entity.animSprite.sprite.texture);
    UnloadTexture(player.animSprite.sprite.texture);
    UnloadMusicStream(music);
    free(flowers.data);
    // Close
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
