#include "HeightSensor.h"

HeightSensor::HeightSensor( )
{
	trigPin = 3;
	echoPin = 4;
	setIO();
	maxHeight = getMaxHeight();
}

HeightSensor::HeightSensor(int trigPin, int echoPin)
{
	this->echoPin = echoPin;
	this->trigPin = trigPin;
	setIO();
	maxHeight = getMaxHeight();
}

void HeightSensor::setIO()
{
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

float HeightSensor::getDistance( )
{
	long duration = 0;
	double distance = 0;

	// Clears the trigPin
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(echoPin, HIGH);

	// Calculating the distance
	distance = (duration*0.033) / 2;

	//Testing for correct distance values
	//Serial.print("distance:");
	//Serial.print(distance);
	//Serial.println(" ");
	//End of Testing

	return distance;
}

float HeightSensor::getMaxHeight()
{
	//Get the max float from the UltraSonic Sensor
	maxHeight = -10000; //Find a better method of setting a lower
	int runTimes = 150;//Number of times the loop is ran. This enssures the accuracy of the reading.

	for (int i = 0; i < runTimes; i++)
	{
		currHeight = getDistance(); //Sets Current Distance Measured by the Ultrasonic Sensor
		if (maxHeight<currHeight) maxHeight = currHeight;//If the a new length is greater than distance make that the new max distance
	}

	//Serial.print("max height is...");
	//Serial.println(maxHeight);
	return maxHeight;
}

float HeightSensor::getMaxWidth( )
{
	//Get the max float from the UltraSonic Sensor
	maxWidth = -1000000; //Find a better method of setting a lower
	int runTimes = 150;//Number of times the loop is ran. This enssures the accuracy of the reading.

	for (int i = 0; i < runTimes; i++)
		currWidth += getDistance(); //Sets Current Distance Measured by the Ultrasonic Sensor

	maxWidth /= runTimes; //Get Average Maximum Height

	//Serial.print("Max width is...");
	//Serial.println(maxWidth);
	return maxWidth;
}

float HeightSensor::getBinCapacity()
{
	currBinCap = ((maxHeight - currHeight) / maxHeight)*100;//Calculates Current Capacity %
	return currBinCap;
}

float HeightSensor::getBC()
{
	return currBinCap;
}

float HeightSensor::getMH()
{
	return maxHeight;
}

int HeightSensor::getTrashCount( )//Fix this function
{
	int temp = 0;

	prevWidth = getDistance();
	currWidth = getDistance();

	while(currWidth > (prevWidth+1)|| currWidth <(prevWidth +1))// Needs to handle variances up to +-1cm
	{
		currWidth = getDistance();
		temp++;
		prevWidth = currWidth;
	}

	//Serial.print("The number of bin items is...");
	//Serial.println(trashCount);
	return trashCount+=temp; //NOTE: this function does not cater for when the bin is completely filled
}


HeightSensor::~HeightSensor()
{
}
