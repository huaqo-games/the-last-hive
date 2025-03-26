#ifndef SPRITE_H
#define SPRITE_H

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

void PrintSprite(const Sprite *sprite) {
    printf("Sprite:\n");
    printf("  Sprite.texture: id = %d\n", sprite->texture.id);
    printf("  Sprite.sourceRec: x = %f, y = %f, width = %f, height = %f\n", sprite->sourceRec.x, sprite->sourceRec.y, sprite->sourceRec.width, sprite->sourceRec.height);
    printf("  Sprite.destRec: x = %f, y = %f, width = %f, height = %f\n", sprite->destRec.x, sprite->destRec.y, sprite->destRec.width, sprite->destRec.height);
    printf("  Sprite.frameSize: x = %f, y = %f\n", sprite->frameSize.x, sprite->frameSize.y);
    printf("  Sprite.origin: x = %f, y = %f\n", sprite->origin.x, sprite->origin.y);
    printf("  Sprite.rotation: %f\n", sprite->rotation);
    printf("  Sprite.color: r = %d, g = %d, b = %d, a = %d\n", sprite->color.r, sprite->color.g, sprite->color.b, sprite->color.a);
}

#endif // SPRITE_H
