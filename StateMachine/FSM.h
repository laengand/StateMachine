#pragma once
#include "GenericState.h"
class FSM
{
	GenericState* currentState;
public:
	FSM();
	~FSM();
	void GoToState(GenericState *state);

};

