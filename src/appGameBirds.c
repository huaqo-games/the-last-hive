#include "appTypes.h"

const TextureAsset birdsTextureAssets[BIRDS_TEX_COUNT] = {
	{"assets/birds.png", 16.0f, 16.0f, 45.0f}
};

Birds CreateBirds(void){
	TextureAsset flyingAsset = birdsTextureAssets[FLYING];
	Texture2D texture = LoadTexture(flyingAsset.path);
	float frameWidth = flyingAsset.frameWidth;
	float rotation = flyingAsset.rotation;
	
	Sprite birdSprite = {
		.texture = texture,
		.frameSize = {frameWidth, frameWidth},
		.sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
		.destRec = {GetScreenWidth()/2, 0.0f, frameWidth, frameWidth},
		.origin = {frameWidth / 2, frameWidth / 2},
		.rotation = rotation,
		.color = WHITE
	};

	Animation birdsAnimation = {
		.state = 1,
		.currentFrame = 0,
		.maxFrame = 2,
		.framesCounter = 0,
		.framesSpeed = 2.0f,
		.animTimer = 0.0f
	};

	Physics birdsPhysics = {
    .position = (Vector2){-100.0f, 0.0f},
    .direction = (Vector2){0.0f, 0.0f},
    .speed = 10.0f
	};

  return (Birds){
    .sprite = birdSprite,
    .animation = birdsAnimation,
    .physics = birdsPhysics
  };
	
}

void UpdateBirds(Birds *birds){
  
  UpdatePhysics(&birds->physics, (Vector2){1.0f,0.0f});
  UpdateSpriteDestRec(&birds->sprite, &birds->physics.position);
  UpdateAnimation(&birds->animation, GetFrameTime());
  UpdateSpriteSourceRec(&birds->sprite, &(Vector2){birds->sprite.frameSize.x * birds->animation.currentFrame, birds->sprite.frameSize.y});
}

void RenderBirds(Birds *birds){
  RenderSprite(&birds->sprite);
}

