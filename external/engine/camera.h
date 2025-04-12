#ifndef CAMERA_H
#define CAMERA_H

#include "input.h" 
#include <raymath.h>

Camera2D CreateCamera(int windowWidth, int windowHeight, Vector2 playerPosition, float initZoom){
    return (Camera2D){
        .offset = (Vector2){windowWidth / 2.0f, windowHeight / 2.0f},
        .target = playerPosition,
        .rotation = 0.0f,
        .zoom = initZoom
    };
}

void UpdateCameraTarget(Camera2D *camera, Vector2 *position, const float smoothness){
    camera->target = Vector2Lerp(camera->target, *position, smoothness * GetFrameTime());
}

void UpdateCameraZoom(Camera2D *camera, const float *scaleFactor, const float *minZoom, const float *maxZoom){
    float targetZoom = Clamp(camera->zoom * *scaleFactor, *minZoom, *maxZoom);
    camera->zoom = Lerp(camera->zoom, targetZoom, 0.1f);
}

void UpdateCamera2D(Camera2D* camera, Vector2* position, Mouse* mouse){
    UpdateCameraTarget(camera, position, 5.0f);
    UpdateCameraZoom(camera, &mouse->scaleFactor, &mouse->minZoom, &mouse->maxZoom);
}


#endif // CAMERA_H
