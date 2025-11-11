#include "engine.h"

Vector2 GetDirectionBetweenTwoVectors(Vector2 vec1, Vector2 vec2)
{
	Vector2 dir = {vec2.x - vec1.x, vec2.y - vec1.y};	
	dir = Vector2Normalize(dir);
	return dir;
}

float GetDistanceBetweenTwoVectors(Vector2 vec1, Vector2 vec2)
{
    float dx = vec1.x - vec2.x;
    float dy = vec1.y - vec2.y;
    return sqrtf(dx * dx + dy * dy);
}

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

