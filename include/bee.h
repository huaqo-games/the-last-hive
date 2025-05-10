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

typedef struct
{
    Sprite sprite;
    Animation animation;
    float defaultSpeed;
    Physics physics;
    Vector2 defaultTarget;
    Target target;
    int visitedFlowers;
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
        .defaultSpeed = speed,
        .physics = {
            .position = position,
            .direction = (Vector2){0.0f,0.0f},
            .speed = speed
        },
        .defaultTarget = basePosition,
        .target = { .position = targetPosition },
    };
}

void UpdateBee(Bee* bee, Array* flowers){
    const float tolerance = 1.0f;

    bool allPollinated = true;
    for (int i = 0; i < flowers->count; i++) {
        Flower* flower = (Flower*)GetElementAtIndex(flowers, i);
        printf("\n\n\n\n\nFlower Coordinate: {%f, %f}\n\n\n\n\n", flower->position.x, flower->position.y);
        if (!flower->pollinated)
        {
            allPollinated = false;
            printf("\n\n\n\n\n\n\n\nNew unpolinated.\n\n\n\n\n\n\n\n");
            break;
        }
    }

    if (!allPollinated) {
        // Has the bee reached the target?
        if (fabs(bee->physics.position.x - bee->target.position.x) < tolerance &&
            fabs(bee->physics.position.y - bee->target.position.y) < tolerance) {

            // Mark the flower as pollinated
            for (int i = 0; i < flowers->count; i++) {
                Flower* flower = (Flower*)GetElementAtIndex(flowers, i);
                if (Vector2Distance(flower->position, bee->target.position) < tolerance) {
                    if (!flower->pollinated) {
                        flower->pollinated = true;
                        bee->visitedFlowers++;
                    }
                    break;
                }
            }

            // Pick a new random unpollinated flower as target
            Flower* newTarget = NULL;
            int safety = 100;
            while (newTarget == NULL && safety-- > 0) {
                Flower* candidate = (Flower*)GetRandomElementFromArray(flowers);
                if (!candidate->pollinated) {
                    newTarget = candidate;
                }
            }

            if (newTarget != NULL) {
                bee->target.position = newTarget->position;
                bee->physics.speed = bee->defaultSpeed;  // Ensure bee starts moving again
            }
        }
    } else {
            // All pollinated: return to hive
            bee->target.position = bee->defaultTarget;

            if (Vector2Distance(bee->physics.position, bee->target.position) < tolerance) {
                bee->physics.speed = 0.0f;
            } else {
                // bee->target.position = bee->defaultTarget;
                bee->physics.speed = bee->defaultSpeed;
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
