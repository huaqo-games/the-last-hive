#include "engine.h"

Camera2D* GetCamera(void){
	static Camera2D camera;
	return &camera;
}

Rectangle GetCameraRectangle(void)
{
	Camera2D *camera = GetCamera();
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();
	
    float viewWidth = 0.0f;
	float viewHeight = 0.0f;
	float viewX = 0.0f;
	float viewY = 0.0f;
	printf("\n CameraZoom: %f \n", camera->zoom);
	if (camera->zoom < 0.5f)
	{	
		viewWidth = screenWidth;
		viewHeight = screenHeight;

		viewX = camera->target.x - camera->offset.x;
		viewY = camera->target.y - camera->offset.y;
	} else 
	{
		viewWidth = screenWidth / camera->zoom;
		viewHeight = screenHeight / camera->zoom;

		viewX = camera->target.x - (camera->offset.x / camera->zoom);
		viewY = camera->target.y - (camera->offset.y / camera->zoom);
	}
	return (Rectangle){
		.x = viewX,
		.y = viewY,
		.width = viewWidth,
		.height = viewHeight
	};
}

void CreateCamera(Vector2 playerPosition, float initZoom){
	Camera2D* camera = GetCamera();
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    *camera = (Camera2D){
        .offset = (Vector2){windowWidth / 2.0f, windowHeight / 2.0f},
        .target = playerPosition,
        .rotation = 0.0f,
        .zoom = initZoom
    };
}

void UpdateCameraTarget(Vector2 *position, const float smoothness){
	Camera2D* camera = GetCamera();
    camera->target = Vector2Lerp(camera->target, *position, smoothness * GetFrameTime());
}

void UpdateCameraZoom(const float *scaleFactor, const float *minZoom, const float *maxZoom){
	Camera2D *camera = GetCamera();
    float targetZoom = Clamp(camera->zoom * *scaleFactor, *minZoom, *maxZoom);
    camera->zoom = Lerp(camera->zoom, targetZoom, 0.1f);
}

void UpdateCamera2D(Vector2* position, Mouse* mouse){
    UpdateCameraTarget(position, 5.0f);
    UpdateCameraZoom(&mouse->scaleFactor, &mouse->minZoom, &mouse->maxZoom);
}

