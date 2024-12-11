/**********************************************************************************************************************/
/*** SEASONS GREETINGS, PROGRAM! PLEASE DIVERT YOUR EYES TO LINE 316 **************************************************/
/**********************************************************************************************************************/


// ArduinoProtoThread
// ArduinoProtoThreadStateMachine.hpp
//
// Abstract class that defines a state machine for ArduinoProtoThread.
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

// Used for pure virtual functions. I think this looks cleaner and is more self-documenting.
#define PURE_VIRTUAL 0


// Used for state machines
enum ArduinoProtoThreadState { Start, Running, Waiting, Kill, Killed };


//
// Abstract class: ArduinoProtoThreadStateMachine
// Purpose: Defines the API for a state machine.
//
class ArduinoProtoThreadStateMachine
{
  public:
    inline virtual ~ArduinoProtoThreadStateMachine() = PURE_VIRTUAL;

    virtual void changeStateTo(ArduinoProtoThreadState newState) = PURE_VIRTUAL;
    virtual ArduinoProtoThreadState currentState();

  protected:
    ArduinoProtoThreadState state;
};
ArduinoProtoThreadStateMachine::~ArduinoProtoThreadStateMachine() { }

/**********************************************************************************************************************/
/* End of ArduinoProtoThreadStateMachine.hpp **************************************************************************/
/**********************************************************************************************************************/


// ArduinoProtoThread
// ArduinoProtoThreadEventHandler.hpp
//
// Abstract class that defines a delegate object for ArduinoProtoThread state transitions.
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

// Uncomment this line if splitting this code into separate files
/* #include "ArduinoProtoThread.hpp" */


class ArduinoProtoThread;

// Used for pure virtual functions. I think this looks cleaner and is more self-documenting.
#define PURE_VIRTUAL 0


class ArduinoProtoThreadEventHandler
{
  public:
    inline virtual ~ArduinoProtoThreadEventHandler() = PURE_VIRTUAL;

    virtual void onStart() = PURE_VIRTUAL;
    virtual void onRunning() = PURE_VIRTUAL;
    virtual void onKill() = PURE_VIRTUAL;

    // Stores the delegation pattern context (the "this" of the parent composition object)
    ArduinoProtoThread *__this;
};
ArduinoProtoThreadEventHandler::~ArduinoProtoThreadEventHandler() { }

/**********************************************************************************************************************/
/* End of ArduinoProtoThreadEventHandler.hpp **************************************************************************/
/**********************************************************************************************************************/


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

// Uncomment these lines if splitting this code into separate files
/* #include "ArduinoProtoThreadStateMachine.hpp" */
/* #include "ArduinoProtoThreadEventHandler.hpp" */


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

/**********************************************************************************************************************/
/* End of ArduinoProtoThread.hpp **************************************************************************************/
/**********************************************************************************************************************/


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

// Uncomment this line if splitting this code into separate files
/* #include "libraries/ArduinoProtoThread.hpp" */

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

/**********************************************************************************************************************/
/* End of ArduinoProtoThread.cpp **************************************************************************************/
/**********************************************************************************************************************/


// HuskyTail
// HuskyTail.ino
//
// Wags the tail of a Home Depot outdoor Christmas decoration.
//
// NOTE: 1. You may need to set syntax highlighting to the C++ language.
//       2. This file is a concatenation of several project files, which were (formerly) separate,
//          but had to be combined due to a bug in the Arduino Cloud server software.
//
// Copyright 2018, 2019, 2024 Greg M. Krsak <greg.krsak@gmail.com>
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


// Required for Arduino Cloud Things
#include "thingProperties.h"


// Arduino Cloud Variables (do not uncomment any of these lines):
/* CloudSwitch cloud_huskyTailShouldWag; */


// Pins used to control the linear servo
struct LinearServoPins
{
  byte hbridgeOutput[1]; // Two digital output pins
  byte analogInput;      // One ADC input pin
};


