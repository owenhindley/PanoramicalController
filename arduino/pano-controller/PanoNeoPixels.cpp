#include "PanoNeoPixels.h"

PanoNeoPixels::PanoNeoPixels()
{
  _pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  _pixels.setBrightness(10); // 0-255
  _pixels.begin();
}


void PanoNeoPixels::ShowAll(){
  _mode = true;
}

void PanoNeoPixels::ShowLR(bool lr){
  _mode = false;
  _lr = lr;
}


void PanoNeoPixels::Update(){
  
  if (_mode) {
    // flash all mode
    _animCounter += 5;
    if (_animCounter > 255){
      _animCounter = 0;
      _flashState = !_flashState;
    }

    for (int i = 0; i < NUMPIXELS; i++){
     _pixels.setPixelColor(i, _pixels.Color(_animCounter,0,0)); // RGB
     _pixels.show();
    }
    
   
  } else {
   // LR mode

   float tgt = _lr ? 1.0f : -1.0f;
   _current += (tgt - _current) * 0.05f;
   
   float _stateL[] = { 1.0f, 0.2f, 0.1f, 0.0f }; 
   float _stateR[] = { 0.0f, 0.1f, 0.2f, 1.0f };
  
   for (int i = 0; i < NUMPIXELS; i++){
    float valL = (float)255 * _stateL[i];
    float valR = (float)255 * _stateR[i];
    int valFinal = (valR * _current) + (valL * (1.0f - _current));
     _pixels.setPixelColor(i, valFinal, 0, 0); // RGB
     
    }
    _pixels.show();
    
  }

  
}

