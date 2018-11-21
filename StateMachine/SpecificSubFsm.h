#pragma once
#include "FSM.h"
class SpecificSubFsm : public FSM
{
  class StateA : public GenericState
  {
  public:
    StateA();
    ~StateA();
    void OnEntry();
    bool Update(FSM *fsm, event_t * event);
    void OnExit();
  };
public:
  SpecificSubFsm();
  ~SpecificSubFsm();
};

