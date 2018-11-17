#include "stdafx.h"
#include <iostream>
#include "SpecificFSM.h"
#include <Windows.h>

using namespace std;
void SpecificFSM::ThreadFunction(SpecificFSM *specificFSM)
{
    while (!specificFSM->IsThreadStopped())
    {
        Sleep(1000);
        GenericState::event_t event;
        event.signal = SpecificFSM::eventSignal_t::EVENTSIGNAL_TIMEOUT;
        specificFSM->PostToQueue(event);
    }
}

SpecificFSM::SpecificFSM()
{
    stateA = new StateA();
    stateB = new StateB();
    stateC = new StateC();
    
    stateA->SetTransistionStates(stateB, stateC);
    stateB->SetTransistionStates(stateC);
    stateC->SetTransistionStates(stateA);
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
    updateCnt++;
    switch (event->signal)
    {
    case EVENTSIGNAL_TIMEOUT:
    {
        if (updateCnt == 5)
        {
            cout << "   StateA -> StateB" << endl;
            fsm->GoToState(stateB);
        }
        else if (updateCnt == 15)
        {
            cout << "   StateA -> StateC" << endl;
            fsm->GoToState(stateC);
            updateCnt = 0;
        }
        break;
    }
    default:
        break;
    }
    return true;
}

void SpecificFSM::StateA::OnExit()
{
    cout << "StateA::OnExit" << endl;
}
void SpecificFSM::StateA::SetTransistionStates(StateB *stateB, StateC *stateC)
{
    this->stateB = stateB;
    this->stateC = stateC;
}
// ================= StateB ================= 
SpecificFSM::StateB::StateB()
{
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
    updateCnt++;
    switch (event->signal)
    {
    case EVENTSIGNAL_TIMEOUT:
        if (updateCnt == 5)
        {
            cout << "   StateB -> StateC" << endl;
            fsm->GoToState(stateC);
            updateCnt = 0;
        }
        break;
    default:
        break;
    }
    return true;
}

void SpecificFSM::StateB::OnExit()
{
    cout << "StateB::OnExit" << endl;
}

void SpecificFSM::StateB::SetTransistionStates(StateC *stateC)
{
    this->stateC = stateC;
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
    updateCnt++;
    switch (event->signal)
    {

    case EVENTSIGNAL_TIMEOUT:
    {
        if (updateCnt == 5)
        {
            cout << "   StateC -> StateA" << endl;
            fsm->GoToState(stateA);
            updateCnt = 0;
        }
    }
    break;
    default:
        break;
    }
    return true;
}

void SpecificFSM::StateC::SetTransistionStates(StateA * stateA)
{
    this->stateA = stateA;
}
