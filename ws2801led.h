#ifndef ws2801led_h
#define ws2801led_h
#include "Arduino.h"

class ws2801led
{
  public:
    ws2801led(short int numLEDs, byte bytesPerLED, byte maxValue);
    void setPixel(short int pixelIndex, byte *pixelColour);
    void getPixel(short int pixelIndex, byte *pixelColour);
    
    byte* LEDs;
    
    short int _rainbowSize;
    short int _frameLength;
    short int _numLEDs;
    byte _bytesPerLED;
    short int _maxValue;
    
  private:
    unsigned short int _counter;
};

#endif
