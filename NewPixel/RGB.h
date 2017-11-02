#ifndef __RGB_H__
#define __RGB_H__

#include <Arduino.h>

class RGB
{
 public:
  // Constructor
  RGB( uint8_t pin, uint16_t numPixels );

  // Destructor
  ~RGB();

  // Member functions
  void setColor( uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue );
  void clear();
  void show();

 private:
  // Instance data
  const uint8_t     pin;
  const uint16_t    numPixels;
  const uint16_t    numBytes;
  uint8_t          *pixels;
  volatile uint8_t *port;
  uint8_t           pinMask;

  // Offsets for the various color components
  const uint8_t rOffset = 0;
  const uint8_t gOffset = 1;
  const uint8_t bOffset = 2;
};


#endif
