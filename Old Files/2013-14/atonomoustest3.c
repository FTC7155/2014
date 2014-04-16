#pragma config(Sensor, S1,     touchSensor,    sensorTouch)
#pragma config(Sensor, S2,     leftIR,         sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     rightIR,        sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     colourSensor,   sensorCOLORFULL)
#pragma config(Motor,  motorA,          leftMotor,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightMotor,    tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.



task main()
{

  while (true)
	{
		if(touchSensor==1){
			motor[leftMotor] = 100;
			motor[leftMotor] = 100;
		}
	}
}
