#include "digital_out.h"
#include <Arduino.h>


Digital_out::Digital_out(int pin)
{
    Digital_out::pinMask = (1<<pin);
}

void Digital_out::init()
{
    DDRB |= Digital_out::pinMask;
    Serial.print("Initializing");
}

void Digital_out::set_hi()
{
    PORTB |= Digital_out::pinMask;
    highState = true;
    Serial.print("Set High");
}

void Digital_out::set_lo()
{
    PORTB &= ~Digital_out::pinMask;
    highState = false;
    Serial.print("Set Low");
}

void Digital_out::toggle()
{
    if (highState)
    {
        Digital_out::set_lo();
    }
    else
    {
        Digital_out::set_hi();
    }
    
}