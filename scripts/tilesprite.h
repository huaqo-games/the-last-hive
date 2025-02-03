#ifndef TILESPRITE_H
#define TILESPRITE_H
#include <raylib.h>
#include "sprite.h"

typedef struct {
    Sprite sprite;
    Rectangle bounds;
} TileSprite;

void UpdateTileSpriteBounds(TileSprite *tileSprite, const Camera2D *camera){
    tileSprite->bounds.x = (int)((camera->target.x - (GetScreenWidth() / 2.0f / camera->zoom)) / tileSprite->sprite.frameSize.x) - 1;
    tileSprite->bounds.width = (int)((camera->target.x + (GetScreenWidth() / 2.0f / camera->zoom)) / tileSprite->sprite.frameSize.x) + 1;
    tileSprite->bounds.y = (int)((camera->target.y - (GetScreenHeight() / 2.0f / camera->zoom)) / tileSprite->sprite.frameSize.y) - 1;
    tileSprite->bounds.height = (int)((camera->target.y + (GetScreenHeight() / 2.0f / camera->zoom)) / tileSprite->sprite.frameSize.y) + 1;
}

void RenderTileSprite(TileSprite *tileSprite){
    for (float y = tileSprite->bounds.y; y <= tileSprite->bounds.height; y++)
        {
            for (float x = tileSprite->bounds.x; x <= tileSprite->bounds.width; x++)
            {
                Vector2 tilePosition = {x * tileSprite->sprite.frameSize.x, y * tileSprite->sprite.frameSize.y};
                UpdateSpriteDestRec(&tileSprite->sprite, &tilePosition);
                RenderSprite(&tileSprite->sprite);  
            }
        }
}

#endif //TILESPRITE_H
