#include "stdafx.h"
#include "FSM.h"
#include <iostream>

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
        if (currentState->IsExitEnabled())
            currentState->OnExit();
    }
    currentState = state;
    if (currentState->IsEntryEnabled())
        currentState->OnEntry();
}
void FSM::Process()
{
    if (eventQueue->empty())
        return;

    GenericState::event_t evt = PeekQueue();
    if (currentState != NULL)
      if (currentState->Update(this, &evt))
      {
        PopQueue();
      }
}
GenericState::event_t FSM::PeekQueue(void)
{
  return eventQueue->front();
}
void FSM::PopQueue(void)
{
  eventQueue->pop();
}
void FSM::PostToQueue(GenericState::event_t event)
{
    eventQueue->push(event);
}