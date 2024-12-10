// ArduinoProtoThread class
#include "libraries/ArduinoProtoThread.hpp"
// Required for the state machine enums
#include "libraries/ArduinoProtoThreadStateMachine.hpp"


// Wags the tail
class TailWagger : public ArduinoProtoThreadEventHandler
{
  public:
    TailWagger(int pins[])
    {
      this->hbridgePin[0] = pins[0];
      this->hbridgePin[1] = pins[1];
    }
    ~TailWagger() { }

    void onStart()
    {
      pinMode(this->hbridgePin[0], OUTPUT);
      pinMode(this->hbridgePin[1], OUTPUT);
      this->remainStill();
    }
    void onRunning()
    {
      // Flip-flop the tail state
      this->tailState ^= HIGH;
      // Wag if commanded
      if (this->shouldWag)
      {
        this->wag();
      }
      else
      {
        this->remainStill();
      }
    }
    void onKill()
    {
      return;
    }

    void enable()
    {
      this->shouldWag = true;
    }
    void disable()
    {
      this->shouldWag = false;
    }

  protected:
    bool tailState = LOW;
    bool shouldWag = false;
    int hbridgePin[1];

    void wag()
    {
      digitalWrite(9, this->tailState);
      digitalWrite(10, !this->tailState);
    }
    void remainStill()
    {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    }
};


// Gives positive commands to the dog
class Trainer1 : public ArduinoProtoThreadEventHandler
{
  public:
    Trainer1(TailWagger *dogTail)
    {
      this->dogTail = dogTail;
    }
    ~Trainer1() { }

    void onStart()
    {
      return;
    }
    void onRunning()
    {
      this->dogTail->enable();
    }
    void onKill()
    {
      return;
    }

  protected:
    TailWagger *dogTail;
};


// Gives negative commands to the dog
class Trainer2 : public ArduinoProtoThreadEventHandler
{
  public:
    Trainer2(TailWagger *dogTail)
    {
      this->dogTail = dogTail;
    }
    ~Trainer2() { }

    void onStart()
    {
      return;
    }
    void onRunning()
    {
      this->dogTail->disable();
    }
    void onKill()
    {
      return;
    }

  protected:
    TailWagger *dogTail;
};


TailWagger *dogsTail;

Trainer1 *yesTrainer;
Trainer2 *noTrainer;

ArduinoProtoThread *wagThread;
ArduinoProtoThread *yesTrainerThread;
ArduinoProtoThread *noTrainerThread;


void setup() {  
  // Initialize tail wagger
  dogsTail = new TailWagger(new int[10, 9]);
  wagThread = new ArduinoProtoThread();
  wagThread->setEventHandlerTo(dogsTail);
  wagThread->setExecutionIntervalTo(990);  
  wagThread->changeStateTo(Start);

  // Initialize "yes" trainer
  yesTrainer = new Trainer1(dogsTail);
  yesTrainerThread = new ArduinoProtoThread();
  yesTrainerThread->setEventHandlerTo(yesTrainer);
  yesTrainerThread->setExecutionIntervalTo(10000);  
  yesTrainerThread->changeStateTo(Start);

  // Initialize "no" trainer
  noTrainer = new Trainer2(dogsTail);
  noTrainerThread = new ArduinoProtoThread();
  noTrainerThread->setEventHandlerTo(noTrainer);
  noTrainerThread->setExecutionIntervalTo(14500);  
  noTrainerThread->changeStateTo(Start);
}


void loop() {
  wagThread->timeSlice();
  yesTrainerThread->timeSlice();
  noTrainerThread->timeSlice();
}
