#include "stdafx.h"
#include "GenericState.h"
#include <iostream>

using namespace std;

GenericState::GenericState()
{
    EntryEnable(false);
    ExitEnable(false);
}

GenericState::~GenericState()
{
}

void GenericState::OnEntry()
{
    cout << "GenericState::OnEntry" << endl;
}

void GenericState::OnExit()
{
    cout << "GenericState::OnExit" << endl;
}

bool GenericState::IsEntryEnabled()
{
    return entryEnable;
}

inline void GenericState::EntryEnable(bool enable)
{
    entryEnable = enable;
}

bool GenericState::IsExitEnabled()
{
    return exitEnable;
}

inline void GenericState::ExitEnable(bool enable)
{
    exitEnable = enable;
}
