#include "engine.h"

ObjectArray CreateObjectArray(const Object *prototype, const size_t count) {
    ObjectArray objects = {0};

    if (count == 0) {
        printf("Objects size must be greater than 0.\n");
        return objects;
    }

    objects.count = count;
    objects.data = (Object* )malloc(count * sizeof(Object));

    if (!objects.data) {
        printf("Memory allocation of objects failed.\n");
        return objects;
    }

    objects.prototype = prototype;

    for (int i = 0; i < count; i++) {
        objects.data[i].position = prototype->position;
        objects.data[i].sprite = prototype->sprite;
    }
    return objects;
}

Object* GetRandomObject(ObjectArray *objects){
    if (objects->count == 0 || objects->data == NULL) {
        return NULL;
    }
    return &objects->data[GetRandomValue(0, (int)objects->count-1)];
}

void AddObjectToArray(ObjectArray *objects, const Object *prototype, Vector2 position) {
    Object *newData = (Object* )realloc(objects->data, (objects->count + 1) * sizeof(Object));
    if (newData) {
        objects->data = newData;
        objects->data[objects->count] = *prototype;
        objects->data[objects->count].position = position;
        objects->data[objects->count].sprite.destRec.x = position.x;
        objects->data[objects->count].sprite.destRec.y = position.y;
        objects->count++;
    } else {
        printf("Memory allocation failed while adding an object.\n");
    }
}

void SetPositionForObjectArray(ObjectArray *objects, const Vector2Array *positions) {
    if (positions->count != objects->count) {
        printf("Warning: Position array size (%zu) does not match ObjectArray size (%zu)\n", positions->count, objects->count);
        return;
    }

    for (size_t i = 0; i < objects->count; i++) {
        objects->data[i].position = positions->data[i];
        objects->data[i].sprite.destRec.x = positions->data[i].x;
        objects->data[i].sprite.destRec.y = positions->data[i].y;
    }
}

void SetRandomPositionForObjectArray(ObjectArray *objects, const Rectangle bounds){
    for (int i = 0; i < objects->count; i++) {
        Vector2 position = GetRandomVector(bounds);
        objects->data[i].position = position;
        objects->data[i].sprite.destRec.x = position.x;
        objects->data[i].sprite.destRec.y = position.y;
    }
}

void SwapAndPopObjectsArrayOnRecCollision(ObjectArray *objects, const Rectangle rec){
    for (int i = 0; i < objects->count; i++){

        if (CheckCollisionRecs(rec, objects->data[i].sprite.destRec)){
            if (objects->count == 1) {
                objects->count = 0;
                break;
            }
            objects->data[i] = objects->data[objects->count - 1];
            objects->count--;
            i--;
        }
    }
    objects->data = (Object*)realloc(objects->data, objects->count * sizeof(Object));

}

void SwapAndPopObjectsArrayOnPointCollision(ObjectArray *objects, const Vector2 point){
    for (int i = 0; i < objects->count; i++){

        if (CheckCollisionPointRec(point, objects->data[i].sprite.destRec)){
            if (objects->count == 1) {
                objects->count = 0;
                break;
            }
            objects->data[i] = objects->data[objects->count - 1];
            objects->count--;
            i--;
        }
    }
    objects->data = (Object*)realloc(objects->data, objects->count * sizeof(Object));
}

Vector2 GetDirectionToObject(Object *object, Vector2 position){
    return Vector2Normalize(Vector2Subtract(object->position, position));
}

void RenderObjectArray(const ObjectArray *objects){
    for (int i = 0; i < objects->count; i++){
        RenderSprite(&objects->data[i].sprite);
    }
}

