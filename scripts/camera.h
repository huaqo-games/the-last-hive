#ifndef CAMERA_H
#define CAMERA_H
#include <raymath.h>
#include "input.h" 

void UpdateCamera2DTarget(Camera2D *camera, Vector2 *position, const float smoothness){
    camera->target = Vector2Lerp(camera->target, *position, smoothness * GetFrameTime());
}

void UpdateCamera2DZoom(Camera2D *camera, const float *scaleFactor, const float *minZoom, const float *maxZoom){
    float targetZoom = Clamp(camera->zoom * *scaleFactor, *minZoom, *maxZoom);
    camera->zoom = Lerp(camera->zoom, targetZoom, 0.1f);
}

#endif // CAMERA_H
