#ifndef BEE_H
#define BEE_H
#include <sprite.h>
#include <animation.h>
#include <physics.h>
#include <object.h>

typedef enum {
    FLYING
} BeeAnimationState;

typedef struct {
    Vector2 position;
} Target;

typedef struct {
    Vector2 position;
} Hive;

typedef struct
{
    Sprite sprite;
    Animation animation;
    Physics physics;
    Target target;
    Hive hive;
    int flowerCount;
} Bee;

Bee CreateBee(BeeAnimationState animState, Texture2D texture, float frameWidth, int maxFrame, int framesSpeed, Vector2 position, float speed, Vector2 targetPosition, Vector2 basePosition){
    return (Bee){
        .sprite = {
            .texture = texture,
            .frameSize = {frameWidth, frameWidth},
            .sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
            .destRec = {0.0f, 0.0f, frameWidth, frameWidth},
            .origin = {frameWidth / 2, frameWidth / 2},
            .rotation = 0.0f,
            .color = WHITE
        },
        .animation = {
            .state = animState,
            .currentFrame = 0,
            .maxFrame = maxFrame,
            .framesCounter = 0,
            .framesSpeed = framesSpeed,
            .animTimer = 0.0f
        },
        .physics = {
            .position = position,
            .direction = (Vector2){0.0f,0.0f},
            .speed = speed
        },
        .target = { .position = targetPosition },
        .hive = { .position = basePosition },
    };
}

void UpdateBee(Bee* bee, Array* flowers){
    const float tolerance = 1.0f;

    // Flower *randomFlower = (Flower *)GetRandomElementFromArray(flowers);
    // printf("\n\n\n\n\n\n\n Random flower position: {%f, %f}\n\n\n\n\n\n\n", randomFlower->position.x, randomFlower->position.y);
    // bee->target.position = randomFlower->position;

    // Check if bee has collected from flowers
    if (bee->flowerCount < flowers->count) {
        // Has it reached the target?
        if (fabs(bee->physics.position.x - bee->target.position.x) < tolerance &&
            fabs(bee->physics.position.y - bee->target.position.y) < tolerance) {
            
            // Increase flower count and set new target
            bee->flowerCount++;
            Flower* randomFlower = (Flower*)GetRandomElementFromArray(flowers);
            bee->target.position = randomFlower->position;
        }
    } else {
        // Go back to hive
        bee->target.position = bee->hive.position;

        // Stop moving once reached hive
        if (fabs(bee->physics.position.x - bee->target.position.x) < tolerance &&
            fabs(bee->physics.position.y - bee->target.position.y) < tolerance) {
            bee->physics.speed = 0.0f;
        }
    }

    Vector2 direction = GetPhysicsDirection(bee->target.position, bee->physics.position);

    UpdatePhysics(&bee->physics, direction);
    UpdateSpriteRotation(&bee->sprite, &bee->physics.direction);
    UpdateSpriteDestRec(&bee->sprite, &bee->physics.position);
    UpdateAnimation(&bee->animation, GetFrameTime());
    UpdateSpriteSourceRec(&bee->sprite, &(Vector2){bee->sprite.frameSize.x * bee->animation.state, bee->sprite.frameSize.x * bee->animation.currentFrame});
}

#endif // BEE_H
