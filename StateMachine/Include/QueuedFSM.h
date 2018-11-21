#pragma once
#include <queue>
#include "FSM.h"
namespace Gadgets
{
  class QueuedFSM : public FSM
  {
  protected:
    std::queue<GenericState::event_t> *eventQueue;
  public:
    QueuedFSM();
    ~QueuedFSM();
    virtual void Process();
    virtual GenericState::event_t PeekQueue(void);
    virtual void PopQueue(void);
    virtual void PostQueue(GenericState::event_t event);
  };
}