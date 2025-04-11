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
    Sprite sprite;
    Animation animation;
    Physics physics;
    Object target;
    Object hive;
    int flowerCount;
} Bee;

Bee CreateBee(BeeAnimationState animState, Texture2D texture, float frameWidth, int maxFrame, int framesSpeed, Vector2 position, float speed, ObjectArray* target, Object* base){
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
        .target = *GetRandomObject(target),
        .hive = *base
    };
}

void UpdateBee(Bee* bee, ObjectArray* flowers, Object* hive){
    const float tolerance = 1.0f; 

    if (bee->flowerCount < 4){
        if (fabs(bee->physics.position.x - bee->target.position.x) < tolerance &&
            fabs(bee->physics.position.y - bee->target.position.y) < tolerance) {
            bee->target = *GetRandomObject(flowers);
            bee->flowerCount++;
        } else {
        }
    } else {
        bee->target = *hive;
        if (fabs(bee->physics.position.x - bee->target.position.x) < tolerance &&
            fabs(bee->physics.position.y - bee->target.position.y) < tolerance) {
            bee->physics.speed = 0.0f;
        } else {
        }
    }
    
    UpdatePhysics(&bee->physics, GetDirectionToObject(&bee->target, bee->physics.position));
    UpdateSpriteRotation(&bee->sprite, &bee->physics.direction);
    UpdateSpriteDestRec(&bee->sprite, &bee->physics.position);
    UpdateAnimation(&bee->animation, GetFrameTime());
    UpdateSpriteSourceRec(&bee->sprite, &(Vector2){bee->sprite.frameSize.x * bee->animation.state, bee->sprite.frameSize.x * bee->animation.currentFrame});
}

#endif // BEE_H
