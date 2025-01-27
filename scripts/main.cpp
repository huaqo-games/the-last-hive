#include <raylib.h>
#include <raymath.h>

Vector2 getDirection(){
    Vector2 direction = {0.0f, 0.0f};
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){ direction = Vector2Add(direction, {1.0f , 0.0f}); }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){ direction = Vector2Add(direction, {-1.0f, 0.0f}); }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){ direction = Vector2Add(direction, {0.0f, 1.0f}); }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){ direction = Vector2Add(direction, {0.0f, -1.0f}); }
    if (Vector2Length(direction) > 0.0f) { direction = Vector2Normalize(direction); }
    return direction;
}

int main()
{
    int screenWidth = 1280;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Lazy Bee");
    SetTargetFPS(60);

    // Init Audio
    InitAudioDevice();
    Music music = LoadMusicStream("assets/beez.mp3");
    PlayMusicStream(music);

    // Init Tiles
    Texture2D tileTexture = LoadTexture("assets/grass.png");
    Vector2 tileFrameSize = {16.0f, 16.0f};
    Rectangle tileSourceRec = { tileFrameSize.x, tileFrameSize.y, tileFrameSize.x, tileFrameSize.y};

    // Init Character
    Texture2D characterTexture = LoadTexture("assets/character_bee.png");
    Vector2 charFrameSize = {16.0f, 16.0f};
    Rectangle charSourceRec = {0.0f, 0.0f, charFrameSize.x, charFrameSize.y};
    Vector2 charPosition = {0.0f, 0.0f};
    Vector2 charOrigin = {charFrameSize.x / 2.0f, charFrameSize.y / 2.0f};
    float charRotation = 0.0f;

    // Init Character Animation
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 10;

    // Init Camera
    Camera2D camera = { 0 };
    camera.target = charPosition;
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 10.0f;

    // Init hive
    Texture2D hiveTexture = LoadTexture("assets/hive.png");
    Vector2 hiveFrameSize = {32.0f,32.0f};
    Rectangle hiveSourceRec = {0.0f, 0.0f, hiveFrameSize.x, hiveFrameSize.y};
    Vector2 hivePosition = {0.0f,0.0f};
    Rectangle hiveDestRec = {hivePosition.x, hivePosition.y, hiveFrameSize.x, hiveFrameSize.y};
    Vector2 hiveOrigin = {hiveFrameSize.x / 2.0f, hiveFrameSize.y / 2.0f};

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);


        // Update Char Movement
        Vector2 direction = getDirection();
        Vector2 targetPosition = Vector2Add(charPosition, Vector2Scale(direction, 100.0f * GetFrameTime())); 
        charPosition = {Lerp(charPosition.x, targetPosition.x, 0.3f),Lerp(charPosition.y, targetPosition.y, 0.3f)};

        // Update Char Rotation
        if (Vector2Length(direction) > 0.0f) {
            float targetRotation = atan2(direction.y, direction.x) * (180.0f / PI) + 90.0f;
            charRotation = Lerp(charRotation, targetRotation, 0.1f); 
        }

        // Update Char Animation
        framesCounter++;

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame >= 4)
                currentFrame = 0;
            charSourceRec.y = currentFrame * charFrameSize.y;
        }

        // Update Char Camera
        camera.target = charPosition;

        // Render
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);

        // Render Tiles
        float left = camera.target.x - (screenWidth / 2.0f / camera.zoom);
        float right = camera.target.x + (screenWidth / 2.0f / camera.zoom);
        float top = camera.target.y - (screenHeight / 2.0f / camera.zoom);
        float bottom = camera.target.y + (screenHeight / 2.0f / camera.zoom);

        int startX = (int)(left / tileFrameSize.x) - 1;
        int endX = (int)(right / tileFrameSize.x) + 1;
        int startY = (int)(top / tileFrameSize.y) - 1;
        int endY = (int)(bottom / tileFrameSize.y) + 1;

        for (int y = startY; y <= endY; y++)
        {
            for (int x = startX; x <= endX; x++)
            {
                Vector2 tilePosition = {x * tileFrameSize.x, y * tileFrameSize.y};
                Rectangle tileDestRec = {tilePosition.x, tilePosition.y, tileFrameSize.x, tileFrameSize.y};
                DrawTexturePro(tileTexture, tileSourceRec, tileDestRec, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
            }
        }

        // Render Hive
        DrawTexturePro(hiveTexture, hiveSourceRec, hiveDestRec, hiveOrigin, 0.0f, WHITE);

        // Render Character
        Rectangle charDestRec = {charPosition.x, charPosition.y, charFrameSize.x, charFrameSize.y};
        DrawTexturePro(characterTexture, charSourceRec, charDestRec, charOrigin, charRotation, WHITE);

        EndMode2D();
        EndDrawing();
    }

    // Unload Character
    UnloadTexture(characterTexture);
    UnloadTexture(tileTexture);
    UnloadMusicStream(music);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}