#ifndef STATE_H
#define STATE_H

#include "view.h"

typedef struct {
    View currentView;
    bool running;
    bool gameStarted;
} State;

#endif // STATE_H
