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


// Required for real-time clock functions
#include "RTC.h"
// Required for Arduino Cloud Things
#include "thingProperties.h"


// Arduino Cloud Variables (do not uncomment any of these lines):
/* CloudSwitch cloud_huskyTailShouldWag; */


#define TAIL_HIGH_POSITION 137
#define TAIL_LOW_POSITION 56


// Pins used to control the linear servo
struct LinearServoPins
{
  byte hbridgeOutput1;   // Digital output pin 1
  byte hbridgeOutput2;   // Digital output pin 2
  byte analogInput;      // One ADC input pin
};


// Models the Actuonix L16 (L16-140-35-12-P) linear actuator as a servo, via both an H-Bridge and also feedback to the Arduino ADC
class LinearServo : public ArduinoProtoThreadEventHandler
{
  public:
    LinearServo(const LinearServoPins pinSettings, byte slop)
    {
      this->pin.hbridgeOutput1 = pinSettings.hbridgeOutput1;
      this->pin.hbridgeOutput2 = pinSettings.hbridgeOutput2;
      this->pin.analogInput = pinSettings.analogInput;
      this->slop = slop;
    }
    ~LinearServo() { }

    void onStart()
    {
      pinMode(this->pin.hbridgeOutput1, OUTPUT);
      pinMode(this->pin.hbridgeOutput2, OUTPUT);
      this->initialPotentiometerValue = this->currentActuatorPosition();
      Serial.print("LinearServo: [INFO] Initialized at position ");
      Serial.println(this->startPosition());
    }

    void onRunning()
    {
      byte servoPosition = this->currentActuatorPosition();
      unsigned long msSinceStart = millis();
      static byte previousServoPosition;
      ///// Hardware safety logic ///////
      if (this->isInErrorState())
      {
        return;
      }
      if (msSinceStart > 37000 && msSinceStart < 40000) { Serial.println("LinearServo: [WARNING] Prepare for movement"); } // See issue #19
      if (msSinceStart < 40000) { this->resetRetries(); this->resetDutyCycle(); return; } // See issue #19
      if (servoPosition > 244)
      {
        Serial.println("LinearServo: [ERROR] Shutdown due to position high limit exceeded");
        this->actuatorDisable();
        return;
      }
      if (servoPosition < 2)
      {
        Serial.println("LinearServo: [ERROR] Shutdown due to position low limit exceeded");
        this->actuatorDisable();
        return;
      }
      if (this->movementRetries > 2)
      {
        Serial.println("LinearServo: [ERROR] Shutdown due to actuator not responding");
        this->actuatorDisable();
        return;
      }
      if (this->timesDutyCycleExceeded > 4)
      {
        Serial.println("LinearServo: [ERROR] Shutdown due to a trend of exceeding actuator duty cycle");
        this->actuatorDisable();
        return;
      }
      else
      {
        if (this->dutyCycle > 50)
        {
          if (this->timesDutyCycleExceeded < 255) this->timesDutyCycleExceeded++;
          Serial.print("LinearServo: [WARNING] Actuator duty cycle has been exceeded ");
          Serial.print(this->timesDutyCycleExceeded);
          Serial.println(" times");
          this->resetDutyCycle();
        }
      }
      if (this->commandedPosition > 240)
      {
        Serial.println("LinearServo: [WARNING] Commanded position too high");
      }
      if (this->commandedPosition < 5)
      {
        Serial.println("LinearServo: [WARNING] Commanded position too low");
      }
      ///// Servo positioning logic /////
      if (servoPosition < this->commandedPosition - this->slop)
      {
        this->actuatorExtend();
        if (this->currentActuatorPosition() == previousServoPosition) { this->incrementRetries(); } else { this->resetRetries(); }
      }
      else if (servoPosition > this->commandedPosition + this->slop)
      {
        this->actuatorRetract();
        if (this->currentActuatorPosition() == previousServoPosition) { this->incrementRetries(); } else { this->resetRetries(); }
      }
      else
      {
        this->resetRetries();
        this->actuatorHold();
      }
      ///////////////////////////////////
      previousServoPosition = servoPosition;
    }

    void onKill()
    {
      this->alive = false;
      Serial.println("LinearServo: [INFO] Disabled until board reset");
      return;
    }

    byte startPosition()
    {
      byte result = this->initialPotentiometerValue;
      return result;
    }

    void moveToPosition(int servoPosition)
    {
      if (this->commandedPosition != servoPosition)
      {
        this->isMoving = false;
        this->commandedPosition = servoPosition;
      }
    }

    byte currentActuatorPosition()
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

    void moveToCenter()
    {
      this->moveToPosition(123);
    }

    bool isInErrorState()
    {
      return this->errorState;
    }

    bool isAlive()
    {
      return this->alive;
    }

  protected:
    LinearServoPins pin;
    bool alive = true;
    bool isMoving = false;
    bool errorState = false;
    byte initialPotentiometerValue;
    byte commandedPosition = 100;
    byte slop;
    byte movementRetries = 0;
    byte dutyCycle = 0;
    byte timesDutyCycleExceeded = 0;

