#include <Arduino.h>
#include <analog_in.h>
#include <PWM_out.h>
#include <digital_in.h>
#include <digital_out.h>
#include <debounce.h>

class stateMachine{

    public:
        stateMachine();
        
        void updateState(char stepOrBack);
        void start();
        void blink(int division);
        int getLedIntensity();
        
        //Operations of each state
        void operationToDo();
        void ledOperation();

    private:
        int state;             //Initilization = 1, Operational = 3                   
        int analogReadValue;
        int ledIntensity;
        bool ledUsed;
        char serRead;
        char lastState;
        
        Analog_in lightInput;    //Analog input á A5 (5)
        Digital_in fault; //Button input on pin 12 (PB4) with ISR set on true. (0, false);
        
        
};