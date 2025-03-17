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

void UpdateFloor(Floor *Floor, const Camera2D *camera){
    Floor->bounds.x = (int)((camera->target.x - (GetScreenWidth() / 2.0f / camera->zoom)) / Floor->sprite.frameSize.x) - 1;
    Floor->bounds.width = (int)((camera->target.x + (GetScreenWidth() / 2.0f / camera->zoom)) / Floor->sprite.frameSize.x) + 1;
    Floor->bounds.y = (int)((camera->target.y - (GetScreenHeight() / 2.0f / camera->zoom)) / Floor->sprite.frameSize.y) - 1;
    Floor->bounds.height = (int)((camera->target.y + (GetScreenHeight() / 2.0f / camera->zoom)) / Floor->sprite.frameSize.y) + 1;
}

void RenderFloor(Floor *Floor){
    for (int y = (int)Floor->bounds.y; y <= (int)Floor->bounds.height; y++)
        {
            for (int x = (int)Floor->bounds.x; x <= (int)Floor->bounds.width; x++)
            {
                Vector2 floorPosition = {x * Floor->sprite.frameSize.x, y * Floor->sprite.frameSize.y};
                UpdateSpriteDestRec(&Floor->sprite, &floorPosition);
                RenderSprite(&Floor->sprite);  
            }
        }
}

#endif //Floor_H
