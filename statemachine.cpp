#include <statemachine.h>

PWM_out ledTimer;
int ledIntensity;
Digital_in returnFromFault(3,false);


stateMachine::stateMachine(){
    //Initilization
    ledUsed = false;
    state = 1;
    //Initialising digital and analog pins
    ledTimer.init();
    stateMachine::lightInput.init();
    fault.init();
    returnFromFault.init();
}

void stateMachine::ledOperation(){

    // Serial.println(stateMachine::lightInput.read());
    if(ledUsed){
        //The LED is in use so do something else
        ledIntensity = map(stateMachine::lightInput.read(),400,860,0,255);
        ledTimer.set(ledIntensity);
    }
    else{
        ledTimer.set(255);
    }
    
}

int stateMachine::getLedIntensity(){
    return stateMachine::ledIntensity;
}

void stateMachine::blink(int division){
    // this code sets up timer1 for a 1 s  @ 16Mhz system clock (mode 4)
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1 = 0;  //initialize counter value to 0

    OCR1A = (16000000 / 1024 - 1)/division;         // assign target count to compare register A (must be less than 65536)
    TCCR1B |= (1 << WGM12);              // clear the timer on compare match A (Mode 4, CTC on OCR1A)
    TIMSK1 |= (1 << OCIE1A);             // set interrupt on compare match A
    TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer
    sei();  //enable interrupts
}

ISR(TIMER1_COMPA_vect)
{
  // action to be done every 1 sec
    if(ledIntensity == 255){
        ledIntensity = 0;
        ledTimer.set(ledIntensity);
    }
    else if(ledIntensity == 0)
    {
        ledIntensity = 255;
        ledTimer.set(ledIntensity);
    }
    
}

void stateMachine::updateState(char stepOrBack)
{
    //Goes to next state according to statemachine
    //According to the char that is sent in
    // 's' = step, 'b' = back
    // if(stepOrBack == 'r')
    // {
    //     restart();
    // }

    if (stepOrBack == 'x')
    { 
        Serial.println("Fault detected");
        blink(4);
        if(state != 4)
        {
            lastState = state;
        }
        
        state = 4;
        
    }

    if (stepOrBack == 'y')
    {
        Serial.println("Exiting Stop state");
        state = lastState;
    }

    switch (state)
    {
    case 1:              //Initilization state
        if(stepOrBack == 'r' or stepOrBack == 'R')
        {
            state = 1;
        }
        else
        {
            state = 2;
        }
        
        break;
    case 2:                 //Pre Operational
        stateMachine::blink(2);
        if(stepOrBack == 's' or stepOrBack == 'S' )
        {
            state = 3;
        }
        else if (stepOrBack == 'r' or stepOrBack == 'R')
        {
            state = 1;
        }
        //TIMSK1 &= ~(1 << OCIE1A);   //Clearing timer
        break;
    case 3:                //Operatinal state
        
        if(stepOrBack == 's')
        {
            state = 3;    
        }
        else if(stepOrBack == 'r' or stepOrBack == 'R')
        {
            state = 1;
        }
        else if(stepOrBack == 'b' or stepOrBack == 'B')
        {
            state = 2;
        }
        
        break;
    
    case 4:
        //DO NOTHING ERROR STATE
        break;

    default:
        Serial.print("Something went wrong state out of bounds");
        break;
    }
}


void stateMachine::operationToDo(){
    //This is what initilization state is supposed to perform
    if(fault.read())
    {  
        updateState('x');
    }

    if(returnFromFault.read())
    {
        updateState('y');
    }
    

    switch (state)
    {
    
    case 1:             //Initilization
    {  
        Serial.print("Current state:");
        Serial.println(state);
        stateMachine();
        updateState('s');
        break;
    }
    case 2:
    { 
        while(!Serial.available());
        char serRead1 = Serial.read();
        if( serRead1 == '1')
        {
            ledUsed = true;
            updateState('s');  
            
        }
        else if( serRead1 == '2')
        {
            ledUsed = false;     
            updateState('s');  
        }
        else if (serRead1 == 'r' or serRead1 == 'R')
        {
            state = 1;
        }
        
    }
        break;
    case 3:             //Operational
    { 
        ledOperation();
        break;
    }

    case 4:
        //DO NOTHING ERROR STATE
        break;
    
    default:
        break;
    }

    Serial.print("Current state:");
    Serial.println(state);
    if (state == 2)
    {
        Serial.println ("Configuration: press 1 to use LED to folow sensor or 1 to leave LED High");
    }
           
}