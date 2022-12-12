// HuskyTail.ino
// https://github.com/gregkrsak/HuskyTail
//
// An Arduino project for the holiday season!
// Written by Greg M. Krsak (greg.krsak@gmail.com)
//
// Moves a linear actuator (motor with an H Bridge) through a range of travel,
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


// Tail wag duration (in milliseconds)
#define TIMEBASE 1500
// H Bridge pins (feel free to change these)
#define HBRIDGE_PIN_1 9
#define HBRIDGE_PIN_2 10


// GLOBAL VARIABLES ////////////////////////////////////////////////
Timer<1/*task*/> timer;
bool goingUp = true;


// RUN ONCE ////////////////////////////////////////////////////////
void setup()
{
  // Set H Bridge output pins
  pinMode(HBRIDGE_PIN_1, OUTPUT);
  pinMode(HBRIDGE_PIN_2, OUTPUT);
  // Set timebase
  timer.every(TIMEBASE, switchDirection);
}


// RUN INDEFINITELY ////////////////////////////////////////////////
void loop()
{
  timer.tick();
  if (goingUp)
  {
    digitalWrite(HBRIDGE_PIN_1, HIGH);
    digitalWrite(HBRIDGE_PIN_2, LOW);
  }
  else
  {
    digitalWrite(HBRIDGE_PIN_1, LOW);
    digitalWrite(HBRIDGE_PIN_2, HIGH);
  }
}


// RUN EVERY TIMEBASE //////////////////////////////////////////////
void switchDirection()
{
  // Flip-flop the wag direction state
  goingUp ? goingUp = false : goingUp = true;

}
// End of HuskyTail.ino
