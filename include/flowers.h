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
    bool pollinated;
} Flower;

Flower DEFAULT_FLOWER;

Array* CreateFlowers(
    int numberOfFlowers,
    Texture2D texture, 
    float frameWidth, 
    float rotation, 
    float fieldSize)
{
    Array* flowers = CreateArray(numberOfFlowers*2);

    if(!flowers) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    DEFAULT_FLOWER = (Flower){
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

    for (int i = 0; i < numberOfFlowers; i++) {
        Flower* flower = malloc(sizeof(Flower));
        *flower = DEFAULT_FLOWER;
        flower->sprite.destRec = (Rectangle){(float)GetRandomValue(-fieldSize,fieldSize), (float)GetRandomValue(-fieldSize,fieldSize), frameWidth, frameWidth};
        flower->position = (Vector2){flower->sprite.destRec.x, flower->sprite.destRec.y};
        AddElementToArray(flowers, flower);
    }
    return flowers;
}

void AddFlower(Array* flowers, Vector2 position){
    Flower* flower = malloc(sizeof(Flower));
    *flower = DEFAULT_FLOWER;
    flower->sprite.destRec.x = position.x;
    flower->sprite.destRec.y = position.y;
    flower->position = (Vector2){flower->sprite.destRec.x, flower->sprite.destRec.y};
    AddElementToArray(flowers, flower);
}


void UpdateFlower(void* element) {
    Flower* f = (Flower*)element;
    if (!f) return;

    if (f->pollinated){
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

}


void RenderFlower(void* element)
{
    Flower* f = (Flower*)element;
    if (!f) return;
    RenderSprite(&(f->sprite));
}




#endif // FLOWERS_H
