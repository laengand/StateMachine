#include "stdafx.h"
#include "GenericState.h"
#include <iostream>

using namespace std;
using namespace Gadgets;

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


