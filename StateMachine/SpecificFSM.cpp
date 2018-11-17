#include "stdafx.h"
#include <iostream>
#include "SpecificFSM.h"


using namespace std;
SpecificFSM::SpecificFSM()
{
    eventQueue = new queue<GenericState::event_t>;
    stateA = new StateA();
    stateB = new StateB();
    stateC = new StateC();
    currentState = stateA;
    stateA->SetTransistionStates(stateB, stateC);
    stateB->SetTransistionStates(stateC);
    stateC->SetTransistionStates(stateA);
}

SpecificFSM::~SpecificFSM()
{
    if (eventQueue != NULL)
        delete eventQueue;

    delete stateA;
    delete stateB;
    delete stateC;

}

void SpecificFSM::Process()
{
    if (eventQueue->empty())
        return;

    GenericState::event_t evt = eventQueue->front();
    if (currentState != NULL)
        if (currentState->Update(this, &evt))
            eventQueue->pop();
}

void SpecificFSM::PostToQueue(GenericState::event_t event)
{
    eventQueue->push(event);
}
// ================= StateA ================= 
SpecificFSM::StateA::StateA()
{
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

bool SpecificFSM::StateB::Update(FSM * fsm, event_t * event)
{
    cout << "StateC::Update" << endl;
    updateCnt++;
    if (updateCnt == 5)
    {
        cout << "   StateB -> StateC" << endl;
        fsm->GoToState(stateC);
        updateCnt = 0;
    }
    return true;
}

void SpecificFSM::StateB::OnExit()
{
    cout << "StateB::OnExit" << endl;
}

void SpecificFSM::StateB::SetTransistionStates(StateC * stateC)
{
    this->stateC = stateC;
}

// ================= StateC ================= 
SpecificFSM::StateC::StateC()
{
}

SpecificFSM::StateC::~StateC()
{
}

bool SpecificFSM::StateC::Update(FSM * fsm, event_t * event)
{
    cout << "StateC::Update" << endl;
    updateCnt++;
    if (updateCnt == 5)
    {
        cout << "   StateC -> StateA" << endl;
        fsm->GoToState(stateA);
        updateCnt = 0;
    }
    return true;
}

void SpecificFSM::StateC::SetTransistionStates(StateA * stateA)
{
    this->stateA = stateA;
}
