#ifndef __TEMP_H__
#define __TEMP_H__

//standard includes
#include <Arduino.h>

// This class encapsulates the commands needed to read
// and interpret data from the DHT11 Sensor

class Temp
{
public:
  //constructor
  Temp(int D2PinIn);

  //public methods
  int readState (boolean val);
  boolean readDHT (float *temp, float *humid);
  byte reassembleByte(int* arrayIn, int iStart);



private:
  int D2;
  float humid = 0;
  float temp = 0;
  const int maxTime = 1600;
};


#endif
