#ifndef PLAYER_H
#define PLAYER_H

#include <sprite.h>
#include <animation.h>
#include <physics.h>
#include <input.h>
#include <asset.h>

#include "inventar.h"

typedef enum
{
	START_SHIP,
	PLAYER_TEX_COUNT
} playerTextureID;

const TextureAsset textureAssets[PLAYER_TEX_COUNT] = {
    {"assets/start_ship.png", 16.0f, 16.0f, 0.0f}
};



typedef enum {
	ANCHOR,
	SLOW_AHEAD,
	FAST_AHEAD,
	SPEED_COUNT
} playerSpeedID;

float playerSpeeds[SPEED_COUNT] = {
	0.0f,
	5.0f,
	10.0f
};


typedef struct
{
    Sprite sprite;
    Animation animation;
    Physics physics;
	float rotation;
} Player;

Player CreatePlayer(void)
{

	TextureAsset startShipAsset = textureAssets[START_SHIP];
	
	Texture2D texture = LoadTexture(startShipAsset.path);
	float frameWidth = startShipAsset.frameWidth;
	float rotation = startShipAsset.rotation;
	

	Sprite playerSprite  = {
            .texture = texture,
            .frameSize = {frameWidth, frameWidth},
            .sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
            .destRec = {0.0f, 0.0f, frameWidth, frameWidth},
            .origin = {frameWidth / 2, frameWidth / 2},
            .rotation = rotation,
            .color = WHITE
	};

	Animation playerAnimation = {
		.state = 1, 
		.currentFrame = 0, 
		.maxFrame = 3, 
		.framesCounter = 0, 
		.framesSpeed = 0.0f, 
		.animTimer = 0.0f
	};

	Physics playerPhysics = {
		.position = (Vector2){0.0f,0.0f}, 
		.direction = (Vector2){0.0f, 0.0f}, 
		.speed = playerSpeeds[ANCHOR]
	};

	
    return (Player){
        .sprite = playerSprite,
		.animation = playerAnimation,
        .physics = playerPhysics,
		.rotation = rotation
	};
}

void UpdatePlayer(Player *player)
{



	if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
		if(player->physics.speed < playerSpeeds[FAST_AHEAD]){
			if(player->physics.speed < playerSpeeds[SLOW_AHEAD]){
				player->physics.speed = playerSpeeds[SLOW_AHEAD];
				player->sprite.sourceRec.x = 16.0f * 1;
			}
			else {
				player->physics.speed = playerSpeeds[FAST_AHEAD];
				player->sprite.sourceRec.x = 16.0f * 2;	
			}
		}
	}

	if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
		if(player->physics.speed > playerSpeeds[ANCHOR]){
			if(player->physics.speed > playerSpeeds[SLOW_AHEAD]){
				player->physics.speed = playerSpeeds[SLOW_AHEAD];
				player->sprite.sourceRec.x = 16.0f * 1;
			}
			else {
				player->physics.speed = playerSpeeds[ANCHOR];
				player->sprite.sourceRec.x = 16.0f * 0;

			}
		}
	}


	float rotationSpeed = 100.0f;

	if (player->physics.speed > playerSpeeds[ANCHOR]){

		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
			player->rotation -= rotationSpeed * GetFrameTime();
		}

		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
			player->rotation += rotationSpeed * GetFrameTime();
		}
	}

	player->sprite.rotation = player->rotation;

	float rad = (player->rotation - 90.0f) * (PI / 180.0f);
	Vector2 dir = { cosf(rad), sinf(rad) };


    UpdatePhysics(&player->physics, dir);
    UpdateSpriteDestRec(&player->sprite, &player->physics.position);
    //UpdateAnimation(&player->animation, GetFrameTime());
    //UpdateSpriteSourceRec(&player->sprite, &(Vector2){player->sprite.frameSize.x * player->animation.currentFrame, player->sprite.frameSize.y * player->animation.state});
}

void RenderPlayer(Player *player){
	RenderSprite(&player->sprite);
}

#endif // PLAYER_H
