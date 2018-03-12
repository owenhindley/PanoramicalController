#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN       7 // DIGITAL PIN ON BOARD
#define NUMPIXELS 4 // NUM PIXELS ON STRIP

class PanoNeoPixels
{
  public:
    PanoNeoPixels();
    void ShowLR(bool lr);
    void ShowAll();
    void Update();
  private:
    Adafruit_NeoPixel _pixels;
    bool _mode;
    bool _lr;
    float _current;
    int _animCounter;
    bool _flashState;
    
};

