#ifndef INPUT_H
#define INPUT_H
#include <raymath.h> 

typedef struct {
    Vector2 worldPosition;
    float zoomSpeed;
    float minZoom;
    float maxZoom;
    float scaleFactor;
    float wheelMove;
    bool leftButton;
    bool rightButton;
} Mouse;

void UpdateMouse(Mouse *mouse, Camera2D *camera) {
    mouse->worldPosition = GetScreenToWorld2D(GetMousePosition(), *camera);
    mouse->leftButton = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    mouse->rightButton = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    
    // Calculate zoom scale factor
    mouse->wheelMove = GetMouseWheelMove();
    if (mouse->wheelMove != 0) {
        float zoomFactor = 1.0f + (mouse->zoomSpeed * fabsf(mouse->wheelMove));
        mouse->scaleFactor = (mouse->wheelMove < 0) ? (1.0f / zoomFactor) : zoomFactor;
    } else {
        mouse->scaleFactor = 1.0f;
    }
}

void UpdateVectorOnInput(Vector2 *vector){
    *vector = (Vector2){0.0f, 0.0f};
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){ vector->x += 1.0f; }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){ vector->x -= 1.0f; }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){ vector->y += 1.0f; }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){ vector->y -= 1.0f; }
    if (Vector2Length(*vector) > 0.0f) { *vector = Vector2Normalize(*vector); }
}

#endif //INPUT_H
