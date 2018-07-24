#include "autonCode_aryaJF3.h"

//LCD
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
bool LCDState = false;
string mainBattery, backupBattery;

int stateCheck = 0;
int soundCheck = 0;

void clearLCD()//Clear both LCD lines
{
	clearLCDLine(0);
	clearLCDLine(1);
}
void clearSound(int time)//Stop playing sounds after (int time) seconds
{
	wait1Msec(time);
	clearSounds();
}
void testSound()//Sound function for determining if blip sound was played while using LCD
{
	if(stateCheck != soundCheck)//If sound was not played then play sound
	{
		playSound(soundShortBlip);
		soundCheck = stateCheck;
	}
	else//No sound if sound was already played
	{
		wait1Msec(100);
		clearSounds();
	}
}

void LCDRun()//Main LCD function
{
	if(nLCDButtons == leftButton)//Turns on the LCD
	{
		LCDState = true;
		playSound(soundUpwardTones);
		bLCDBacklight = true;
		clearSound(500);
	}
	if(LCDState == true)
	{
		if(SensorValue[navPot] <= 500)//RED POLE == 0
		{
			testSound();
			stateCheck = 0;
			displayLCDCenteredString(0,"==              ");
			displayLCDCenteredString(1,"    RED POLE   >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 0;
				displayLCDCenteredString(0,"----RED POLE----");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(1500);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 500 && SensorValue[navPot] <= 1000)//RED RIGHT == 1
		{
			testSound();
			stateCheck = 1;
			displayLCDCenteredString(0,"  ==            ");
			displayLCDCenteredString(1,"<  RED  RIGHT  >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 1;
				displayLCDCenteredString(0,"---RED  RIGHT---");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(1500);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 1000 && SensorValue[navPot] <= 1500)//RED LEFT == 2
		{
			stateCheck = 2;
			testSound();
			displayLCDCenteredString(0,"    ==          ");
			displayLCDCenteredString(1,"<   RED LEFT   >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 2;
				displayLCDCenteredString(0,"----RED LEFT----");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(1500);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 1500 && SensorValue[navPot] <= 2000)//BLUE POLE == 3
		{
			stateCheck = 3;
			testSound();
			displayLCDCenteredString(0,"      ==        ");
			displayLCDCenteredString(1,"<  BLUE  POLE  >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 3;
				displayLCDCenteredString(0,"---BLUE  POLE---");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(1500);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 2000 && SensorValue[navPot] <= 2500)//BLUE RIGHT == 4
		{
			stateCheck = 4;
			testSound();
			displayLCDCenteredString(0,"        ==      ");
			displayLCDCenteredString(1,"<  BLUE RIGHT  >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 4;
				displayLCDCenteredString(0,"---BLUE RIGHT---");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(2000);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 2500 && SensorValue[navPot] <= 3000)//BLUE LEFT == 5
		{
			stateCheck = 5;
			testSound();
			displayLCDCenteredString(0,"          ==    ");
			displayLCDCenteredString(1,"<  BLUE  LEFT  >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 5;
				displayLCDCenteredString(0,"---BLUE  LEFT---");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(2000);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 3000 && SensorValue[navPot] <= 3500)//SKILLS == 6
		{
			stateCheck = 6;
			testSound();
			displayLCDCenteredString(0,"            ==  ");
			displayLCDCenteredString(1,"<    SKILLS    >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 6;
				displayLCDCenteredString(0,"-----SKILLS-----");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(2000);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else//Check Battery Voltage
		{
			stateCheck = 7;
			testSound();
			displayLCDCenteredString(0,"              ==");
			displayLCDCenteredString(1,"<    BATTERY    ");
			while(nLCDButtons == centerButton)
			{
				displayLCDString(0,0,"  Primary: ");
				sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
				displayNextLCDString(mainBattery);
				displayLCDCenteredString(1," ");
			}

		}
		if(nLCDButtons == rightButton)
		{
			LCDState = false;
			playSound(soundDownwardTones);
			wait1Msec(500);
			clearSounds();
		}
	}
	else
	{
		clearLCD();
		bLCDBacklight = false;
	}
}
