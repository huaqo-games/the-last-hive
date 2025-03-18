#ifndef LOGO_H
#define LOGO_H

typedef struct {
    int frameCounter;
    int positionX;
    int positionY;
    int lettersCount;
    int topSideRecWidth;
    int leftSideRecHeight;
    int bottomSideRecWidth;
    int rightSideRecHeight;
    int state;
    float alpha;
} LogoState;

void InitLogo(LogoState *l) {
    SetTargetFPS(60);
    
    l->frameCounter = 0;
    l->positionX = GetScreenWidth() / 2 - 128;
    l->positionY = GetScreenHeight() / 2 - 128;
    l->lettersCount = 0;
    l->topSideRecWidth = 16;
    l->leftSideRecHeight = 16;
    l->bottomSideRecWidth = 16;
    l->rightSideRecHeight = 16;
    l->state = 0;
    l->alpha = 1.0f;
}

void UpdateLogo(LogoState *l, Screen *currentScreen) {
    l->frameCounter++;  // Increment the frame counter each frame

    if (l->state == 0) { // State 0: Small box blinking for 120 frames (2 seconds at 60 FPS)
        if (l->frameCounter >= 120) {
            l->state = 1;
            l->frameCounter = 0;  // Reset frame counter
        }
    } 
    else if (l->state == 1) { // State 1: Top and left bars growing
        l->topSideRecWidth += 4;
        l->leftSideRecHeight += 4;

        if (l->topSideRecWidth >= 256) {
            l->state = 2;
            l->frameCounter = 0;
        }
    } 
    else if (l->state == 2) { // State 2: Bottom and right bars growing
        l->bottomSideRecWidth += 4;
        l->rightSideRecHeight += 4;

        if (l->bottomSideRecWidth >= 256) {
            l->state = 3;
            l->frameCounter = 0;
        }
    } 
    else if (l->state == 3) { // State 3: Letters appearing
        if (l->frameCounter % 12 == 0) {  // Every 12 frames, one more letter appears
            l->lettersCount++;
        }

        if (l->lettersCount >= 10) { // Fade out animation
            l->alpha -= 0.02f;
            if (l->alpha <= 0.0f) {
                l->alpha = 0.0f;
                l->state = 4;
            }
        }
    } 
    else if (l->state == 4) {  // State 4: Transition to GAMEPLAY
        SetTargetFPS(0);
        *currentScreen = MENU;
    } 
}

void RenderLogo(const LogoState *l) {
    BeginDrawing();
        ClearBackground(RAYWHITE);

        if (l->state == 0) { // Small box blinking
            if ((l->frameCounter / 15) % 2 == 0) {  // Blink every 15 frames
                DrawRectangle(l->positionX, l->positionY, 16, 16, BLACK);
            }
        } 
        else if (l->state == 1) { // Top and left bars growing
            DrawRectangle(l->positionX, l->positionY, l->topSideRecWidth, 16, BLACK);
            DrawRectangle(l->positionX, l->positionY, 16, l->leftSideRecHeight, BLACK);
        } 
        else if (l->state == 2) { // Bottom and right bars growing
            DrawRectangle(l->positionX, l->positionY, l->topSideRecWidth, 16, BLACK);
            DrawRectangle(l->positionX, l->positionY, 16, l->leftSideRecHeight, BLACK);
            DrawRectangle(l->positionX + 240, l->positionY, 16, l->rightSideRecHeight, BLACK);
            DrawRectangle(l->positionX, l->positionY + 240, l->bottomSideRecWidth, 16, BLACK);
        } 
        else if (l->state == 3) { // Letters appearing
            DrawRectangle(l->positionX, l->positionY, l->topSideRecWidth, 16, Fade(BLACK, l->alpha));
            DrawRectangle(l->positionX, l->positionY + 16, 16, l->leftSideRecHeight - 32, Fade(BLACK, l->alpha));
            DrawRectangle(l->positionX + 240, l->positionY + 16, 16, l->rightSideRecHeight - 32, Fade(BLACK, l->alpha));
            DrawRectangle(l->positionX, l->positionY + 240, l->bottomSideRecWidth, 16, Fade(BLACK, l->alpha));
            DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, l->alpha));

            DrawText(TextSubtext("raylib", 0, l->lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, l->alpha));
        } 

    EndDrawing();
}

#endif // LOGO_H
