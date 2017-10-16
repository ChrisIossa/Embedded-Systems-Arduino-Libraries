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
  LCD(int EpinIn,int RSpinIn,int D4PinIn,int D5PinIn,int D6PinIn,int D7PinIn);

  //public methods
  void initalize();
  void writeFourBits(byte val);
  void sendByte(byte val);
  void sendChar(byte val);
  void writeStr(char* str);

private:
  int Epin;
  int RSpin;
  int D4Pin;
  int D5Pin;
  int D6Pin;
  int D7Pin;

};

#endif
