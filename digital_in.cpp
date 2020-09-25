#include <Arduino.h>
#include <digital_in.h>

Digital_in::Digital_in()
{
    Digital_in::pinMask = (1<<4);   //Button input on pin 12 (PB4) with ISR set on true. (0, false);
    isISR = false;

}

Digital_in::Digital_in(int pin, bool ISR)
{
    Digital_in::pinMask = (1<<pin);
    isISR = ISR;

}

void Digital_in::init()
{
    DDRB &= ~Digital_in::pinMask;

    PORTB |= pinMask;

    if(isISR)   //ONLY FOR PIN 12
    {
        PCICR |= 0x01;
        PCMSK0 |= 0x10;

    }

}

bool Digital_in::read()
{
bool isOpen = PINB & pinMask;
return isOpen;
}