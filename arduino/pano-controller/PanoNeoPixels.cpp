/*
 * https://github.com/technobly/NeoPixel-KnightRider/blob/master/NeoPixel_KnightRider.ino
 */
 
 #include "PanoNeoPixels.h"

PanoNeoPixels::PanoNeoPixels()
{
  _pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  //_pixels.setBrightness(10); // 0-255
  _pixels.begin();
}


void PanoNeoPixels::ShowAll(){
  _mode = true;
}

void PanoNeoPixels::ShowLR(bool lr){
  if (_mode != false || lr != _lr){
   KnightRider(20,2,0xFFFFFF,lr);
  }
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
//   // LR mode
//
//   float tgt = _lr ? 1.0f : -1.0f;
//   _current += (tgt - _current) * 0.05f;
//   
//   float _stateL[] = { 1.0f, 0.2f, 0.00f, 0.0f }; 
//   float _stateR[] = { 0.0f, 0.00f, 0.2f, 1.0f };
//  
//   for (int i = 0; i < NUMPIXELS; i++){
//    float valL = (float)255 * _stateL[i];
//    floats valR = (float)255 * _stateR[i];
//    int valFinal = (valR * _current) + (valL * (1.0f - _current));
//     _pixels.setPixelColor(i, valFinal, 0, 0); // RGB
//     
//    }
//    _pixels.show();
    
  }

  
}

void PanoNeoPixels::KnightRider(uint16_t speed, uint8_t width, uint32_t color, bool left){
  uint32_t old_val[NUMPIXELS];
  //if (left){
    for (int count = 1; count < NUMPIXELS; count++) {
      _pixels.setPixelColor(count, color);
    }
  //}
}

void PanoNeoPixels::ClearStrip(){
  for (uint8_t i = 0; i < NUMPIXELS; i++){
    _pixels.setPixelColor(i, 0x000000);
    _pixels.show();
  }
}

uint32_t PanoNeoPixels::DimColor(uint32_t color, uint8_t width) {
   return (((color&0xFF0000)/width)&0xFF0000) + (((color&0x00FF00)/width)&0x00FF00) + (((color&0x0000FF)/width)&0x0000FF);
}
