#include <raylib.h>
#include "app.h"

int main(void)
{
    App app;
    ConfigApp(&app);
    InitWindow(app.window.width, app.window.height, app.window.title); 
    InitAudioDevice(); 
    InitApp(&app);
    UpdateApp(&app);
    CleanupApp(&app);
    CloseWindow();
    return 0;
}
