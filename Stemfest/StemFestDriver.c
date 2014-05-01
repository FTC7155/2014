////////////////////////////////////////////////////////////////////////////////
///////                    Driver Control Custom V2                  ///////////
////////////////////////////////////////////////////////////////////////////////

//Pragma Statements - Only motors really needed, sensors optional.
#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     color,          sensorCOLORFULL)
#pragma config(Sensor, S3,     compass,        sensorI2CHiTechnicCompass)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     block,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     tail,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     slide,         tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Needed to make the joysticks work



task baseDrive()  //Task for driving the main part of the robot
{
	int leftWheelPower, rightWheelPower;
	while(true)
	{
		getJoystickSettings(joystick); //Updates info from joysticks

		if(abs(joystick.joy1_y2)<10)								// this deals with joystick "noise"
			leftWheelPower = 0;
		else
			leftWheelPower = joystick.joy1_y2/14.1;

		if(abs(joystick.joy1_y1)<10)
			rightWheelPower = 0;
		else
			rightWheelPower = joystick.joy1_y1/14.1  ;

		leftWheelPower *= leftWheelPower*sgn(leftWheelPower);			//square it...
		rightWheelPower *= rightWheelPower*sgn(rightWheelPower);

		motor[leftWheel] = leftWheelPower;
		motor[rightWheel] = rightWheelPower;

		if (joy1Btn(1) == 1)									// start tail command
			motor[tail] = 100;

		if (joy1Btn(2) == 1)									// stop tail
			motor[tail] = 0;

		if (joy1Btn(3) == 1)                                    // reverse tail
			motor[tail] = -100;

	}
}

task slideDrive()  //task for driving the vertical slide on the robot
{
	while(true)  //looping
	{
		getJoystickSettings(joystick); //updates info from joystick
		if(joystick.joy2_TopHat == 0)  //if up button is pressed
		{
			motor[slide] = 100; //make slide go up
		}
		else if(joystick.joy2_TopHat == 4 ) //if down button is pressed
		{
			motor[slide] = -100;   //make slide go down
		}
		else  //if no button is pressed
		{
			motor[slide] = 0; //stop slide motor
		}


	}
}

task catrinDrive() //FOR CATRIN TO DRIVE
{
	while(true)
	{
		getJoystickSettings(joystick);   //update joystick data

		if(joy2Btn(1)) //blocks in
		{
			motor[block] = 100;
		}
		if(joy2Btn(8)) //stop block motor
		{
			motor[block] = 0;
		}
		if(joy2Btn(2)) //blocks out
		{
			motor[block] = -100;
		}

	}
}

task dylanDrive() //FOR DYLAN TO DRIVE
{
	while(true)
	{
		getJoystickSettings(joystick);  //update joystick data
		if(joy2Btn(8)) //blocks out
		{
			motor[block] = -100;
		}
		if(joy2Btn(6)) //blocks in
		{
			motor[block] = 100;
		}
		if(joy2Btn(7)) //stop block motor
		{
			motor[block] = 0;
		}
	}
}

void waitForSelection ()  //choose driving code for catrin or dylan
{
	getJoystickSettings(joystick);
	while (joy2Btn(9) == 0 && joy2Btn(10) == 0) //Waiting for a program to be chosen.
		getJoystickSettings(joystick);
}

void startSelection ()  //switch tasks for catrin and dylan
{
	if (joy2Btn(9) == 1)
	{
		StartTask (catrinDrive);
		StopTask (dylanDrive);
	}
	if (joy2Btn(10) == 1)
	{
		StartTask (dylanDrive);
		StopTask (catrinDrive);
	}
}

/*    ==OLD CODE FOR ARM==
task armDrive()
{
	while (true)
	{
	getJoystickSettings(joystick);
		if(joy2Btn(11)==1)
		{
			motor[arm] = 20;
		}
		else if (joy2Btn(12)==1)
		{
			motor[arm] = -20;
		}
		else
		{
			motor[arm] = 0;
		}
	}
}
*/

//MAIN TASK
task main()
{
	bFloatDuringInactiveMotorPWM = false; //remove later - keeps power on while code is inactive...i think *calls for nomi*
	StartTask (baseDrive);  //calling for base drive task
	StartTask (slideDrive); //calling for slide drive task
	//StartTask (armDrive); //OLD calling for old arm  -- NOT NEEDED ANYMORE
	StartTask (dylanDrive); //switch out before hand with dylanDrive and catrinDrive

	waitForSelection (); //switching for dylan and catrin driving - NOT SURE IF WORKING

	startSelection();  //starting tasks for dylan and catrin - NOT SURE IF WORKING

	while(true) //just in case the driver wants to switch in between them or presses the wrong button.
	{
    waitForSelection();
    startSelection();
	}

}
