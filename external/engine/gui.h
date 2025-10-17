#ifndef GUI_H
#define GUI_H

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

typedef struct
{
    Rectangle rec;
    char *text;
} Button;

Button initButton(char *text, Vector2 dimensions, Vector2 position)
{
	Button b;

    b.rec = (Rectangle){position.x - dimensions.x / 2, position.y - dimensions.y / 2, dimensions.x, dimensions.y};
    b.text = text;
	return b;
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
