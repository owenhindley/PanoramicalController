//#include "ardumidi.h"
#include "PanoNeoPixels.h"
#define NUM_KNOBS 9
#define THRESHOLD 10

int switchButton = 10;
int switchButton5v = 2;
int buttonState;
int lastButtonState = LOW;
bool shiftState = false;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int knobState[NUM_KNOBS*2];

PanoNeoPixels pix = PanoNeoPixels();

void setup(){

  for (int i=0; i < NUM_KNOBS*2; i++){
    knobState[i] = -1;
  }

  
//  Serial.begin(115200);
  pinMode(switchButton5v, OUTPUT);
  digitalWrite(switchButton5v, HIGH);
  pinMode(switchButton, INPUT);
}

void loop(){
  // check shift button state with debouncing
  int reading = digitalRead(switchButton);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        shiftState = !shiftState;
      }
    }
  }

  pix.ShowLR(shiftState);

  lastButtonState = reading;

  // check & transmit knobs
  for (int i=0; i < NUM_KNOBS; i++){
    int currentState = analogRead(i);
    int index = i + (shiftState ? 0 : NUM_KNOBS);
    int diff = abs(currentState - knobState[index]);
    if (diff > THRESHOLD){
//      midi_controller_change(0, index, currentState/8); 
      knobState[index] = currentState;
    }
    
  }

  pix.Update();
  
}

