#include "engine.h"

ImageButton CreateImageButton(ButtonState state, Texture2D *texture, const TextureAsset *asset, Vector2 *source, Vector2 *clicked, Vector2 *hover, Rectangle *destRec){
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
        .hover = *hover,
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

int isImageButtonClicked(ImageButton *b, Sound soundHover, Sound soundClick){
    if (CheckCollisionPointRec(GetMousePosition(), b->sprite.destRec)) {

        if (!b->isHovered) {
            PlaySound(soundHover);
            b->isHovered = true;
            UpdateSpriteSourceRec(&b->sprite, &b->hover);
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            if (!b->isClicked) {
                PlaySound(soundClick);
                b->isClicked = true;
                UpdateSpriteSourceRec(&b->sprite, &b->clicked);
            }
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
        {
            b->isClicked = false;
            b->isHovered = false;
            UpdateSpriteSourceRec(&b->sprite, &b->notClicked);
            return true;
        }
    } else {
        UpdateSpriteSourceRec(&b->sprite, &b->notClicked);
        b->isClicked = false;
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

