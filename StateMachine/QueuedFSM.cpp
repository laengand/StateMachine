#include "stdafx.h"
#include "QueuedFSM.h"
using namespace std;

QueuedFSM::QueuedFSM()
{
  eventQueue = new queue<GenericState::event_t>;
}


QueuedFSM::~QueuedFSM()
{
  delete eventQueue;
}

GenericState::event_t QueuedFSM::PeekQueue(void)
{
  return eventQueue->front();
}

void QueuedFSM::PopQueue(void)
{
  eventQueue->pop();
}

void QueuedFSM::PostToQueue(GenericState::event_t event)
{
  eventQueue->push(event);
}

void QueuedFSM::Process()
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