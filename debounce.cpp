#include <Arduino.h>
#include <debounce.h>

// basic constructor to set debounce Time.
Debounce::Debounce(int waitTime)
{
      interruptTime = 0;
      debounceTime = waitTime;
      lastInterruptTime = 0;

}

// check time passed in the debounce.
bool Debounce::check()
{
    interruptTime = millis();
    if (Debounce::interruptTime - Debounce::lastInterruptTime > Debounce::debounceTime)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// update last interrupt time.
void Debounce::updateLast()
{
    Debounce::lastInterruptTime = Debounce::interruptTime;
}