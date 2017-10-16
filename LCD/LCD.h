#ifndef __LCD_H__
#define __LCD_H__

//standard includes
#include <Arduino.h>

// This class encapsulates the commands needed to interface
// with and LCD Display

class LCD
{
public:

  //constructor
  LCD(EpinIn, RSpinIn, D4PinIn, D5PinIn, D6PinIn, D7PinIn);

  //public methods
  void initalize();
  void writeFourBits(byte val);
  void sendByte(byte val);
  void sendChar(byte val);
  void writeStr(char* str);

private:
  int Epin, RSpin, D4Pin, D5Pin, D6Pin, D7Pin;

};

#endif
