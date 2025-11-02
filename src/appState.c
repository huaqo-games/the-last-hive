#include "appTypes.h"

void OnEscapeChangeView(App *app, View view)
{	
	if (IsKeyPressed(KEY_ESCAPE))
	{
		app->state.currentView = view;
	}
}

void OnWindowClosedStoppApp(App *app)
{
    if (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        app->state.running = false;
    }
}
