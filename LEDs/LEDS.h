#ifndef __LEDS_H__
#define __LEDS_H__

//Std Includes
#include <Arduino.h>

// This class encapsulates the commands needed to
// control the illumination of two LEDs
class LEDS
{
	public: 
		//constructor
		LEDS(int redLEDPin, int greenLEDPin);

		//Public methods
		void setRedLevel( byte level);
		void setGreenLevel(byte level);

	private:
		//instance data
	int _redLEDPin;
	int _greenLEDPin;	
};

#endif
