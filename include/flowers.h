#ifndef FLOWERS_H
#define FLOWERS_H

#include "array.h"

typedef enum {
    CHILD,
    TEEN,
    ADULT
} AGE;

typedef struct {
    Sprite sprite;
    Vector2 position;
    AGE age;
    float ageTimer;
} Flower;

Array* CreateFlowers(Texture2D texture, float frameWidth, float rotation, float fieldSize)
{
    Array* flowers = CreateArray(10);

    if(!flowers) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        Flower* flower = malloc(sizeof(Flower));
        *flower = (Flower){
            .sprite = {
                .texture = texture,
                .sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
                .destRec = {(float)GetRandomValue(-fieldSize,fieldSize), (float)GetRandomValue(-fieldSize,fieldSize), frameWidth, frameWidth},
                .origin = {frameWidth / 2, frameWidth / 2},
                .rotation = rotation,
                .color = WHITE,
            },
            .age = CHILD,
            .ageTimer = 0.0f
        };
        AddElementToArray(flowers, flower);
    }
    return flowers;
}


void UpdateFlower(void* element) {
    Flower* f = (Flower*)element;
    if (!f) return;

    f->ageTimer += 1;

    if (f->age == CHILD && f->ageTimer >= 3000.0f) {
        f->age = TEEN;
        f->sprite.sourceRec.x = f->sprite.sourceRec.width; 
    }
    else if (f->age == TEEN && f->ageTimer >= 6000.0f) {
        f->age = ADULT;
        f->sprite.sourceRec.x = 2.0f * f->sprite.sourceRec.width;
    }
}


void RenderFlower(void* element)
{
    Flower* f = (Flower*)element;
    if (!f) return;
    RenderSprite(&(f->sprite));
}




#endif // FLOWERS_H
