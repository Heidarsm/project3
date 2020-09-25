#include <Arduino.h>
#include <analog_in.h>

Analog_in::Analog_in()
{
    Analog_in::inputPin = 5; //Analog input á A5 (5)

}

Analog_in::Analog_in(int pin)
{
    Analog_in::inputPin = pin;

}

void Analog_in::init()
{
    //DDRC &= ~Analog_in::pinMask;

    //ADMUX |= pinMask;

    // ADMUX = (1 << REFS0);
    // ADCSRA |= (1<<ADEN) | ( 1 << ADATE) |(1<<ADSC) |(1<<ADPS2) |(1<<ADPS1) |(1<<ADPS0);


    ADMUX = (1 << REFS0) |inputPin ;
    ADCSRA |= (1<<ADEN) | ( 1 << ADATE) |(1<<ADSC) |(1<<ADPS2) |(1<<ADPS1) |(1<<ADPS0) ;
}

int Analog_in::read()
{
    adc_value = ADCW;
    return adc_value;
}