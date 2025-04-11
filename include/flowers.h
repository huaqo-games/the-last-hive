#ifndef FLOWERS_H
#define FLOWERS_H

#include <object.h>

ObjectArray CreateFlowers(Texture2D texture, float frameWidth, float rotation, float fieldSize)
{
    ObjectArray flowers = CreateObjectArray(&(Object){
                                                .sprite = {
                                                    .texture = texture,
                                                    .sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
                                                    .destRec = {0.0f, 0.0f, frameWidth, frameWidth},
                                                    .origin = {frameWidth / 2, frameWidth / 2},
                                                    .rotation = rotation,
                                                    .color = WHITE},
                                                .position = {0.0f, 0.0f}},
                                            10);

    if (!flowers.data)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    SetRandomPositionForObjectArray(&flowers, (Rectangle){-fieldSize, -fieldSize, fieldSize * 2, fieldSize * 2});

    return flowers;
}

#endif // FLOWERS_H
