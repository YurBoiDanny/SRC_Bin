#include "LCDdisplay.h"


LCDdisplay::LCDdisplay()
{
	this->RS_pin = 1;
	this->RW_pin = 2;
	this->d5_pin = 4;
	this->d6_pin = 5;
	this->d7_pin = 6;
	this->d8_pin = 7;
	setLCD();
}

LCDdisplay::LCDdisplay(int RS_pin, int RW_pin, int d5_pin, int d6_pin, int d7_pin, int d8_pin)
{
		this->RS_pin = RS_pin;
		this->RW_pin = RW_pin;
		this->d5_pin = d5_pin;
		this->d6_pin = d6_pin;
		this->d7_pin = d7_pin;
		this->d8_pin = d8_pin;
		setLCD();	
}

LCDdisplay::~LCDdisplay()
{
}

void LCDdisplay::setLCD()
{
	lcd = new LiquidCrystal(RS_pin, RW_pin, d5_pin, d6_pin, d7_pin, d8_pin);
	lcd->begin(16, 2);
}

LiquidCrystal LCDdisplay::getLCD()
{
	return *lcd;
}

void LCDdisplay::print(String str)
{
	lcd->print(str);
	lcd->home();
}

void LCDdisplay::print(int num)
{
    lcd->print(num);
	lcd->home();
}

