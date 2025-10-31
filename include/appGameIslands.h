#ifndef APPGAMEISLANDS_H
#define APPGAMEISLANDS_H

typedef struct {
	Sprite sprite;
	Animation animation;
	Physics physics;
} Islands;

typedef enum 
{
	ISLAND,
	ISLANDS_TEX_COUNT
} islandsTextureID;

const TextureAsset islandsTextureAssets[ISLANDS_TEX_COUNT] = {
	{"assets/island.png", 16.0f, 16.0f, 0.0f}
};

Islands CreateIslands(void){
	TextureAsset islandAsset = islandsTextureAssets[ISLAND];
	Texture2D texture = LoadTexture(islandAsset.path);
	float frameWidth = islandAsset.frameWidth;
	float rotation = islandAsset.rotation;
	
	Sprite islandSprite = {
		.texture = texture,
		.frameSize = {frameWidth, frameWidth},
		.sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
		.destRec = {GetScreenWidth()/2, 0.0f, frameWidth, frameWidth},
		.origin = {frameWidth / 2, frameWidth / 2},
		.rotation = rotation,
		.color = WHITE
	};

	Physics islandPhysics = {
    .position = (Vector2){-100.0f, 0.0f},
    .direction = (Vector2){0.0f, 0.0f},
    .speed = 10.0f
	};

  return (Islands){
    .sprite = islandSprite,
    .physics = islandPhysics
  };
	
}

void UpdateIslands(Islands *islands){
  
  UpdatePhysics(&islands->physics, (Vector2){0.0f,0.0f});
  UpdateSpriteDestRec(&islands->sprite, &islands->physics.position);
  UpdateAnimation(&islands->animation, GetFrameTime());
  UpdateSpriteSourceRec(&islands->sprite, &(Vector2){islands->sprite.frameSize.x * islands->animation.currentFrame, islands->sprite.frameSize.y});
}

void RenderIslands(Islands *islands){
  RenderSprite(&islands->sprite);
}

#endif // APPGAMEISLANDS_H

