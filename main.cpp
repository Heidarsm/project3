#include <Arduino.h>
#include <statemachine.h>

stateMachine StateMachine;
char serRead;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  StateMachine.updateState('s');    //The statemachine should
                                    //go autonomusly to next state (1 -> 2)
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0){
    serRead = Serial.read();
    StateMachine.updateState(serRead);
   // StateMachine.operationToDo();
  }
  StateMachine.operationToDo();
    
}

