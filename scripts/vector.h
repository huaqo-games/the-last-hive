#ifndef VECTOR_H
#define VECTOR_H
#include <raylib.h>

typedef struct {
    Vector2 *data;
    size_t count;
} Vector2Array;

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

#endif // VECTOR_H
