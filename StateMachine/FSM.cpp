#include "stdafx.h"
#include "FSM.h"


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
        currentState->OnExit();
        currentState = state;
        currentState->OnEntry();
    }
}
