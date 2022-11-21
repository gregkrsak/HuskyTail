// HuskyTail.ino
// https://github.com/gregkrsak/HuskyTail
//
// An Arduino project for the holiday season!
// Written by Greg M. Krsak (greg.krsak@gmail.com)
//
// Moves a linear actuator (electric servo) through ~1in (~2.5cm) of travel,
// in order to "wag" the tail of a standing Husky decoration, which my daughter
// and I bought in the outdoor Christmas decorations section at Home Depot.
//
// This is free and unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
// 
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// 
// For more information, please refer to <http://unlicense.org/>
//
// Ho, Ho, Ho.


// Needed for the Timer class
// Reference: https://github.com/contrem/arduino-timer
#include "arduino-timer.h"
// Needed for the Servo class
// Reference: https://github.com/arduino-libraries/Servo
#include <Servo.h>


// Servo motion limits (changing these could lead to broken stuff)
#define SERVO_TAIL_UP_STOP   90
#define SERVO_TAIL_DOWN_STOP 70
// Servo motion timebase (in milliseconds)
#define TIMEBASE 125
// Servo PWM pin (feel free to change this to another PWM pin)
#define SERVO_PIN 9


// GLOBAL VARIABLES ////////////////////////////////////////////////
Timer<1/*task*/> timer;
Servo linearActuator;


// RUN ONCE ////////////////////////////////////////////////////////
void setup()
{
  // Set servo PWM output pin
  linearActuator.attach(SERVO_PIN);
  // Set timebase
  timer.every(TIMEBASE, base);
}


// RUN INDEFINITELY ////////////////////////////////////////////////
void loop()
{
  timer.tick();
}


// RUN EVERY TIMEBASE //////////////////////////////////////////////
void base()
{
  static byte counter = SERVO_TAIL_DOWN_STOP;
  static bool goingUp = true;

  // Increment or decrement the counter appropriately
  goingUp ? counter++ : counter--;

  // Set the "going up or down" boolean flag appropriately
  if (counter > SERVO_TAIL_UP_STOP)
  {
    goingUp = false;
  }
  if (counter < SERVO_TAIL_DOWN_STOP)
  {
    goingUp = true;
  }

  // Move the servo. The counter equals the position.
  linearActuator.write(counter);
}
// End of HuskyTail.ino
