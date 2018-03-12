#include "PanoNeoPixels.h"

PanoNeoPixels pix = PanoNeoPixels();

unsigned long time;
bool flip = false;

void setup() {
  pix.ShowAll(); 
}

void loop() {
  pix.Update();

//  if (millis() - time > 2000){
//    time = millis();
//    flip = !flip;
//    pix.ShowLR(flip);
//  }


}
