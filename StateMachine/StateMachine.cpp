// StateMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "SpecificFSM.h"
int main()
{
    SpecificFSM specificFSM;
    while (1)
    {
        specificFSM.Process();
        Sleep(1000);
        GenericState::event_t event;
        event.signal = SpecificFSM::eventSignal_t::EVENTSIGNAL_TIMEOUT;
        specificFSM.PostToQueue(event);
    }
    return 0;
}

