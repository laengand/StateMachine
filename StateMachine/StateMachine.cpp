// StateMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "SpecificFSM.h"
#include <iostream>
#include <thread>
#include <conio.h>

using namespace std;
using namespace Gadgets;
SpecificFSM *specificFSM;
bool stopMain = false;
void handleInput(bool *stopThread)
{
  int input;
  char c_input;
  while (!(*stopThread))
  {
    c_input = _getche();
    if (c_input == '\0')
      continue;
    input = atoi(&c_input);
    cout << endl;
    if (input > 4)
      stopMain = true;
    else
    {
      GenericState::event_t event;
      event.signal = (SpecificFSM::eventSignal_t)input;
      specificFSM->PostQueue(event);
    }
  }
}
int main()
{
  bool stopThread = false;

  specificFSM = new SpecificFSM();
  thread t(handleInput, &stopThread);

  while (!stopMain)
  {
    specificFSM->Process();
    Sleep(200);
  }
  stopThread = true;
  t.join();
  delete specificFSM;
  return 0;
}

