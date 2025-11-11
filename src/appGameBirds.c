#include "appTypes.h"
#include "engine.h"


const TextureAsset birdsTextureAssets[BIRDS_TEX_COUNT] = {
	{"assets/birds.png", 16.0f, 16.0f, 45.0f}
};

Birds CreateBirds(void){
	Birds birds = {.count = MAX_BIRDS};
	TextureAsset flyingAsset = birdsTextureAssets[FLYING];
	Texture2D texture = LoadTexture(flyingAsset.path);
	float frameWidth = flyingAsset.frameWidth;
	float rotation = flyingAsset.rotation;

	for (int i = 0; i < birds.count; i++)	
	{
		birds.sprite[i] = (Sprite){
			.texture = texture,
			.frameSize = {frameWidth, frameWidth},
			.sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
			.destRec = {GetScreenWidth()/2, 0.0f, frameWidth, frameWidth},
			.origin = {frameWidth / 2, frameWidth / 2},
			.rotation = rotation,
			.color = WHITE
		};

		birds.animation[i] = (Animation){
			.state = 1,
			.currentFrame = 0,
			.maxFrame = 2,
			.framesCounter = 0,
			.framesSpeed = 2.0f,
			.animTimer = 0.0f
		};

		Rectangle cameraRec = GetCameraRectangle();

		birds.physics[i] = (Physics){
		.position = GetPositionOutsideRectangle(cameraRec, 100, 1000),
		.direction = (Vector2){0.0f, 0.0f},
		.speed = 5.0f
		};

		birds.arrived[i] = true;
		birds.destPos[i] = (Vector2){0.0f, 0.0f};	

	}

	return birds;
}

void UpdateBirds(Birds *birds){
	Camera2D *camera = GetCamera();
	Rectangle cameraRec = GetCameraRectangle();

	for (int i = 0; i < birds->count; i++)
	{
		if(birds->arrived[i])
		{
			birds->destPos[i] = GetPositionOutsideRectangle(cameraRec, 100, 1000);
			birds->arrived[i] = false;
		}
		if(CheckCollisionPointCircle(birds->physics[i].position, birds->destPos[i], 10.0F))
		{
			birds->arrived[i] = true;
		}	
		if(GetDistanceBetweenTwoVectors(birds->physics[i].position, camera->target) > 1000){
			birds->physics[i].position = GetPositionOutsideRectangle(cameraRec, 100, 1000);
		}
		Vector2 dir = GetDirectionBetweenTwoVectors(birds->physics[i].position, birds->destPos[i]);
		UpdatePhysics(&birds->physics[i], dir);
		printf("birdsPos: %f, %f", birds->physics[i].position.x, birds->physics[i].position.y);
		printf("cameraTarget: %f, %f",camera->target.x, camera->target.y );
		UpdateSpriteDestRec(&birds->sprite[i], &birds->physics[i].position);
		float rotation = Vector2ToRotation(dir);
		UpdateSpriteRotation(&birds->sprite[i], rotation + 45.0f);
		UpdateAnimation(&birds->animation[i], GetFrameTime());
		UpdateSpriteSourceRec(&birds->sprite[i], &(Vector2){birds->sprite[i].frameSize.x * birds->animation[i].currentFrame, birds->sprite[i].frameSize.y});
	}
}

void RenderBirds(Birds *birds){

	for (int i = 0; i < birds->count; i++)
	{
		RenderSprite(&birds->sprite[i]);
	}

}

