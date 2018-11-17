#pragma once

#include <queue>
#include "FSM.h"
class SpecificFSM : FSM
{
    class StateA;
    class StateB;
    class StateC;
    class StateA : public GenericState
    {
        StateB *stateB;
        StateC *stateC;
        int updateCnt;
    public:
        StateA();
        ~StateA();
        void OnEntry();
        bool Update(FSM *fsm, event_t * event);
        void OnExit();
        void SetTransistionStates(StateB *stateB, StateC *stateC);
    };

    class StateB : public GenericState
    {
        StateC *stateC;
        int updateCnt;
    public:
        StateB();
        ~StateB();
        void OnEntry();
        bool Update(FSM *fsm, event_t * event);
        void OnExit();
        void SetTransistionStates(StateC *stateC);
    };
    class StateC : public GenericState
    {
        StateA *stateA;
        int updateCnt;
    public:
        StateC();
        ~StateC();
        bool Update(FSM *fsm, event_t * event);
        void SetTransistionStates(StateA *stateA);
    };
    
    std::queue<GenericState::event_t> *eventQueue;
    StateA *stateA;
    StateB *stateB;
    StateC *stateC;
public:

    typedef enum e_eventSignal
    {
        EVENTSIGNAL_TIMEOUT = 0,
    }eventSignal_t;
    SpecificFSM();
    ~SpecificFSM();
    void Process();
    void PostToQueue(GenericState::event_t event);
};

