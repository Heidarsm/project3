#include <arduino.h>

class Analog_in {

    public:
        Analog_in();
        Analog_in(int pin);
        void init();
        int read();

    private:
        uint8_t pinMask;
        int adc_value;
        byte inputPin;
        bool isISR;

};

