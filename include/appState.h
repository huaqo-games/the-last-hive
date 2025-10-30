#ifndef APPSTATE_H
#define APPSTATE_H

typedef enum View {
    LOGO = 0,
    MENU = 1,
    GAMEPLAY = 2
} View;

typedef struct {
    View currentView;
    bool running;
    bool gameStarted;
} State;

#endif // APPSTATE_H
