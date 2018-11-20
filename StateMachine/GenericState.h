#pragma once
#include <stdint.h>
class FSM;
class GenericState;



class GenericState
{
  bool entryEnable;
  bool exitEnable;

public:
  typedef struct s_event
  {
    int signal;
    void* data;
    uint32_t dataSize;
  }event_t;

  GenericState();
  ~GenericState();

  virtual void OnEntry();
  virtual bool Update(FSM *fsm, event_t *event) = 0;
  virtual void OnExit();
  inline bool IsEntryEnabled() { return entryEnable; }
  inline void EntryEnable(bool enable) { entryEnable = enable; }
  inline bool IsExitEnabled() { return exitEnable; }
  inline void ExitEnable(bool enable) { exitEnable = enable; }
};


