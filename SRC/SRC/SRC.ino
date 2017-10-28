/*
 Name:		SRC.ino (Smart Recycling System)
 Created:	10/10/2017 7:54:06 AM
 Author:	Daniel Gordon

 Summary:
	This is the code for SRC bin. There are four components to the code:
		1) LED Display (For Testing and UI)
		2) Height and Lid open/close sensor
		3) GPS Module
*/


//Pre-complier Directives
#include "LEDdisp.h"
#include "HeightSensor.h"
#include <SoftwareSerial.h>
#include <BlynkSimpleStream.h>
//End of Pre-complier Directives

#define BLYNK_PRINT SwSerial

//List of Global Components
	//LCDdisplay lcd1;


SoftwareSerial SwSerial(10, 11);//RX,TX pins on the app



char auth[] = "0937bb033594485290dadad1ff1e3e6c "; /*fd0a296d4cee429689b752b5cc478f0d*/
WidgetTerminal terminal(V1);
WidgetMap myMap(V2);
float BinCapacity = 0;

//LEDdisp ledDisp1; //Chalieplexed LED array
LEDdisp ledDisp2(5, 6, 7, 8);// 1:1 single wired LED's
HeightSensor hs1; //Height Sensor
BlynkTimer dispBinCapTimer;
BlynkTimer showGaugeTimer;
//End of Global Components List


//void notifyOnBinCapacity()
//{
//	// Invert state, since button is "Active LOW"
//	int isButtonPressed = !digitalRead(2);
//
//	if (isButtonPressed) 
//	{
//		/*terminal.println("Bin_Capacity>90.00%");
//		terminal.flush();*/
//
//		// Note:
//		//   We allow 1 notification per 15 seconds for now.
//		Blynk.notify("Max Bin Capacity Achieved!");	
//	}
//
//}

void dispBinCap()
{

	ledDisp2.displayBinCap();
	//float maxHeight = hs1.getMH();
	//float currBinCap = ((maxHeight-hs1.getDistance())/maxHeight)*100;
	Blynk.virtualWrite(V3, BinCapacity);
}

//void showGauge()
//{
//	
//	float currBinCapacity = 50/*hs1.getBC()*/;
//	terminal.print("The bin capacity is...");
//	terminal.println(currBinCapacity);
//	terminal.flush();
//
//	Blynk.virtualWrite(V3, currBinCapacity);
//
//	//	if (BinCapacity == 90)
//	//		digitalWrite(2, HIGH);
//	//	else if (BinCapacity > 100)
//	//		BinCapacity = 0;
//	//
//	//	Blynk.virtualWrite(V3,BinCapacity);
//	//	++BinCapacity;
//}

// the setup function runs once when you press reset or power the board
void setup()
{
	SwSerial.begin(9600);
	Serial.begin(9600);
	Blynk.begin(Serial, auth);
	


	terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
	terminal.println(F("-------------"));
	;

	dispBinCapTimer.setInterval(/*1000*/31.25, dispBinCap);
	//showGaugeTimer.setInterval(1000/*31.25*/, showGauge);

	// Setup notification button on pin 2
	pinMode(2, INPUT_PULLUP);
	// Attach pin 2 interrupt to our handler
	//attachInterrupt(digitalPinToInterrupt(2), notifyOnBinCapacity, CHANGE);


	int index = 1;
	double lat = 10.639649;
	double lon = -61.400213;
	myMap.location(index, lat, lon, "UWI_SRC_bin");
}

// the loop function runs over and over again until power down or reset
void loop()
{

	//To-do List:
		//1)Get Max Heigh of the bin
			/*
				Create a getMax function under the HeightSensor Class
			*/

			//2)Generate % of current capacity of the bin
				/*
				 12 pins => 100%/3 = 33.33%
				*/

				//3)Capacity % from step2 determines how many led's are lit
					/*
						Increment/Decrement Number of LED's on
					*/

					//3.5) Make a counter for the amount of trash added to the bin
						/*
							Use a sencond ultrasonic sensor place at the opening
							of the bin to detect if an object enters it.
						*/

						//4)Set up GPS Module
							/*
								Research how to use the module with Arduino Uno...have Fun!
							*/

							//5)Store Coordinate to Dropbox or an Online Cloud storage via a text

							//6)Parse that text file to enter, and use a next Arduino to get location and send it back?

						//END OF TO-DO LIST//

////Start of Development Code//

		Blynk.run();
		dispBinCapTimer.run();


////End of Development Code//

}