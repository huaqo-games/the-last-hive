#include "engine.h"

void UpdateAnimation(Animation *animation, float deltaTime) {
    animation->animTimer += deltaTime;
    float frameTime = 1.0f / animation->framesSpeed;

    if (animation->animTimer < frameTime) {
        return;
    }

    animation->animTimer -= frameTime;
    animation->currentFrame++;

    if (animation->currentFrame >= animation->maxFrame) {
        animation->currentFrame = 0;
    }
}
