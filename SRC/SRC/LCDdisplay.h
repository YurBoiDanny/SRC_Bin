#pragma once
#include "Arduino.h"
#include<LiquidCrystal.h>


class LCDdisplay
{

private:
	LiquidCrystal* lcd; //Pointer to LCD to be created dynamically
	int counter = 0;//Multipurposed Counter
	int RS_pin;//Register Select pin
	int RW_pin;//Read/Write pin
	int	d5_pin, d6_pin, d7_pin, d8_pin;//Data pins (4 upto 7)
	
public:
	LCDdisplay();
	LCDdisplay(int RS_pin, int RW_pin, int d5_pin, int d6_pin, int d7_pin, int d8_pin);
	~LCDdisplay();
	

	//Member Functions
	void setLCD(); //Initializes the LCD
	LiquidCrystal getLCD(); //Gets the LCD variable
	void print(String str); //Prints a string to the LCD
	void print(int num);//Prints a number to the LCD
	//End of Member Functions
};

