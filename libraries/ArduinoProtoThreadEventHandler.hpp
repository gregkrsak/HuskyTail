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

// Needed for ArduinoProtoThread
#include "ArduinoProtoThread.hpp"
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

// End of ArduinoProtoThreadEventHandler.hpp
