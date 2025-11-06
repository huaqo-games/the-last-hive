#include "appTypes.h"




Vector2 GetPositionInsideRectangle(Rectangle rec)
{
	int randX =	GetRandomValue(rec.x, rec.width);
	int randY = GetRandomValue(rec.y, rec.height);
	Vector2 randVector = {randX, randY};
	return randVector;
}

Vector2 GetPositionOutsideRectangle(Rectangle rec, int min, int max)
{
    int side = GetRandomValue(0, 3);
    Vector2 pos = {0};

    switch (side)
    {
        case 0: // left
            pos.x = rec.x - GetRandomValue(min, max);
            pos.y = GetRandomValue((int)rec.y, (int)(rec.y + rec.height));
            break;

        case 1: // right
            pos.x = rec.x + rec.width + GetRandomValue(min, max);
            pos.y = GetRandomValue((int)rec.y, (int)(rec.y + rec.height));
            break;

        case 2: // top
            pos.x = GetRandomValue((int)rec.x, (int)(rec.x + rec.width));
            pos.y = rec.y - GetRandomValue(min, max);
            break;

        case 3: // bottom
            pos.x = GetRandomValue((int)rec.x, (int)(rec.x + rec.width));
            pos.y = rec.y + rec.height + GetRandomValue(min, max);
            break;
    }

    return pos;
}

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

	Rectangle cameraRec = GetCameraRectangle();
	printf("cameraRec: %f, %f, %f, %f", cameraRec.x, cameraRec.y, cameraRec.width, cameraRec.height);

	Physics birdsPhysics = {
    .position = GetPositionOutsideRectangle(cameraRec, 1, 100),
    .direction = (Vector2){0.0f, 0.0f},
    .speed = 5.0f
	};

  return (Birds){
    .sprite = birdSprite,
    .animation = birdsAnimation,
    .physics = birdsPhysics
  };
	
}
void UpdateBirds(Birds *birds){
	Camera2D *camera = GetCamera();
	Vector2 dir = {camera->target.x - birds->physics.position.x, camera->target.y - birds->physics.position.y};
	UpdatePhysics(&birds->physics, dir);
	printf("birdsPos: %f, %f", birds->physics.position.x, birds->physics.position.y);
	printf("cameraTarget: %f, %f",camera->target.x, camera->target.y );
	UpdateSpriteDestRec(&birds->sprite, &birds->physics.position);
	float rotation = Vector2ToRotation(dir);
	UpdateSpriteRotation(&birds->sprite, rotation + 45.0f);
	UpdateAnimation(&birds->animation, GetFrameTime());
	UpdateSpriteSourceRec(&birds->sprite, &(Vector2){birds->sprite.frameSize.x * birds->animation.currentFrame, birds->sprite.frameSize.y});
}

void RenderBirds(Birds *birds){
  RenderSprite(&birds->sprite);
}

