#ifndef HIVE_H
#define HIVE_H
#include "../engine/object.h"

Object CreateHive(Texture2D texture, float frameWidth){
    return (Object) {
        .sprite = {
            .texture = texture,
            .sourceRec = (Rectangle){0.0f, 0.0f, frameWidth, frameWidth},
            .destRec = (Rectangle){0.0f, 0.0f, frameWidth, frameWidth},
            .origin = (Vector2){frameWidth / 2, frameWidth / 2},
            .rotation = 0.0f,
            .color = WHITE
        },
        .position = (Vector2){0.0f, 0.0f}
    };
}

#endif // HIVE_H
