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
    void KnightRider(uint16_t speed, uint8_t width, uint32_t color, bool dir);
    void ClearStrip();
    uint32_t DimColor(uint32_t color, uint8_t width);
  private:
    Adafruit_NeoPixel _pixels;
    bool _mode;
    bool _lr;
    float _current;
    int _animCounter;
    bool _flashState;
    
};

