#pragma once
#include "GenericState.h"
class FSM
{
protected:
    GenericState *currentState;
public:
    FSM();
    ~FSM();
    void GoToState(GenericState *state);

};

