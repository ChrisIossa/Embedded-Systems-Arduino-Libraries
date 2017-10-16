#include "LCD.h"

LCD::LCD(int EpinIn,int RSpinIn,int D4PinIn,int D5PinIn,int D6PinIn,int D7PinIn)
{
  for (int i=7;i<=12;i++)
  {
    pinMode(i,OUTPUT);
  }  
  Epin=EpinIn;
  RSpin=RSpinIn;
  D4pin=D4PinIn;
  D5pin=D5PinIn;
  D6pin=D6PinIn;
  D7pin=D7PinIn;
  dataPins[0]=D4pin;
  dataPins[1]=D5pin;
  dataPins[2]=D6pin;
  dataPins[3]=D7pin;
  
}

void LCD::startScreen()
{

  digitalWrite(Epin, LOW);
  digitalWrite(RSpin, LOW);
  initalize();
  sendByte(0x28);
  sendByte(0x0C);
  sendByte(0x06);
  sendByte(0x01);
  delay(3);
}

void LCD::initalize()
{
  delay(15);
  writeFourBits(0x03);
  delay(5);
  writeFourBits(0x03);
  delayMicroseconds(100);
  writeFourBits(0x03);
  writeFourBits(0x02);
}

void LCD::writeFourBits(byte val)
{
  for(int i=0; i<4; i++)
  {
    if(val&0x01)
    {
      digitalWrite(dataPins[i],HIGH);
    }
    else
    {
      digitalWrite(dataPins[i],LOW);
    }
    val>>=1;
  }
  digitalWrite(Epin, HIGH);
  digitalWrite(Epin,LOW);
  delayMicroseconds(100);
}

void LCD::sendByte(byte val)
{
  digitalWrite(RSpin,LOW);
  writeFourBits(val>>4);
  writeFourBits(val);
}

void LCD::sendChar(byte val)
{
  digitalWrite(RSpin,HIGH);
  writeFourBits(val>>4);
  writeFourBits(val);
}

void LCD::writeStr(char* str)
{
  while (*str)
  {
   sendChar(*str);
   str++;
  }
}
