#include "ardumidi.h"
#define NUM_KNOBS 9
#define THRESHOLD 10

int switchButton = 0;
bool shiftState = false;
int knobState[NUM_KNOBS*2];

void setup(){

  for (int i=0; i < NUM_KNOBS*2; i++){
    knobState[i] = -1;
  }
  
  Serial.begin(115200);
  pinMode(switchButton, INPUT);
}

void loop(){
  shiftState = digitalRead(switchButton);
  for (int i=0; i < NUM_KNOBS; i++){
    int currentState = analogRead(i);
    int index = i + (shiftState ? 0 : NUM_KNOBS);
    int diff = abs(currentState - knobState[index]);
    if (diff > THRESHOLD){
      midi_controller_change(0, index, currentState/8); 
      knobState[index] = currentState;
    }
    
  }
  
}

