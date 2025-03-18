#ifndef GUI_H
#define GUI_H

#define RAYGUI_IMPLEMENTATION
#include "../../include/raygui.h"

typedef struct
{
    Rectangle rec;
    const char *text;
} Button;

void initButton(Button *b, const char *text, int buttonWidth, int buttonHeight, int buttonPosX, int buttonPosY)
{
    b->rec = (Rectangle){buttonPosX - buttonWidth / 2, buttonPosY - buttonHeight / 2, buttonWidth, buttonHeight};
    b->text = text;
}

int isButtonClicked(Button *b)
{
    return (CheckCollisionPointRec(GetMousePosition(), b->rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

void renderButton(Button *b)
{
    GuiButton(b->rec, b->text);
}

#endif // GUI_H