// Models the Actuonix L16 (L16-140-35-12-P) linear actuator as a servo, via both an H-Bridge and also feedback to the Arduino ADC
class LinearServo : public ArduinoProtoThreadEventHandler
{
  public:
    LinearServo(const LinearServoPins pinSettings)
    {
      this->pin.hbridgeOutput[0] = pinSettings.hbridgeOutput[0];
      this->pin.hbridgeOutput[1] = pinSettings.hbridgeOutput[1];
      this->pin.analogInput = pinSettings.analogInput;
    }
    ~LinearServo() { }

    void onStart()
    {
      pinMode(this->pin.hbridgeOutput[0], OUTPUT);
      pinMode(this->pin.hbridgeOutput[1], OUTPUT);
      this->initialPotentiometerValue = this->potentiometerValue();
      this->commandedPosition = this->initialPotentiometerValue;
    }

    void onRunning()
    {
      byte servoPosition = this->potentiometerValue();
      Serial.print(servoPosition);
      if (this->servoIsMisaligned())
      {
        if (servoPosition < this->commandedPosition) { this->actuatorExtend(); Serial.print("<"); }
        if (servoPosition > this->commandedPosition) { this->actuatorRetract(); Serial.print(">"); }
      }
      else
      {
        this->actuatorHold();
        Serial.print("=");
      }
      Serial.println(this->commandedPosition);
    }

    void onKill()
    {
      return;
    }

    byte startPosition()
    {
      byte result = this->initialPotentiometerValue;
      return result;
    }

    void moveToPosition(int servoPosition)
    {
      this->commandedPosition = servoPosition;
    }

  protected:
    LinearServoPins pin;
    byte initialPotentiometerValue;
    byte commandedPosition;


    void actuatorExtend()
    {
      digitalWrite(this->pin.hbridgeOutput[0], HIGH);
      digitalWrite(this->pin.hbridgeOutput[1], LOW);
    }

    void actuatorRetract()
    {
      digitalWrite(this->pin.hbridgeOutput[0], LOW);
      digitalWrite(this->pin.hbridgeOutput[1], HIGH);
    }

    void actuatorHold()
    {
      digitalWrite(this->pin.hbridgeOutput[0], LOW);
      digitalWrite(this->pin.hbridgeOutput[1], LOW);
    }

    bool servoIsMisaligned()
    {
      bool result = (this->potentiometerValue() != this->commandedPosition);
      return result;
    }

    byte potentiometerValue()
    {
      byte result;
      int rawValue;
      int constrainedValue;
      long mappedValue;
      rawValue = analogRead(this->pin.analogInput);
      mappedValue = map(rawValue, 0, 1023, 0, 255);
      constrainedValue = constrain(mappedValue, 0, 255);
      result = (byte)constrainedValue;
      return result;
    }
};



LinearServo *tailServo;
ArduinoProtoThread *tailServoThread;


void setup()
{
  // Initialize serial monitor support
  Serial.begin(115200);
  delay(1500);

  // Initialize Arduino Cloud
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  // Initialize linear servo connected to the husky's tail
  LinearServoPins withPinConnections;
  withPinConnections.hbridgeOutput[0] = 10;
  withPinConnections.hbridgeOutput[1] = 9;
  withPinConnections.analogInput = 0;
  tailServo = new LinearServo(withPinConnections);
  tailServoThread = new ArduinoProtoThread();
  tailServoThread->setEventHandlerTo(tailServo);
  tailServoThread->setExecutionIntervalTo(100);  
  tailServoThread->changeStateTo(Start);
}


void loop()
{
  ArduinoCloud.update();
  tailServoThread->timeSlice();
}


// This code is executed every time a new value is received from Arduino Cloud.
void onCloudHuskyTailShouldWagChange()
{
  // do nothing
}

/**********************************************************************************************************************/
/* End of HuskyTail.ino ***********************************************************************************************/
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/*** END OF LINE. I MEAN FILE. ****************************************************************************************/
/**********************************************************************************************************************/
