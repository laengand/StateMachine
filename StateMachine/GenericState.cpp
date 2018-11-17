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

void GenericState::s_OnEntry(GenericState * state)
{
    state->OnEntry();
}
void GenericState::s_OnExit(GenericState * state)
{
    state->OnExit();
}
void GenericState::EntryEnable(bool enable)
{
    onEntry = enable ? &s_OnEntry : NULL;
}

void GenericState::ExitEnable(bool enable)
{
    onExit = enable ? &s_OnExit : NULL;;
}
