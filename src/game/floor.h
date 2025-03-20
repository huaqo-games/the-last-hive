#ifndef Floor_H
#define Floor_H
#include "../engine/sprite.h"

typedef struct {
    Sprite sprite;
    Rectangle bounds;
} Floor;

Floor CreateFloor(Texture2D texture, float textureWidth){
    return (Floor){
        .sprite = {
            .texture = texture,
            .frameSize = {textureWidth,textureWidth},
            .sourceRec = { 0.0f, 0.0f, textureWidth, textureWidth},
            .destRec = {0.0f, 0.0f, textureWidth, textureWidth},
            .origin = {textureWidth / 2, textureWidth / 2},
            .rotation = 0.0f,
            .color = WHITE
        },
        .bounds = {0.0f,0.0f,0.0f,0.0f}
    };
}

void UpdateFloor(Floor *floor, const Camera2D *camera){
    floor->bounds.x = (int)((camera->target.x - (GetScreenWidth() / 2.0f / camera->zoom)) / floor->sprite.frameSize.x) - 1;
    floor->bounds.width = (int)((camera->target.x + (GetScreenWidth() / 2.0f / camera->zoom)) / floor->sprite.frameSize.x) + 1;
    floor->bounds.y = (int)((camera->target.y - (GetScreenHeight() / 2.0f / camera->zoom)) / floor->sprite.frameSize.y) - 1;
    floor->bounds.height = (int)((camera->target.y + (GetScreenHeight() / 2.0f / camera->zoom)) / floor->sprite.frameSize.y) + 1;
}

void RenderFloor(Floor *floor){
    for (int y = (int)floor->bounds.y; y <= (int)floor->bounds.height; y++)
        {
            for (int x = (int)floor->bounds.x; x <= (int)floor->bounds.width; x++)
            {
                Vector2 floorPosition = {x * floor->sprite.frameSize.x, y * floor->sprite.frameSize.y};
                UpdateSpriteDestRec(&floor->sprite, &floorPosition);
                RenderSprite(&floor->sprite);  
            }
        }
}

#endif //Floor_H
