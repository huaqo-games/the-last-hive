#ifndef PLAYER_H
#define PLAYER_H
#include "../engine/sprite.h"
#include "../engine/animation.h"
#include "../engine/physics.h"
#include "../engine/input.h"

typedef struct {
    Sprite sprite;
    Animation animation;
    Physics physics;
} Player;

Player CreatePlayer(Texture2D texture, float frameWidth, int maxFrame, int framesSpeed, Vector2 startPosition, float speed){
    return (Player){
        .sprite = {
            .texture = texture,
            .frameSize = {frameWidth, frameWidth},
            .sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
            .destRec = {0.0f, 0.0f, frameWidth, frameWidth},
            .origin = {frameWidth / 2, frameWidth / 2},
            .rotation = 0.0f,
            .color = WHITE
        },
        .animation = {
            .currentFrame = 0,
            .maxFrame = maxFrame,
            .framesCounter = 0,
            .framesSpeed = framesSpeed,
            .animTimer = 0.0f
        },
        .physics = {
            .position = startPosition,
            .direction = (Vector2){0.0f,0.0f},
            .speed = speed
        }
    };
}

void UpdatePlayer(Player* player){
    UpdatePhysics(&player->physics, GetDirectionVector());
    UpdateSpriteRotation(&player->sprite, &player->physics.direction);
    UpdateSpriteDestRec(&player->sprite, &player->physics.position);
    UpdateAnimation(&player->animation, GetFrameTime());
    UpdateSpriteSourceRec(&player->sprite, &(Vector2){player->sprite.frameSize.x, player->sprite.frameSize.x * player->animation.currentFrame});
}

#endif // PLAYER_H
