#ifndef GAMEGUI_H
#define GAMEGUI_H

#include "sprite.h"
#include <raylib.h>

typedef enum {
    NOT_CLICKED,
    CLICKED
} ButtonState;

typedef struct 
{
    Sprite sprite;
    Vector2 notClicked;
    Vector2 clicked;
    bool isHovered;
} ImageButton;

typedef struct
{
    Sprite sprite;
} ImageElement;

ImageButton CreateImageButton(ButtonState state, Texture2D *texture, const TextureAsset *asset, Vector2 *source, Vector2 *clicked, Rectangle *destRec){
    return (ImageButton){
        .sprite = {
            .texture = *texture,
            .sourceRec = (Rectangle){ source->x, source->y, asset->frameWidth, asset->frameHeight},
            .destRec = *destRec,
            .frameSize = (Vector2){asset->frameWidth, asset->frameHeight},
            .origin = (Vector2){0.0f, 0.0f},
            .rotation = 0.0f,
            .color = WHITE
        },
        .notClicked = (Vector2){source->x, source->y},
        .clicked = *clicked
    };
}

ImageElement CreateImageElement(Texture2D *texture, const TextureAsset *asset, Vector2 *source, Rectangle *destRec){
    return (ImageElement){
        .sprite = {
            .texture = *texture,
            .sourceRec = (Rectangle){ source->x, source->y, asset->frameWidth, asset->frameHeight},
            .destRec = *destRec,
            .frameSize = (Vector2){asset->frameWidth, asset->frameHeight},
            .origin = (Vector2){0.0f, 0.0f},
            .rotation = 0.0f,
            .color = WHITE
        }
    };
}

void PrintImageButton(const ImageButton btn) {
    printf("ImageButton:\n");
    printf("  Sprite.texture: id = %d\n", btn.sprite.texture.id);
    printf("  Sprite.sourceRec: x = %f, y = %f, width = %f, height = %f\n",
           btn.sprite.sourceRec.x, btn.sprite.sourceRec.y,
           btn.sprite.sourceRec.width, btn.sprite.sourceRec.height);
    printf("  Sprite.destRec: x = %f, y = %f, width = %f, height = %f\n",
           btn.sprite.destRec.x, btn.sprite.destRec.y,
           btn.sprite.destRec.width, btn.sprite.destRec.height);
    printf("  Sprite.frameSize: x = %f, y = %f\n",
           btn.sprite.frameSize.x, btn.sprite.frameSize.y);
    printf("  Sprite.origin: x = %f, y = %f\n",
           btn.sprite.origin.x, btn.sprite.origin.y);
    printf("  Sprite.rotation: %f\n", btn.sprite.rotation);
    printf("  Sprite.color: r = %d, g = %d, b = %d, a = %d\n",
           btn.sprite.color.r, btn.sprite.color.g,
           btn.sprite.color.b, btn.sprite.color.a);
    printf("  notClicked: x = %f, y = %f\n", btn.notClicked.x, btn.notClicked.y);
    printf("  clicked: x = %f, y = %f\n", btn.clicked.x, btn.clicked.y);
}

int isImageButtonClicked(ImageButton *b, Sound soundHover, Sound soundClick){
    if (CheckCollisionPointRec(GetMousePosition(), b->sprite.destRec)) {

        if (!b->isHovered) {
            PlaySound(soundHover);
            b->isHovered = true;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            UpdateSpriteSourceRec(&b->sprite, &b->clicked);
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(soundClick);
            b->isHovered = false;
            UpdateSpriteSourceRec(&b->sprite, &b->notClicked);
            return true;
        }
    } else {
        UpdateSpriteSourceRec(&b->sprite, &b->notClicked);
        b->isHovered = false;
    }
    return false;
}

void renderImageButton(ImageButton *b) {
    RenderSprite(&b->sprite);
}

void renderImageElement(ImageElement *e){
    RenderSprite(&e->sprite);
}


#endif // GAMEGUI_H
