#include "app.h"

int main(void)
{
    App app;
    ConfigApp(&app);
    InitApp(&app);
    UpdateApp(&app);
    CleanupApp(&app);
    return 0;
}
