#ifndef PLAYER_H
#define PLAYER_H
#include "../engine/sprite.h"
#include "../engine/animation.h"
#include "../engine/physics.h"
#include "../engine/input.h"

typedef enum {
    IDLE_UP,
    IDLE_LEFT,
    IDLE_DOWN,
    IDLE_RIGHT,
    WALKING_UP,
    WALKING_LEFT,
    WALKING_DOWN,
    WALKING_RIGHT
} PlayerState;

typedef struct {
    PlayerState state;
    Sprite sprite;
    Animation animation;
    Physics physics;
} Player;

Player CreatePlayer(Texture2D texture, float frameWidth, int maxFrame, int framesSpeed, Vector2 startPosition, float rotation, float speed){
    return (Player){
        .sprite = {
            .texture = texture,
            .frameSize = {frameWidth, frameWidth},
            .sourceRec = {0.0f,0.0f, frameWidth, frameWidth},
            .destRec = {0.0f, 0.0f, frameWidth, frameWidth},
            .origin = {frameWidth / 2, frameWidth / 2},
            .rotation = rotation,
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

void UpdateState(PlayerState *state) {
    Vector2 dir = GetDirectionVector();

    if (dir.x == 0 && dir.y == 0) {
        switch (*state) {
            case WALKING_DOWN:  *state = IDLE_DOWN; break;
            case WALKING_UP:    *state = IDLE_UP; break;
            case WALKING_RIGHT: *state = IDLE_RIGHT; break;
            case WALKING_LEFT:  *state = IDLE_LEFT; break;
            default: break;
        }
    } else {
        if (dir.y == -1)      *state = WALKING_DOWN;
        else if (dir.y == 1)  *state = WALKING_UP;
        else if (dir.x == 1)  *state = WALKING_RIGHT;
        else if (dir.x == -1) *state = WALKING_LEFT;
    }
}



void UpdatePlayer(Player* player){
    UpdatePhysics(&player->physics, GetDirectionVector());
    UpdateState(&player->state);
    // UpdateSpriteRotation(&player->sprite, &player->physics.direction);
    UpdateSpriteDestRec(&player->sprite, &player->physics.position);
    UpdateAnimation(&player->animation, GetFrameTime());
    UpdateSpriteSourceRec(&player->sprite, &(Vector2){player->sprite.frameSize.x * player->state, player->sprite.frameSize.y * player->animation.currentFrame});
}

#endif // PLAYER_H
