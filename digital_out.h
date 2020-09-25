#include <arduino.h>

class Digital_out {

    public:
        Digital_out(int pin);
        void init();
        void set_hi();
        void set_lo();
        void toggle();

    private:
        uint8_t pinMask;
        bool highState;

};

