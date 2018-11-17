#include "stdafx.h"
#include "FSM.h"
using namespace std;

FSM::FSM()
{
    eventQueue = new queue<GenericState::event_t>;
}


FSM::~FSM()
{
    delete eventQueue;
}

void FSM::GoToState(GenericState *state)
{
    if (currentState != NULL)
    {
        if (currentState->onExit != NULL)
            currentState->onExit(currentState);
    }
    currentState = state;
    if (currentState->onEntry != NULL)
        currentState->onEntry(currentState);
}
void FSM::Process()
{
    if (eventQueue->empty())
        return;

    GenericState::event_t evt = eventQueue->front();
    if (currentState != NULL)
        if (currentState->Update(this, &evt))
            eventQueue->pop();
}

void FSM::PostToQueue(GenericState::event_t event)
{
    eventQueue->push(event);
}