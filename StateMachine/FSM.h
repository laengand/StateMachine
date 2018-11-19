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
    virtual void Process();
    virtual GenericState::event_t PeekQueue(void);
    virtual void PopQueue(void);
    virtual void PostToQueue(GenericState::event_t event);
    virtual void GoToState(GenericState *state);

};

