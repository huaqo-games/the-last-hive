#ifndef SPRITE_H
#define SPRITE_H
#include <raylib.h>

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
