#ifndef PHYSICS_H
#define PHYSICS_H
#include <raylib.h>
#include <raymath.h> 


typedef struct {
    Vector2 position;
    Vector2 direction;
    float speed;
} Physics;

Vector2 GetVelocity(Vector2 *direction, float *speed){
    return Vector2Scale(*direction, *speed * GetFrameTime());
}

void Move(Vector2 *position, Vector2 *direction, float *speed) {
    *position = Vector2Add(*position, GetVelocity(direction, speed));
}

#endif // PHYSICS_H
