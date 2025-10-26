#ifndef GAMEUI
#define GAMEUI

#include "flags.h"

void RenderGameUI(bool showFPS){	
	BeginDrawing();
	ClearBackground(BLACK);

	if (showFPS)
	{
		DrawFPS(10, 10);
	}

	EndDrawing();
}

#endif //GAMEUI

