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
// An optional "dog bark" sound is played, if an Adafruit Sound Board is
// connected.
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


// Tail wag one-way travel duration (in milliseconds)
#define TIMEBASE 750
// How long of a wait until the husky animates (in seconds)
#define ANIMATION_DELAY 45
// How many times the dog wags its tail at the start of each animation period
#define NUMBER_OF_WAGS  5
// Internal counter threshold
#define ANIMATION_COUNTER_THRESHOLD ((1000 / TIMEBASE) * ANIMATION_DELAY)
// H Bridge pins (feel free to change these)
#define HBRIDGE_PIN_1 9
#define HBRIDGE_PIN_2 10
// Sound Board pins (feel free to change these)
#define SOUND_PIN_TRIGGER 6
#define SOUND_PIN_VOLUME  7
// Timebase visual feedback pin
#define UI_PIN_DEBUG 13


// GLOBAL VARIABLES ////////////////////////////////////////////////
Timer<1/*task*/> timer;
bool goingUp = false;
bool shouldAnimate = false;
bool alreadyBarked = false;
bool alreadyWagged = false;
int wagCounter = 0;
long animationCounter = 0;


// RUN ONCE ////////////////////////////////////////////////////////
void setup()
{
  // Set H Bridge output pins
  pinMode(HBRIDGE_PIN_1, OUTPUT);
  pinMode(HBRIDGE_PIN_2, OUTPUT);
  // Set Sound Board output pins
  pinMode(SOUND_PIN_TRIGGER, INPUT);
  digitalWrite(SOUND_PIN_TRIGGER, LOW);
  pinMode(SOUND_PIN_VOLUME, INPUT);
  digitalWrite(SOUND_PIN_VOLUME, LOW);
  // Set timebase
  timer.every(TIMEBASE, base);
  // Set UI pin, which is useful for debugging
  pinMode(UI_PIN_DEBUG, OUTPUT);
}


// RUN INDEFINITELY ////////////////////////////////////////////////
void loop()
{
  timer.tick();
  if (shouldAnimate)
  {
    wag(NUMBER_OF_WAGS);
    bark(); // Dog will play bark sound effect only once per animation period
  }
  else
  {
    remain_still(); // Dog does nothing when outside of animation period
  }
}


// RUN EVERY TIMEBASE //////////////////////////////////////////////
void base()
{
  // Flip-flop the animation state, if appropriate
  if (animationCounter > ANIMATION_COUNTER_THRESHOLD)
  {
    animationCounter = 0;
    wagCounter = 0;
    alreadyBarked = false;
    alreadyWagged = false;
    shouldAnimate = !shouldAnimate;
  }
  
  // Flip-flop the wag direction state and increase the wag counter
  goingUp = !goingUp;
  if(goingUp)
  {
    wagCounter++;
  }
  // Increase the animation counter
  animationCounter++;
}


// HELPER FUNCTIONS ////////////////////////////////////////////////
void wag(int howManyTimes)
{
  if (!alreadyWagged)
  {
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
    if (wagCounter > howManyTimes)
    {
      alreadyWagged = true;
      flashDebugLedBasedOn(false);
    }
    else
    {
      flashDebugLedBasedOn(goingUp);
    }
  }
}

void bark()
{
  if (!alreadyBarked)
  {
    pinMode(SOUND_PIN_TRIGGER, OUTPUT);
    digitalWrite(SOUND_PIN_TRIGGER, LOW);
    alreadyBarked = true;
  }
  else
  {
    pinMode(SOUND_PIN_TRIGGER, INPUT);
    digitalWrite(SOUND_PIN_TRIGGER, LOW);
  }
}

void remain_still()
{
  digitalWrite(HBRIDGE_PIN_1, LOW);
  digitalWrite(HBRIDGE_PIN_2, LOW);
}

void flashDebugLedBasedOn(bool flag)
{
  digitalWrite(UI_PIN_DEBUG, flag);
}

// End of HuskyTail.ino
