#include "ardumidi.h"
#include <Adafruit_NeoPixel.h>
#define NUM_KNOBS 9
#define THRESHOLD 10
#define HOLD_CONTROLLER 64

int switchButton = 10;

#define PIN       7 // DIGITAL PIN ON BOARD
#define NUMPIXELS 10 // NUM PIXELS ON STRIP

int switchButton5v = 2;
int pots5v = 3;
int buttonState;
int lastButtonState = LOW;
bool shiftState = false;
bool holdState = false;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastButtonHighTime = 0;
unsigned long holdDelay = 500;  // if button is held down for this long, becomes a 'HOLD' event

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int knobState[NUM_KNOBS*2];

void setup(){

  for (int i=0; i < NUM_KNOBS*2; i++){
    knobState[i] = -1;
  }

  
  Serial.begin(115200);
  pinMode(switchButton5v, OUTPUT);
  pinMode(pots5v, OUTPUT);
  digitalWrite(switchButton5v, HIGH);
  digitalWrite(pots5v, HIGH);
  pinMode(switchButton, INPUT);
  
  pixels.begin();
  pixels.show();
}

void loop(){


  

  // check shift button state with debouncing
  int reading = digitalRead(switchButton);
  // if (reading != lastButtonState) {
  //   // reset the debouncing timer
  //   lastDebounceTime = millis();
  // }

  // if ((millis() - lastDebounceTime) > debounceDelay) {
  //   if (reading != buttonState) {
  //     buttonState = reading;

  //     // only toggle the LED if the new button state is HIGH
  //     if (buttonState == HIGH) {
  //       shiftState = !shiftState;
  //       lastButtonHighTime = millis();
  //     }
  //   }
  // }

  // if (buttonState && (millis() - lastButtonHighTime) > holdDelay){
  //   holdState = true;
  //   midi_controller_change(0, HOLD_CONTROLLER, 127); 
  //   pix.ShowAll();
  // } else if (holdState && !buttonState) {
  //   holdState = false;
  //   midi_controller_change(0, HOLD_CONTROLLER, 0); 
  //   lastButtonHighTime = millis();
    
  // }

  if (reading != buttonState) {
    buttonState = reading;

    holdState = buttonState;

    if (buttonState == HIGH) {
      midi_controller_change(0, HOLD_CONTROLLER, 127); 
      for (int i = 0; i < NUMPIXELS; i++){
        pixels.setPixelColor(i, pixels.Color(255,255,255));
        pixels.show();
      }
    } else {
      for (int i = 0; i < NUMPIXELS; i++){
        pixels.setPixelColor(i, pixels.Color(0,0,0));
        pixels.show();
      }
      midi_controller_change(0, HOLD_CONTROLLER, 0); 
    }
  }
   
  lastButtonState = reading;

  // check & transmit knobs
  for (int i=0; i < NUM_KNOBS; i++){
    int currentState = analogRead(i);
    int index = i + (shiftState ? NUM_KNOBS : 0);
    int diff = abs(currentState - knobState[index]);
    if (diff > THRESHOLD){
      midi_controller_change(0, index, currentState/8); 
      knobState[index] = currentState;
    }
    
  }

  
}

