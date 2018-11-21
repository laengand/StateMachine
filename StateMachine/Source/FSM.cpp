#include "FSM.h"

using namespace std;
using namespace Gadgets;
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

