#pragma once
class GenericState
{
public:
	GenericState();
	~GenericState();
	virtual void OnEntry();
	virtual void OnExit();
};

