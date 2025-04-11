#ifndef PHYSICS_H
#define PHYSICS_H

#include <raymath.h>

typedef struct
{
    Vector2 position;
    Vector2 direction;
    Vector2 velocity;
    float speed;
} Physics;

void UpdatePhysicsDirection(Vector2 *direction, Vector2 vector)
{
    *direction = Vector2Normalize(vector);
}

void UpdatePhysicsVelocity(Vector2 *velocity, Vector2 *direction, float *speed)
{
    *velocity = Vector2Scale(*direction, *speed * GetFrameTime());
}

void UpdatePhysicsPosition(Vector2 *position, Vector2 *velocity)
{
    *position = Vector2Add(*position, *velocity);
}

void UpdatePhysicsSpeed(float *speed, float *newSpeed)
{
    *speed = *newSpeed;
}

void UpdatePhysics(Physics *physics, Vector2 direction)
{
    UpdatePhysicsDirection(&physics->direction, direction);
    UpdatePhysicsVelocity(&physics->velocity, &physics->direction, &physics->speed);
    UpdatePhysicsPosition(&physics->position, &physics->velocity);
}

#endif // PHYSICS_H
