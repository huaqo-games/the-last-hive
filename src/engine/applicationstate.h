#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

typedef struct {
    Screen currentScreen;
    bool running;
    bool gameStarted;
    bool flagFPS;
} State;

#endif // APPLICATIONSTATE_H
