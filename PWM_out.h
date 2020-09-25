#include <Arduino.h>

class PWM_out
{
    public:
        PWM_out();
        void set(int duty_cycle);
        void init();
        int getDuty();

    private:

        int currDuty;

};