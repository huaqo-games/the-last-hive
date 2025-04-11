#include <raylib.h>
#include "app.h"

int main(void)
{
    Application app;
    ConfigApp(&app);
    InitWindow(app.display.width, app.display.height, app.display.title); 
    InitAudioDevice(); 
    InitApp(&app);
    UpdateApp(&app);
    CleanupApp(&app);
    CloseWindow();
    return 0;
}
