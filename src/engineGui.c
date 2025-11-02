#define RAYGUI_IMPLEMENTATION

#include "engine.h"

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

