#ifndef ANIMSPRITE_H
#define ANIMSPRITE_H
#include <raylib.h>
#include "sprite.h"

typedef struct {
    Sprite sprite;    
    int currentFrame;       
    int maxFrame;           
    int framesCounter;      
    int framesSpeed;        
    float animTimer;
    bool isVertical;        
} AnimSprite;

void UpdateAnimSprite(AnimSprite *animSprite) {
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

    Vector2 newFramePos = {
        .x = animSprite->isVertical ? animSprite->sprite.sourceRec.x
                                    : animSprite->currentFrame * animSprite->sprite.frameSize.x,
        .y = animSprite->isVertical ? animSprite->currentFrame * animSprite->sprite.frameSize.y
                                    : animSprite->sprite.sourceRec.y
    };

    UpdateSpriteSourceRec(&animSprite->sprite, &newFramePos);
}

#endif // ANIMSPRITE_H
