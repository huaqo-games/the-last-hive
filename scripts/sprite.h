#ifndef SPRITE_H
#define SPRITE_H
#include <raylib.h>
#include <raymath.h> 

typedef struct {
    Texture2D texture;      
    Rectangle sourceRec;    
    Rectangle destRec;      
    Vector2 frameSize;      
    Vector2 origin;         
    float rotation;         
    Color color;
} Sprite;

void UpdateSpriteSourceRec(Sprite *sprite, const Vector2 *vector){
    sprite->sourceRec.x = vector->x;
    sprite->sourceRec.y = vector->y;
}

void UpdateSpriteDestRec(Sprite *sprite, const Vector2 *vector){
    sprite->destRec.x = vector->x;
    sprite->destRec.y = vector->y;
}

void UpdateSpriteRotation(Sprite *sprite, Vector2 *vector){
    if(Vector2Length(*vector) <= 0.0f){
        return;
    }
    float targetRotation = (float)atan2(vector->y, vector->x) * (180.0f / PI) + 90.0f;
    sprite->rotation = Lerp(sprite->rotation, targetRotation, 0.1f); 
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

#endif // SPRITE_H
