#pragma once
#include "Arduino.h"
#include "LCDdisplay.h"
#include "HeightSensor.h"





class LEDdisp:public HeightSensor
{
private:
	
	int IO1;//A
	int IO2;//B
	int IO3;//C
	int IO4;//D

public:
	LEDdisp();
	LEDdisp(int IO1,int IO2,int IO3,int IO4);
	void cycle(String state);
	void flashLED(int hi, int lo);
	void displayBinCap();
	void startUp();
	~LEDdisp();
};

