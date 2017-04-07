#include "ws2801led.h"

ws2801led::ws2801led(short int numLEDs, byte bytesPerLED, byte maxValue)
{  
  _numLEDs = numLEDs;
  _bytesPerLED = bytesPerLED;
  _maxValue = maxValue;
  _rainbowSize = maxValue*6;
  _frameLength = numLEDs*bytesPerLED;
  LEDs = new byte[_frameLength];

  //Clear Frame Data
  for(_counter=0; _counter<_frameLength; _counter++)
  {
    LEDs[_counter] = 0;
  }
}

void ws2801led::setPixel(short int pixelIndex, byte *pixelColour)
{
  _counter = _bytesPerLED*(pixelIndex);
  LEDs[ _counter ] = pixelColour[0];
  LEDs[ _counter+1 ] = pixelColour[1];
  LEDs[ _counter+2 ] = pixelColour[2];
}

void ws2801led::getPixel(short int pixelIndex, byte *pixelColour)
{
  _counter = _bytesPerLED*(pixelIndex);
  pixelColour[0] = LEDs[ _counter ];
  pixelColour[1] = LEDs[ _counter+1 ];
  pixelColour[2] = LEDs[ _counter+2 ];
}
