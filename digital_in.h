
#include <arduino.h>

class Digital_in {

    public:
        Digital_in();
        Digital_in(int pin, bool ISR);
        void init();
        bool read();

    private:
        uint8_t pinMask;
        bool isISR;

};

