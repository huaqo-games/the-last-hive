#include "engine.h"

Mouse CreateMouse(float zoomSpeed, float minZoom, float maxZoom, Texture2D *texture){
    HideCursor();
    return (Mouse){
        .zoomSpeed = zoomSpeed,
        .minZoom = minZoom,
        .maxZoom = maxZoom,
        .cursorTexture = *texture
    };
}

void UpdateMouseScreen(Mouse *mouse){
    mouse->screenPosition = GetMousePosition();

}

void UpdateMouse(Mouse *mouse, Camera2D *camera) {

    Vector2 pos = GetMousePosition();
    mouse->screenPosition = pos;
    mouse->worldPosition = GetScreenToWorld2D(pos, *camera);
    mouse->leftButton = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    mouse->rightButton = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    
    mouse->wheelMove = GetMouseWheelMove();
    if (mouse->wheelMove != 0) {
        float zoomFactor = 1.0f + (mouse->zoomSpeed * fabsf(mouse->wheelMove));
        mouse->scaleFactor = (mouse->wheelMove < 0) ? (1.0f / zoomFactor) : zoomFactor;
    } else {
        mouse->scaleFactor = 1.0f;
    }
}

Vector2 GetDirectionVector(void){
    Vector2 vector = {.x = 0.0f, .y = 0.0f};
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){vector.x += 1.0f; }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){ vector.x -= 1.0f; }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){ vector.y -= 1.0f; }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){ vector.y += 1.0f; }
    if (Vector2Length(vector) > 0.0f) {vector = Vector2Normalize(vector); }
    return vector;
}
