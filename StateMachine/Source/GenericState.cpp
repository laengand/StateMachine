#include "GenericState.h"

using namespace std;
using namespace Gadgets;

GenericState::GenericState()
{
  EntryEnable(false);
  ExitEnable(false);
}

GenericState::~GenericState() {}
void GenericState::OnEntry() {}
void GenericState::OnExit() {}


