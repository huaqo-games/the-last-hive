#ifndef PLAYER_H
#define PLAYER_H

#include <sprite.h>
#include <animation.h>
#include <physics.h>
#include <input.h>

#include "inventar.h"

typedef enum
{
    IDLE,
    WALKING,
    USING_TOOL
} PlayerState;

typedef enum
{
    NO_TOOL,
    HOE,
    AXT,
    CAN
} SelectedTool;

typedef enum
{
    IDLE_DOWN,
    IDLE_UP,
    IDLE_LEFT,
    IDLE_RIGHT,
    WALKING_DOWN,
    WALKING_UP,
    WALKING_LEFT,
    WALKING_RIGHT,
    HOE_DOWN,
    HOE_UP,
    HOE_RIGHT,
    HOE_LEFT,
    AXT_DOWN,
    AXT_UP,
    AXT_RIGHT,
    AXT_LEFT,
    CAN_DOWN,
    CAN_UP,
    CAN_RIGHT,
    CAN_LEFT,
} PlayerAnimationState;

typedef struct
{
    SelectedTool selectedTool;
    Sprite sprite;
    Animation animation;
    Physics physics;
    Inventar inventar;
} Player;

Player CreatePlayer(PlayerAnimationState animState, SelectedTool selectedTool, Texture2D texture, float frameWidth, int maxFrame, int framesSpeed, Vector2 startPosition, float rotation, float speed)
{
    return (Player){
        .selectedTool = selectedTool,
        .sprite = {
            .texture = texture,
            .frameSize = {frameWidth, frameWidth},
            .sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
            .destRec = {0.0f, 0.0f, frameWidth, frameWidth},
            .origin = {frameWidth / 2, frameWidth / 2},
            .rotation = rotation,
            .color = WHITE},
        .animation = {.state = animState, .currentFrame = 0, .maxFrame = maxFrame, .framesCounter = 0, .framesSpeed = framesSpeed, .animTimer = 0.0f},
        .physics = {.position = startPosition, .direction = (Vector2){0.0f, 0.0f}, .speed = speed},
        .inventar = {.seedCount = 6}};
}

void UpdatePlayerAnimationState(int *state, SelectedTool *selectedTool, Vector2 *dir)
{

    if (IsKeyPressed(KEY_ZERO))
    {
        *selectedTool = NO_TOOL;
    }

    if (IsKeyPressed(KEY_ONE))
    {
        *selectedTool = HOE;
    }

    if (IsKeyPressed(KEY_TWO))
    {
        *selectedTool = AXT;
    }

    if (IsKeyPressed(KEY_THREE))
    {
        *selectedTool = CAN;
    }

    if (dir->x == 0 && dir->y == 0)
    {
        switch (*state)
        {
        case WALKING_DOWN:
            *state = IDLE_DOWN;
            break;
        case WALKING_UP:
            *state = IDLE_UP;
            break;
        case WALKING_LEFT:
            *state = IDLE_LEFT;
            break;
        case WALKING_RIGHT:
            *state = IDLE_RIGHT;
            break;
        default:
            break;
        }
    }
    else
    {
        if (dir->y == 1)
            *state = WALKING_DOWN;
        else if (dir->y == -1)
            *state = WALKING_UP;
        else if (dir->x == -1)
            *state = WALKING_LEFT;
        else if (dir->x == 1)
            *state = WALKING_RIGHT;
    }
}

void UpdatePlayer(Player *player)
{
    if (IsKeyPressed(KEY_SPACE) && player->inventar.seedCount > 0)
    {
        player->inventar.seedCount--;
    }
    Vector2 dir = GetDirectionVector();
    UpdatePlayerAnimationState(&player->animation.state, &player->selectedTool, &dir);
    UpdatePhysics(&player->physics, dir);
    UpdateSpriteDestRec(&player->sprite, &player->physics.position);
    UpdateAnimation(&player->animation, GetFrameTime());
    UpdateSpriteSourceRec(&player->sprite, &(Vector2){player->sprite.frameSize.x * player->animation.currentFrame, player->sprite.frameSize.y * player->animation.state});
}

#endif // PLAYER_H
