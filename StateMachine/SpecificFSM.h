#pragma once

#include <thread>
#include <mutex>
#include "QueuedFSM.h"
class SpecificFSM : public QueuedFSM
{
  static void ThreadFunction(SpecificFSM *specificFSM);
  std::thread *timeoutThread;
  bool stopThread;
  bool IsThreadStopped() { return stopThread; };
  std::mutex mtx;
  class StateA;
  class StateB;
  class StateC;
  class StateIdle;

  class StateA : public GenericState
  {
    StateB *stateB;
    StateC *stateC;
    StateIdle *stateIdle;
    int updateCnt;
  public:
    StateA();
    ~StateA();
    void OnEntry();
    bool Update(FSM *fsm, event_t * event);
    void OnExit();
    void SetTransistionStates(StateB *stateB, StateC *stateC, StateIdle *stateIdle);
  };

  class StateB : public GenericState
  {
    StateC *stateC;
    StateIdle *stateIdle;
    int updateCnt;
  public:
    StateB();
    ~StateB();
    void OnEntry();
    bool Update(FSM *fsm, event_t * event);
    void OnExit();
    void SetTransistionStates(StateC *stateC, StateIdle *stateIdle);
  };
  class StateC : public GenericState
  {
    StateA *stateA;
    StateIdle *stateIdle;
    int updateCnt;
  public:
    StateC();
    ~StateC();
    bool Update(FSM *fsm, event_t * event);
    void OnExit();
    void SetTransistionStates(StateA *stateA, StateIdle *stateIdle);
  };

  class StateIdle : public GenericState
  {
    StateA *stateA;
    StateB *stateB;
    StateC *stateC;
    int updateCnt;
  public:
    StateIdle();
    ~StateIdle();
    bool Update(FSM *fsm, event_t * event);
    void SetTransistionStates(StateA *stateA, StateB *stateB, StateC *stateC);
  };


  StateA *stateA;
  StateB *stateB;
  StateC *stateC;
  StateIdle *stateIdle;
public:

  typedef enum e_eventSignal
  {
    EVENTSIGNAL_TIMEOUT = 0,
    EVENTSIGNAL_STATEA = 1,
    EVENTSIGNAL_STATEB = 2,
    EVENTSIGNAL_STATEC = 3,
    EVENTSIGNAL_STOP = 4,
  }eventSignal_t;
  SpecificFSM();
  ~SpecificFSM();
  GenericState::event_t PeekQueue(void);
  void PopQueue(void);
  void PostToQueue(GenericState::event_t event);

};

