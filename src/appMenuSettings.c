#include "appTypes.h"

void InitMenuSettings(MenuSettings *s)
{
	int windowWidth = GetScreenWidth();
	int windowHeight = GetScreenHeight();
	Vector2 windowCenter = {windowWidth / 2, windowHeight / 2};

	Vector2 standardButtonDimensions = {100, 50};
	int standardSpacing = standardButtonDimensions.y / 2;

	Vector2 button1Pos = {windowCenter.x, windowCenter.y};
	Vector2 button2Pos = {windowCenter.x, windowCenter.y + standardButtonDimensions.y + standardSpacing};

	s->showFPS = initButton("showFPS", standardButtonDimensions, button1Pos);
	s->soundtrackOn = initButton("soundtrackOn", standardButtonDimensions, button2Pos);
}

void UpdateMenuSettings(MenuSettings *s, MenuView *menuView,Flags *flags)
{
	ShowCursor();

	if(isButtonClicked(&s->showFPS)){
		flags->showFPS = !flags->showFPS;
	}

	if(isButtonClicked(&s->soundtrackOn)){
		flags->soundtrackOn = !flags->soundtrackOn;
	}

	if (IsKeyPressed(KEY_ESCAPE)){
		*menuView = MAIN;
	}

	
}

void RenderMenuSettings(MenuSettings *s, Flags *flags)
{
	BeginDrawing();
	ClearBackground(BLACK);

	renderButton(&s->showFPS);

	if (flags->showFPS){
		DrawFPS(10,10);
	}

	renderButton(&s->soundtrackOn);

	EndDrawing();
	
}

void ClenupMenuSettings(MenuSettings *s){

}

