#ifndef ANIMATION_H
#define ANIMATION_H

typedef struct {    
    int currentFrame;       
    int maxFrame;           
    int framesCounter;      
    int framesSpeed;        
    float animTimer;  
} Animation;

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

#endif // ANIMATION_H
