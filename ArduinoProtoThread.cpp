// ArduinoProtoThread
// ArduinoProtoThread.cpp
//
// Implements a protothread API, allowing Arduino compatibles to multitask.
//
// Copyright 2018, 2019 Greg M. Krsak <greg.krsak@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//


#include "ArduinoProtoThread.hpp"

// Arduino library
#include <Arduino.h>


//
// Member Function: setEecutionIntervalTo
// Purpose: Sets the protothread execution interval.
// Parameters:
//  newIntervalInMs: Try to run this protothread every X number of milliseconds.
// Returns: void
//
void ArduinoProtoThread::setExecutionIntervalTo(unsigned long newIntervalInMs)
{
  this->executionInterval = newIntervalInMs;
}


//
// Member Function: changeStateTo
// Purpose: Changes the state of the protothread's state machine.
// Parameters:
//  newState: The new state for the protothread. See ArduinoProtoThreadStateMachine.hpp for details.
// Returns: void
//
void ArduinoProtoThread::changeStateTo(ArduinoProtoThreadState newState)
{
  this->state = newState;
  return;
}


//
// Member Function: currentState
// Purpose: Returns the state of the protothread's state machine.
// Returns: enum
//
ArduinoProtoThreadState ArduinoProtoThread::currentState()
{
  ArduinoProtoThreadState result = this->state;
  return result;
}


//
// Member Function: setEventHandlerTo
// Purpose: Sets the protothread's delegate.
// Parameters:
//  *object: The protothread's delegate. See ArduinoProtoThreadEventHandler.hpp for details.
// Returns: void
//
void ArduinoProtoThread::setEventHandlerTo(ArduinoProtoThreadEventHandler *object)
{
  object->__this = this;
  this->delegate = object;
  return;
}


//
// Member Function: timeSlice
// Purpose: Executes the protothread for one slice of time.
// Returns: void
//
void ArduinoProtoThread::timeSlice()
{
  unsigned long currentTime;
  ArduinoProtoThreadState state;

  state = this->currentState();

  switch (state)
  {
    case Start:
      this->delegate->onStart();
      this->changeStateTo(Running);
      break;
    case Running:
      this->delegate->onRunning();
      this->changeStateTo(Waiting);
      break;
    case Waiting:
      currentTime = millis();
      this->timeDifference = currentTime - this->previousExecutionTime;
      if (this->timeDifference > this->executionInterval)
      {
        this->previousExecutionTime = currentTime;
        this->changeStateTo(Running);
      }
      break;
    case Kill:
      this->delegate->onKill();
      this->changeStateTo(Killed);
      break;
    case Killed:
      // TODO: A future thread manager class will cleanup dead threads
      break;
  }
}

// End of ArduinoProtoThread.cpp
