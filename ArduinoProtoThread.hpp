// ArduinoProtoThread
// ArduinoProtoThread.hpp
//
// Defines a protothread API, allowing Arduino compatibles to multitask.
//
// https://github.com/gregkrsak/ArduinoProtoThread
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

#pragma once

// Needed for ArduinoProtoThreadStateMachine
#include "ArduinoProtoThreadStateMachine.hpp"
// Needed for ArduinoProtoThreadEventHandler
#include "ArduinoProtoThreadEventHandler.hpp"


//
// Class: ArduinoProtoThread
// Derived from: ArduinoProtoThreadStateMachine
// Purpose: Defines a protothread API, allowing Arduino compatibles to multitask.
//
class ArduinoProtoThread : public ArduinoProtoThreadStateMachine
{
  public:
    ArduinoProtoThread() { }
    inline virtual ~ArduinoProtoThread();

    void setExecutionIntervalTo(unsigned long newIntervalInMs);
    void setEventHandlerTo(ArduinoProtoThreadEventHandler *object);
    void timeSlice();

    // BEGIN from ArduinoProtoThreadStateMachine //////////
    void changeStateTo(ArduinoProtoThreadState newState);
    ArduinoProtoThreadState currentState();
    // END from ArduinoProtoThreadStateMachine //////////

  protected:
    unsigned long timeDifference;
    unsigned long executionInterval;
    unsigned long previousExecutionTime;
    ArduinoProtoThreadEventHandler *delegate;
};
ArduinoProtoThread::~ArduinoProtoThread() { }


// End of ArduinoProtoThread.hpp
