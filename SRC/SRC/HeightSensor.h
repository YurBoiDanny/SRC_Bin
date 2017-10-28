#pragma once
#include "Arduino.h"
#include "LCDdisplay.h"


class HeightSensor
{
private:
	int trigPin;//Output Signal from the ultrasonic sensor
	int echoPin;//Input Signal from the signal produced by the trig pin on the ulrasonic sensor
	int trashCount;//Stores the number of recycleable materials in the bin

protected:
	float maxHeight;//Max Height of the Bin
	float maxWidth;//Max Width of the Bin
	float prevHeight;//Stores the previous height value
	float currHeight;//Stores the current height value
	float prevWidth;//Stores the previous width value
	float currWidth;//Stores the current width value
	float currBinCap;//Current Bin's Capacity 

public:
	HeightSensor();//Sets pins to default values:3 & 4
	HeightSensor(int trigPin, int echoPin);//Sets pins to user-defined ones
	void setIO();//Sets the pins to input/output;
	float getBinCapacity();//Returns the current bins capacity
	float getBC();//TEMPORARY
	float getMH();//TEMPORARY
	float getDistance();//Calculates Distant
	float getMaxHeight();//Gets total Internal Height of the Bin
	float getMaxWidth();//Gets total Internal Width of the Bin
	int getTrashCount();//Returns the amount of trash in the bin
	~HeightSensor();//Deconstructor
};

