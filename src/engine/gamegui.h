#ifndef GAMEGUI_H
#define GAMEGUI_H

#include "sprite.h"

typedef struct 
{
    int state;
    Rectangle textureRecs[2];
    Rectangle buttonBounds;
    Texture2D texture;
} ImageButton;

void initImageButton(ImageButton *b, Rectangle textureRecs[2], Rectangle buttonBounds, Texture2D texture){
    b->textureRecs[0] = textureRecs[0];
    b->textureRecs[1] = textureRecs[1];
    b->buttonBounds = buttonBounds;
    b->texture = texture;
    b->state = 0;
}

int isImageButtonClicked(ImageButton *b){
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, b->buttonBounds)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) b->state = 1;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
        {
            b->state = 0;
            return true;
        }
    } else {
        b->state = 0;
    }
    return false;
}

void renderImageButton(ImageButton *b) {
    Sprite sprite;
    sprite.texture   = b->texture;
    sprite.sourceRec = b->textureRecs[b->state];
    sprite.destRec   = b->buttonBounds;   
    sprite.origin    = (Vector2){ 0, 0 };    
    sprite.rotation  = 0.0f;                        
    sprite.color     = WHITE;
    RenderSprite(&sprite);
}


#endif // GAMEGUI_H
