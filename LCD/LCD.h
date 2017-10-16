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
  void startScreen();
private:
  int Epin;
  int RSpin;
  int D4pin;
  int D5pin;
  int D6pin;
  int D7pin;
  int dataPins[4];

};

#endif
