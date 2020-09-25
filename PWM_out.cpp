#include <Arduino.h>
#include <PWM_out.h>
//TIMER2 USED TO NOT INTERRUPT MILLIS() IN DEBOUNCE THAT RUNS ON TIMER0;

PWM_out::PWM_out()
{
    
}

void PWM_out::init()
{
    DDRD = 0b00001000;
    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS22);
    OCR2B = 0;
}
//Duty cycle is 0-255;
void PWM_out::set(int duty_cycle)
{
    OCR2B = duty_cycle;
    PWM_out::currDuty = duty_cycle;
}

int PWM_out::getDuty()
{
    return(PWM_out::currDuty);
}