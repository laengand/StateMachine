#pragma once
#include "GenericState.h"
namespace Gadgets
{
  class FSM
  {
  protected:
    GenericState *currentState;
  public:
    FSM();
    ~FSM();
    virtual void Dispatch(GenericState::event_t *event);
    virtual void GoToState(GenericState *state);

  };
}