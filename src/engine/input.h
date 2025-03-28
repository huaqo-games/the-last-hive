#ifndef INPUT_H
#define INPUT_H

typedef struct {
    Vector2 screenPosition;
    Vector2 worldPosition;
    float zoomSpeed;
    float minZoom;
    float maxZoom;
    float scaleFactor;
    float wheelMove;
    bool leftButton;
    bool rightButton;
    Texture2D cursorTexture;
} Mouse;

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

    mouse->screenPosition = GetMousePosition();
    mouse->worldPosition = GetScreenToWorld2D(GetMousePosition(), *camera);
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

#endif //INPUT_H
