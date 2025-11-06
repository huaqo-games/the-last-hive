#include "engine.h"

bool IsVectorZero(Vector2 v) {
    float epsilon = 0.01f;
    return (fabs(v.x) < epsilon && fabs(v.y) < epsilon);
}

Vector2 GetRandomVector(const Rectangle bounds) {
    return (Vector2){
        bounds.x + (float)GetRandomValue(0, 10000) / 10000.0f * bounds.width,
        bounds.y + (float)GetRandomValue(0, 10000) / 10000.0f * bounds.height
    };
}

Vector2 RotationToVector2(float rotation)
{
	float rad = rotation * (PI / 180.0f);
	Vector2 vec = { cosf(rad), sinf(rad) };
	return vec;
}

float Vector2ToRotation(Vector2 vec)
{
    float rad = atan2f(vec.y, vec.x);
    float deg = rad * (180.0f / PI);
    return deg; 
}