    void actuatorExtend()
    {
      this->incrementDutyCycle();
      if (!this->isMoving)
      {
        digitalWrite(this->pin.hbridgeOutput1, HIGH);
        digitalWrite(this->pin.hbridgeOutput2, LOW);
        this->isMoving = true;
        Serial.println("LinearServo: [INFO] Extending...");
      }
    }

    void actuatorRetract()
    {
      this->incrementDutyCycle();
      if (!this->isMoving)
      {
        digitalWrite(this->pin.hbridgeOutput1, LOW);
        digitalWrite(this->pin.hbridgeOutput2, HIGH);
        this->isMoving = true;
        Serial.println("LinearServo: [INFO] Retracting...");
      }
    }

    void actuatorHold()
    {
      this->decrementDutyCycle();
      if (this->isMoving)
      {
        digitalWrite(this->pin.hbridgeOutput1, LOW);
        digitalWrite(this->pin.hbridgeOutput2, LOW);
        this->isMoving = false;
        Serial.print("LinearServo: [INFO] Holding at ");
        Serial.print(this->currentActuatorPosition());
        Serial.print(" (Commanded ");
        Serial.print(this->commandedPosition);
        Serial.println(")");
      }
    }

    void actuatorDisable()
    {
      this->actuatorHold();
      this->errorState = true;
    }

    void incrementRetries()
    {
      this->movementRetries++;
      if (this->movementRetries > 1)
      {
        Serial.print("LinearServo: [WARNING] Movement retries now at ");
        Serial.println(this->movementRetries);
      }
    }

    void resetRetries()
    {
      this->movementRetries = 0;
    }

    void incrementDutyCycle()
    {
      if (this->dutyCycle < 255)
      {
        this->dutyCycle++;
      }
    }

    void decrementDutyCycle()
    {
      if (this->dutyCycle > 0)
      {
        this->dutyCycle--;
      }
    }

    void resetDutyCycle()
    {
      this->dutyCycle = 0;
    }
};


LinearServo *tailServo;
ArduinoProtoThread *tailServoThread;

RTCTime currentTime;


void setup()
{
  // Initialize the RTC
  RTC.begin();
  
  // Initialize serial monitor support
  Serial.begin(115200);
  delay(1000);

  // Initialize Arduino Cloud
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  // Initialize linear servo connected to the husky's tail
  LinearServoPins withPinConnections;
  byte andSlop = 5;
  withPinConnections.hbridgeOutput1 = 10;
  withPinConnections.hbridgeOutput2 = 9;
  withPinConnections.analogInput = 0;
  tailServo = new LinearServo(withPinConnections, andSlop);
  tailServoThread = new ArduinoProtoThread();
  tailServoThread->setEventHandlerTo(tailServo);
  tailServoThread->setExecutionIntervalTo(750);  
  tailServoThread->changeStateTo(Start);
}


void loop()
{
  byte currentSeconds;    // Holds the seconds portion of the current time
  byte waggingUp = false; // Direction of tail wag

  // Get data from the board's real-time clock
  RTC.getTime(currentTime);
  currentSeconds = currentTime.getSeconds();
  
  // Check for a servo error state
  if (tailServo->isAlive() && tailServo->isInErrorState())
  {
    tailServoThread->changeStateTo(Kill);
  }
  
  // Wag the tail
  if (cloud_huskyTailShouldWag)
  {
    if (tailServoIsApproximatelyAt(TAIL_HIGH_POSITION) && waggingUp)
    {
      waggingUp = false;
    }
    if (tailServoIsApproximatelyAt(TAIL_LOW_POSITION) && !waggingUp)
    {
      waggingUp = true;
    }
    if (waggingUp)
    {
      tailServo->moveToPosition(TAIL_HIGH_POSITION);
    }
    else
    {
      tailServo->moveToPosition(TAIL_LOW_POSITION);
    }
  }
  
  // Process Arduino Cloud updates
  ArduinoCloud.update();
  // Process servo updates
  tailServoThread->timeSlice();
}

// This function is based on code by forum user robtillaart
// Ref: https://forum.arduino.cc/t/how-do-i-do-an-approximately-equals/391466/3
bool tailServoIsApproximatelyAt(byte targetPosition)
{
  byte x = tailServo->currentActuatorPosition();
  byte y = targetPosition;
  byte epsilon = 5;
  if ((abs(x - y) < epsilon) || (abs(y - x) < epsilon)) { return true; } else { return false; }
}

// This code is executed every time a new value is received from Arduino Cloud.
void onCloudHuskyTailShouldWagChange()
{
  Serial.print("Alexa: [INFO] Arduino Cloud Variable cloud_huskyTailShouldWag changed to ");
  Serial.println(cloud_huskyTailShouldWag ? "TRUE" : "FALSE");
}

/**********************************************************************************************************************/
/* End of HuskyTail.ino ***********************************************************************************************/
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/*** END OF LINE. I MEAN FILE. ****************************************************************************************/
/**********************************************************************************************************************/
