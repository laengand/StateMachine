#include "stdafx.h"
#include <iostream>
#include "SpecificFSM.h"
#include <Windows.h>

using namespace std;
using namespace Gadgets;
void SpecificFSM::ThreadFunction(SpecificFSM *specificFSM)
{
  while (!specificFSM->IsThreadStopped())
  {
    Sleep(1000);
    GenericState::event_t event;
    event.signal = SpecificFSM::eventSignal_t::EVENTSIGNAL_TIMEOUT;
    specificFSM->PostQueue(event);
  }
}

GenericState::event_t SpecificFSM::PeekQueue(void)
{
  return eventQueue->front();
}

void SpecificFSM::PopQueue(void)
{
  mtx.lock();
  QueuedFSM::PopQueue();
  mtx.unlock();
}

void SpecificFSM::PostQueue(GenericState::event_t event)
{
  mtx.lock();
  QueuedFSM::PostQueue(event);
  mtx.unlock();
}

SpecificFSM::SpecificFSM()
{
  stateA = new StateA();
  stateB = new StateB();
  stateC = new StateC();
  stateIdle = new StateIdle();
  stateA->SetTransistionStates(stateB, stateC, stateIdle);
  stateB->SetTransistionStates(stateC, stateIdle);
  stateC->SetTransistionStates(stateA, stateIdle);
  stateIdle->SetTransistionStates(stateA, stateB, stateC);
  stopThread = false;
  timeoutThread = new thread(&SpecificFSM::ThreadFunction, this);
  GoToState(stateA);
}

SpecificFSM::~SpecificFSM()
{
  stopThread = true;
  timeoutThread->join();

  delete stateA;
  delete stateB;
  delete stateC;
  delete stateIdle;
  delete timeoutThread;
}

// ================= StateA ================= 
SpecificFSM::StateA::StateA()
{
  EntryEnable(true);
  ExitEnable(true);
}

SpecificFSM::StateA::~StateA()
{
}

void SpecificFSM::StateA::OnEntry()
{
  cout << "StateA::OnEntry" << endl;
}

bool SpecificFSM::StateA::Update(FSM *fsm, event_t * event)
{
  cout << "StateA::Update" << endl;

  switch (event->signal)
  {
  case EVENTSIGNAL_TIMEOUT:
  {
    updateCnt++;
    if (updateCnt == 5)
    {
      cout << "   StateA -> StateB" << endl;
      fsm->GoToState(stateB);
    }
    else if (updateCnt == 15)
    {
      cout << "   StateA -> StateC" << endl;
      updateCnt = 0;
      fsm->GoToState(stateC);
    }
    break;
  }
  case EVENTSIGNAL_STOP:
    fsm->GoToState(stateIdle);
    break;
  default:
    cout << "   StateA Error" << endl;
    break;
  }
  return true;
}

void SpecificFSM::StateA::OnExit()
{
  cout << "StateA::OnExit" << endl;
}
void SpecificFSM::StateA::SetTransistionStates(StateB *stateB, StateC *stateC, StateIdle *stateIdle)
{
  this->stateB = stateB;
  this->stateC = stateC;
  this->stateIdle = stateIdle;
}
// ================= StateB ================= 
SpecificFSM::StateB::StateB()
{
  EntryEnable(true);
  ExitEnable(true);
}

SpecificFSM::StateB::~StateB()
{
}

void SpecificFSM::StateB::OnEntry()
{
  cout << "StateB::OnEntry" << endl;
}

bool SpecificFSM::StateB::Update(FSM *fsm, event_t *event)
{
  cout << "StateB::Update" << endl;

  switch (event->signal)
  {
  case EVENTSIGNAL_TIMEOUT:
    updateCnt++;
    if (updateCnt == 5)
    {
      cout << "   StateB -> StateC" << endl;
      fsm->GoToState(stateC);
    }
    break;
  case EVENTSIGNAL_STOP:
    fsm->GoToState(stateIdle);
    break;
  default:
    cout << "   StateB Error" << endl;
    break;
  }
  return true;
}

void SpecificFSM::StateB::OnExit()
{
  updateCnt = 0;
  cout << "StateB::OnExit" << endl;
}

void SpecificFSM::StateB::SetTransistionStates(StateC *stateC, StateIdle *stateIdle)
{
  this->stateC = stateC;
  this->stateIdle = stateIdle;
}

// ================= StateC ================= 
SpecificFSM::StateC::StateC()
{
  ExitEnable(true);
}

SpecificFSM::StateC::~StateC()
{
}

bool SpecificFSM::StateC::Update(FSM * fsm, event_t * event)
{
  cout << "StateC::Update" << endl;

  switch (event->signal)
  {
  case EVENTSIGNAL_TIMEOUT:
  {
    updateCnt++;
    if (updateCnt == 5)
    {
      cout << "   StateC -> StateA" << endl;
      fsm->GoToState(stateA);
    }
  }
  break;
  case EVENTSIGNAL_STOP:
    fsm->GoToState(stateIdle);
    break;
  default:
    cout << "   StateC Error" << endl;
    break;
  }
  return true;
}
void SpecificFSM::StateC::OnExit()
{
  updateCnt = 0;
  cout << "StateC::OnExit" << endl;
}
void SpecificFSM::StateC::SetTransistionStates(StateA * stateA, StateIdle *stateIdle)
{
  this->stateA = stateA;
  this->stateIdle = stateIdle;
}

// ================= StateIdle ================= 
SpecificFSM::StateIdle::StateIdle()
{
  EntryEnable(true);
  ExitEnable(true);
}

SpecificFSM::StateIdle::~StateIdle()
{
}

bool SpecificFSM::StateIdle::Update(FSM * fsm, event_t * event)
{
  cout << "StateIdle::Update" << endl;
  updateCnt++;
  switch (event->signal)
  {

  case EVENTSIGNAL_TIMEOUT:
  case EVENTSIGNAL_STOP:
    break;
  case EVENTSIGNAL_STATEA:
    fsm->GoToState(stateA);
    break;
  case EVENTSIGNAL_STATEB:
    fsm->GoToState(stateB);
    break;
  case EVENTSIGNAL_STATEC:
    fsm->GoToState(stateC);
    break;
  default:
    cout << "   StateIdle Error" << endl;
    break;
  }
  return true;
}

void SpecificFSM::StateIdle::SetTransistionStates(StateA * stateA, StateB *stateB, StateC *stateC)
{
  this->stateA = stateA;
  this->stateB = stateB;
  this->stateC = stateC;
}
