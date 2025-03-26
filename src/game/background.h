#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "../engine/sprite.h"
#include "raylib.h"

typedef struct {
    Sprite sprite;
    float scrolling;
    float scale;
    float scrollSpeed;
    Vector2 pos;
} Background;

void InitBackground(float scrollSpeed, Background *bg, Texture2D *texture, const TextureAsset *backgroundAsset){
    bg->scrolling = 0.0f;
    bg->scrollSpeed = scrollSpeed;
    bg->scale = 1.0f;
    bg->sprite = (Sprite){
        .texture = *texture,
        .sourceRec = (Rectangle){0.0f,0.0f,backgroundAsset->frameWidth, backgroundAsset->frameHeight},
        .destRec = (Rectangle){0.0f,0.0f,(float)GetScreenWidth(),(float)GetScreenHeight()},
        .origin = (Vector2){0.0f,0.0f},
        .rotation = 0.0f,
        .color = WHITE
    };
}

void UpdateBackground(Background *bg){
    bg->scrolling -= bg->scrollSpeed;

    if (bg->scrolling <= -bg->sprite.texture.width * bg->scale) {
        bg->scrolling = 0;
    }

    bg->pos = (Vector2){ bg->scrolling, 0.0f };
    UpdateSpriteDestRec(&bg->sprite, &bg->pos);
}

void RenderBackground(Background *bg){

    Sprite temp0 = bg->sprite;
    float newX0 = bg->sprite.destRec.x + bg->sprite.texture.width * bg->scale * 2;
    Vector2 newPos0 = {newX0, bg->sprite.destRec.y};
    UpdateSpriteDestRec(&temp0, &newPos0);
    RenderSprite(&temp0);

    Sprite temp = bg->sprite;
    float newX = bg->sprite.destRec.x + bg->sprite.texture.width * bg->scale;
    Vector2 newPos = {newX, bg->sprite.destRec.y};
    UpdateSpriteDestRec(&temp, &newPos);
    RenderSprite(&temp);

    RenderSprite(&bg->sprite);

    Sprite temp2 = bg->sprite;
    float newX2 = bg->sprite.destRec.x - bg->sprite.texture.width * bg->scale;
    Vector2 newPos2 = {newX2, bg->sprite.destRec.y};
    UpdateSpriteDestRec(&temp2, &newPos2);
    RenderSprite(&temp2);

    Sprite temp3 = bg->sprite;
    float newX3 = bg->sprite.destRec.x - bg->sprite.texture.width * bg->scale * 2;
    Vector2 newPos3 = {newX3, bg->sprite.destRec.y};
    UpdateSpriteDestRec(&temp3, &newPos3);
    RenderSprite(&temp3);


}

#endif // BACKGROUND_H
