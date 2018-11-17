#pragma once
#include <stdint.h>
class FSM;
class GenericState;



class GenericState
{
protected:

public:
    typedef struct s_event
    {
        int signal;
        void* data;
        uint32_t dataSize;
    }event_t;
    typedef void(OnEntry_t)(GenericState* state);
    typedef void(OnExit_t)(GenericState* state);
    OnEntry_t *onEntry;
    OnExit_t *onExit;
    GenericState();
    ~GenericState();

    virtual void OnEntry();
    virtual bool Update(FSM *fsm, event_t *event) = 0;
    virtual void OnExit();
    void EntryEnable(bool enable);
    void ExitEnable(bool enable);
    static void s_OnEntry(GenericState * state);
    static void s_OnExit(GenericState * state);
};


