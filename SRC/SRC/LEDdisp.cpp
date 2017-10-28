#include "LEDdisp.h"


LEDdisp::LEDdisp()
{
	IO1 = 9;
	IO2 = 10;
	IO3 = 11;
	IO4 = 12;
}

LEDdisp::LEDdisp(int IO1, int IO2, int IO3, int IO4)
{
	this->IO1 = IO1;
	this->IO2 = IO2;
	this->IO3 = IO3;
	this->IO4 = IO4;

	pinMode(IO1, OUTPUT);
	pinMode(IO2, OUTPUT);
	pinMode(IO3, OUTPUT);
	pinMode(IO4, OUTPUT);

}

void LEDdisp::startUp()
{
	int brightness = 0;

	pinMode(IO1, INPUT);
	pinMode(IO2, INPUT);
	pinMode(IO3, OUTPUT);
	pinMode(IO4, OUTPUT);

	// One LED fade on for a "boot up"
	digitalWrite(IO4, LOW);
	while (brightness < 260)
	{
		analogWrite(IO3, brightness);
		brightness += 5;
		delay(50);
	}

	// finish the cycle since we are at an offset
	// before going to loop()
	delay(20);
	pinMode(IO3, INPUT);
	pinMode(IO4, INPUT);
	flashLED(IO4, IO1);
	flashLED(IO4, IO2);
	flashLED(IO4, IO3);
	flashLED(IO4, IO2);
	flashLED(IO4, IO1);
	flashLED(IO3, IO4);
	flashLED(IO3, IO2);
	flashLED(IO3, IO1);
	flashLED(IO2, IO4);
	flashLED(IO2, IO3);
	flashLED(IO2, IO1);
	flashLED(IO1, IO4);
	flashLED(IO1, IO3);
	flashLED(IO1, IO2);
}

///////////////////////////////////////////
// Function to flash LED and change the LED
// pins back to INPUT.
///////////////////////////////////////////
void LEDdisp::flashLED(int hi, int low)
{
	pinMode(hi, OUTPUT);
	pinMode(low, OUTPUT);
	digitalWrite(hi, HIGH);
	digitalWrite(low, LOW);
	delay(125);//1.6875 for all LED's on simultaneously
	pinMode(hi, INPUT);
	pinMode(low, INPUT);
}

void LEDdisp::cycle(String state)
{
	if (state == "R2L")
	{
		// Cycle across the LEDs from right to left
		flashLED(IO1, IO2);
		flashLED(IO1, IO3);
		flashLED(IO1, IO4);
		flashLED(IO2, IO1);
		flashLED(IO2, IO3);
		flashLED(IO2, IO4);
		flashLED(IO3, IO1);
		flashLED(IO3, IO2);
		flashLED(IO3, IO4);
		flashLED(IO4, IO1);
		flashLED(IO4, IO2);
		flashLED(IO4, IO3);
	}

	else if (state == "L2R")
	{
		// Cycle across the LEDs from left to right
		flashLED(IO4, IO2);
		flashLED(IO4, IO1);
		flashLED(IO3, IO4);
		flashLED(IO3, IO2);
		flashLED(IO3, IO1);
		flashLED(IO2, IO4);
		flashLED(IO2, IO3);
		flashLED(IO2, IO1);
		flashLED(IO1, IO4);
		flashLED(IO1, IO3);
	}
}

void LEDdisp::displayBinCap()
{
	currHeight = getDistance();
	//Serial.print("Current height is...");
	//Serial.println(currHeight);

	currBinCap = getBinCapacity();
	//Serial.print("Capacity Percentage is...");
	//Serial.println(currBinCap);

	if (currHeight > (prevHeight + 1)|| currHeight > (prevHeight - 1))
	{
		//Serial.println("Increment the # of Lit LED's");

		if (currBinCap < 25.00)
		{
			digitalWrite(IO1,HIGH);
			
		}
		else if (currBinCap > 25.00 && currBinCap < 50.00 )
		{
			//Serial.println("currBinCap > 25.00 && currBinCap < 50.00");
			digitalWrite(IO2, HIGH);
		}
		else if (currBinCap > 50.00 && currBinCap < 75.00)
		{
			//Serial.println("currBinCap > 50.00 && currBinCap < 75.00");
			digitalWrite(IO2, HIGH);
			digitalWrite(IO3, HIGH);

		}
		else if (currBinCap > 75.00)
		{
			//Serial.println("currBinCap > 75.00");
			digitalWrite(IO2, HIGH);
			digitalWrite(IO3, HIGH);
			digitalWrite(IO4, HIGH);
			
			//Notifications Pin
			digitalWrite(2, HIGH);
		}
	}
	else if (currHeight < (prevHeight+1) || currHeight < (prevHeight-1))
	{
		//Serial.println("Decrement the # of Lit LED's");
		if (currBinCap < 25.00)
		{
			//Serial.println("currBinCap < 25.00");
			digitalWrite(IO2, LOW);
			digitalWrite(IO3, LOW);
			digitalWrite(IO4, LOW);
		}
		else if (currBinCap > 25.00 && currBinCap < 50.00)
		{
			//Serial.println("currBinCap > 25.00 && currBinCap < 50.00");
			digitalWrite(IO3, LOW);
			digitalWrite(IO4, LOW);
		}
		else if (currBinCap > 50.00 && currBinCap < 75.00)
		{
			//Serial.println("currBinCap > 50.00 && currBinCap < 75.00");
			digitalWrite(IO4, LOW);
		}
		else if (currBinCap > 75.00)
		{
			//Serial.println("currBinCap > 75.00");

		}
	}

	prevHeight = currHeight;
}

LEDdisp::~LEDdisp()
{
}
