#ifndef ENGINE_H
#define ENGINE_H

#include <raylib.h>
#include <raymath.h>
#include <raygui.h>
#include <rini.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	Texture2D texture;
	Rectangle sourceRec;
	Rectangle destRec;
	Vector2 frameSize;
	Vector2 origin;
	float rotation;
	Color color;
} Sprite;

typedef struct {   
    int state;
    int currentFrame;       
    int maxFrame;           
    int framesCounter;      
    int framesSpeed;        
    float animTimer;  
} Animation;

typedef struct {
    void** elements;
    unsigned int count;
    unsigned int capacity;
} Array;

typedef struct {
    const char* path;
    float frameWidth;
    float frameHeight;
    float rotation;
} TextureAsset;

typedef struct {
    const char* path;
} ShaderAsset;

typedef struct {
    const char* path;
} SoundtrackAsset;

typedef struct {
    const char* path;
} SoundAsset;

typedef struct {
    const TextureAsset *textureAssets;
    const ShaderAsset *shaderAssets;
    const SoundtrackAsset *soundtrackAssets;
    const SoundAsset *soundAssets;
} Assets;

typedef struct {
    char *path;
    rini_config rini;
} Config;

typedef enum {
    NOT_CLICKED,
    HOVER,
    CLICKED
} ButtonState;

typedef struct 
{
    Sprite sprite;
    Vector2 notClicked;
    Vector2 hover;
    Vector2 clicked;
    bool isHovered;
    bool isClicked;
} ImageButton;

typedef struct
{
    Sprite sprite;
} ImageElement;

typedef struct
{
    Rectangle rec;
    char *text;
} Button;

typedef struct {
    Vector2 screenPosition;
    Vector2 worldPosition;
    float zoomSpeed;
    float minZoom;
    float maxZoom;
    float scaleFactor;
    float wheelMove;
    bool leftButton;
    bool rightButton;
    Texture2D cursorTexture;
} Mouse;

typedef struct {
    Sprite sprite;
    Vector2 position;
} Object;

typedef struct {
    Object *data;
    const Object *prototype;
    size_t count;
} ObjectArray;

typedef struct
{
    Vector2 position;
    Vector2 direction;
    Vector2 velocity;
    float speed;
} Physics;

typedef struct {
    Shader shader;
    int resolutionLoc;
    int strengthLoc;
    float strength;
} PostProcessing;

typedef struct {
    Music music;
    bool playing;
	bool paused;
} Soundtrack;

typedef struct {
    Vector2 *data;
    size_t count;
} Vector2Array;

typedef struct {
    int width;
    int height;
    const char* title;
} Window;

void UpdateAnimation(Animation *animation, float deltaTime);

Array* CreateArray(unsigned int initCapacity);
int AddElementToArray(Array* array, void* element);
int RemoveElementFromArray(Array* array, unsigned int index);
void* GetRandomElementFromArray(Array* array);
void UpdateArray(Array* array, void (*updateFunc)(void*));
void RenderArray(Array* array, void (*renderFunc)(void*));
void FreeArray(Array** array);

Camera2D* GetCamera(void);
Rectangle GetCameraRectangle(void);
void CreateCamera(Vector2 playerPosition, float initZoom);
void UpdateCameraTarget(Vector2 *position, const float smoothness);
void UpdateCameraZoom(const float *scaleFactor, const float *minZoom, const float *maxZoom);
void UpdateCamera2D(Vector2* position, Mouse* mouse);

void InitConfig(Config *config, const char* path);
int GetConfigInt(Config *config, const char *key);
int GetConfigIntOrDefault(Config *config, const char *key, int default_value);
const char* GetConfigString(Config *config, const char *key);
const char* GetConfigStringOrDefault(Config *config, const char *key, const char *default_value);
const char* GetConfigDescription(Config *config, const char *key);
int SetConfigInt(Config *config, const char *key, int value, const char *desc);
int SetConfigString(Config *config, const char *key, const char *text, const char *desc);
int SetConfigDescription(Config *config, const char *key, const char *desc);
int AddCommentLine(Config *config, const char *comment);
void SaveConfig(Config *config);
void CleanUpConfig(Config *config);

void InitFont(Font *font, const char* path);
void CleanupFont(Font *font);

ImageButton CreateImageButton(ButtonState state, Texture2D *texture, const TextureAsset *asset, Vector2 *source, Vector2 *clicked, Vector2 *hover, Rectangle *destRec);
ImageElement CreateImageElement(Texture2D *texture, const TextureAsset *asset, Vector2 *source, Rectangle *destRec);
int isImageButtonClicked(ImageButton *b, Sound soundHover, Sound soundClick);
void renderImageButton(ImageButton *b);
void renderImageElement(ImageElement *e);

Button initButton(char *text, Vector2 dimensions, Vector2 position);
int isButtonClicked(Button *b);
void renderButton(Button *b);

Mouse CreateMouse(float zoomSpeed, float minZoom, float maxZoom, Texture2D *texture);
void UpdateMouseScreen(Mouse *mouse);
void UpdateMouse(Mouse *mouse);
Vector2 GetDirectionVector(void);

ObjectArray CreateObjectArray(const Object *prototype, const size_t count);
Object* GetRandomObject(ObjectArray *objects);
void AddObjectToArray(ObjectArray *objects, const Object *prototype, Vector2 position);
void SetPositionForObjectArray(ObjectArray *objects, const Vector2Array *positions);
void SetRandomPositionForObjectArray(ObjectArray *objects, const Rectangle bounds);
void SwapAndPopObjectsArrayOnRecCollision(ObjectArray *objects, const Rectangle rec);
void SwapAndPopObjectsArrayOnPointCollision(ObjectArray *objects, const Vector2 point);
void RenderObjectArray(const ObjectArray *objects);

Vector2 GetDirectionBetweenTwoVectors(Vector2 vec1, Vector2 vec2);
float GetDistanceBetweenTwoVectors(Vector2 vec1, Vector2 vec2);
void UpdatePhysicsDirection(Vector2 *direction, Vector2 vector);
void UpdatePhysicsVelocity(Vector2 *velocity, Vector2 *direction, float *speed);
void UpdatePhysicsPosition(Vector2 *position, Vector2 *velocity);
void UpdatePhysicsSpeed(float *speed, float *newSpeed);
void UpdatePhysics(Physics *physics, Vector2 direction);

PostProcessing CreatePostFX(const char* shaderPath);
void UpdatePostFX(PostProcessing *postFX);
void RenderPostFX(PostProcessing *postFX, RenderTexture2D *target);
void UnloadPostFX(PostProcessing *postFX);

Soundtrack LoadSoundtrack(const char* musicPath);
void UpdateSoundtrack(Soundtrack *soundtrack, bool playing);

void UpdateSpriteSourceRec(Sprite *sprite, const Vector2 *vector);
void UpdateSpriteDestRec(Sprite *sprite, const Vector2 *vector);
void UpdateSpriteRotation(Sprite *sprite, float rotation);
void RenderSprite(const Sprite *sprite);
void PrintSprite(const Sprite *sprite);

bool IsVectorZero(Vector2 v);
Vector2 GetRandomVector(const Rectangle bounds);
Vector2 RotationToVector2(float rotation);
float Vector2ToRotation(Vector2 vec);

Vector2 GetPositionInsideRectangle(Rectangle rec);
Vector2 GetPositionOutsideRectangle(Rectangle rec, int min, int max);

#endif //ENGINE_H

