#include <raylib.h>

typedef struct
{
    float x;
    float y;
    int count;
} SpriteSet;

int main()
{
    int screenWidth = 1280;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Father and Son");
    SetTargetFPS(60);

    // Initialize Tiles
    Texture2D tileTexture = LoadTexture("assets/tileset.png");
    Vector2 tileFrameSize = {16.0f, 16.0f};

    Rectangle tileSourceRec = { tileFrameSize.x * 11 + 11, tileFrameSize.y * 10 + 10, tileFrameSize.x, tileFrameSize.y};


    // Initialize Background 
    // Texture2D backTexture = LoadTexture("assets/map.png");
    // Vector2 backFrameSize = {639.0f, 271.0f};
    // Rectangle backSourceRec = {0.0f, 0.0f, backFrameSize.x, backFrameSize.y};
    // Rectangle backDestRec = {0.0f, 0.0f, backFrameSize.x, backFrameSize.y};
    // Vector2 backOrigin = {0.0f, 0.0f};

    // Initialize Character
    Texture2D characterTexture = LoadTexture("assets/character.png");
    Vector2 charFrameSize = {32.0f, 32.0f};

    SpriteSet idle = {0.0f, 0.0f, 2};
    SpriteSet walkingDown = {0.0f, 96.0f, 4};
    SpriteSet walkingRight = {0.0f, 128.0f, 4};
    SpriteSet walkingUp = {0.0f, 160.0f, 4};
    SpriteSet current = idle;

    Rectangle charSourceRec = {idle.x, idle.y, charFrameSize.x, charFrameSize.y};
    Vector2 charPosition = {0.0f, 0.0f};
    Vector2 charOrigin = {charFrameSize.x / 2.0f, charFrameSize.y / 2.0f};

    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 4;

    // Initialize Camera
    Camera2D camera = { 0 };
    camera.target = charPosition;
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 10.0f;

    while (!WindowShouldClose())
    {
        // Update Character
        if (IsKeyDown(KEY_RIGHT))
        {
            current = walkingRight;
            charSourceRec.width = charFrameSize.x;
            charPosition.x += 0.5f;
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            current = walkingRight;
            charSourceRec.width = -charFrameSize.x;
            charPosition.x -= 0.5f;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            current = walkingDown;
            charSourceRec.width = charFrameSize.x;
            charPosition.y += 0.5f;
        }
        else if (IsKeyDown(KEY_UP))
        {
            current = walkingUp;
            charSourceRec.width = charFrameSize.x;
            charPosition.y -= 0.5f;
        }
        else
        {
            current = idle;
            charSourceRec.width = charFrameSize.x;
        }

        framesCounter++;

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame >= current.count)
                currentFrame = 0;

            charSourceRec.x = current.x + currentFrame * charFrameSize.x;
            charSourceRec.y = current.y;
        }

        // Update Camera
        camera.target = charPosition;

        // Render
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera); // Activate 2D camera

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

        // Render Background
        // DrawTexturePro(backTexture, backSourceRec, backDestRec, backOrigin, 0.0f, WHITE);

        // Render Character
        Rectangle charDestRec = {charPosition.x, charPosition.y, charFrameSize.x, charFrameSize.y};
        DrawTexturePro(characterTexture, charSourceRec, charDestRec, charOrigin, 0.0f, WHITE);

        EndMode2D();
        
        // Render Debug

        EndDrawing();
    }

    // Unload Character
    UnloadTexture(characterTexture);
    UnloadTexture(tileTexture);
    // UnloadTexture(backTexture);

    CloseWindow();

    return 0;
}


/*
DrawRectangleLines(charDestRec.x, charDestRec.y, charFrameSize.x, charFrameSize.y, GREEN);
DrawRectangleLines(charPosition.x, charPosition.y, charFrameSize.x, charFrameSize.y, GREEN);
DrawRectangleLines(camera.offset.x, camera.offset.y, charFrameSize.x, charFrameSize.y, RED);
DrawRectangleLines(camera.target.x, camera.target.y, charFrameSize.x, charFrameSize.y, RED);
DrawText(TextFormat("charDestRec: %f, %f", charDestRec.x, charDestRec.y),10,10,20,GREEN);
DrawText(TextFormat("charSourceRec: %f, %f", charSourceRec.x, charSourceRec.y),10,30,20,GREEN);
DrawFPS(screenWidth - 30, 10);
*/