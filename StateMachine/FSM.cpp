#include "stdafx.h"
#include "FSM.h"
#include <iostream>

using namespace std;
FSM::FSM()
{
    
}

FSM::~FSM()
{
    
}

void FSM::GoToState(GenericState *state)
{
    if (currentState != NULL)
    {
        if (currentState->IsExitEnabled())
            currentState->OnExit();
    }
    currentState = state;
    if (currentState->IsEntryEnabled())
        currentState->OnEntry();
}

void FSM::Dispatch(GenericState::event_t *event)
{
  currentState->Update(this, event);
}

