#pragma once
#include <queue>
#include "GenericState.h"

class FSM
{
protected:
    GenericState *currentState;
    std::queue<GenericState::event_t> *eventQueue;
public:
    FSM();
    ~FSM();
    void Process();
    void PostToQueue(GenericState::event_t event);
    void GoToState(GenericState *state);

};

