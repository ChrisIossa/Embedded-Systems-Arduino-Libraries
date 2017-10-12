//includes our definition
#include "LEDS.h"

//constructor
LEDS::LEDS( int redLEDPin, int greenLEDPin)
{
	_redLEDPin = redLEDPin;
	_greenLEDPin = greenLEDPin;
	pinMode( _redLEDPin, OUTPUT);
	pinMode( _greenLEDPin, OUTPUT);
}

// set the level of the red LED
//illumination level in percentage of full @level
void LEDS::setRedLevel(byte level)
{
	byte dutyCycle = map (level, 0,100,0,255);
	analogWrite(_redLEDPin, dutyCycle);
}

// set the level of the green LED
//illumination level in percentage of full @level
void LEDS::setGreenLevel(byte level)
{
	byte dutyCycle = map (level, 0,100,0,255);
	analogWrite(_greenLEDPin, dutyCycle);
}
