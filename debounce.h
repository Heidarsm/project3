#include <arduino.h>


class Debounce{

    public:
        Debounce(int waitTime);
        bool check();
        void updateLast();

    private:
        int lastInterruptTime;
        int interruptTime;
        int debounceTime;

};