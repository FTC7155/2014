#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     controller,     sensorNone)
#pragma config(Sensor, S2,     color,          sensorCOLORFULL)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     leftKnot,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightKnot,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     leftWheel,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     rightWheel,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_1,    servo7,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-sensormux.h"  // just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"               // the files for the Logitech controller to work by USB to the laptop and then by bluetooth/USB to the NXT, NOT by samantha module.

#define DEBUG														// used only for debugging... delete when trying the program for real.

const tMUXSensor irLeft = msensor_S4_1; // configuring the IR sensor over the SMUX.
const tMUXSensor irRight = msensor_S4_2;


void initializerobot() {		// get robot ready

}

void seekbeacon(){														// function for finding the IR beacon, called seekBeacon.

	int valRight;
	int valLeft;

	while(true){

			valRight = HTIRS2readDCDir(irRight);
			valLeft  = HTIRS2readDCDir(irLeft);

#ifdef DEBUGIR
			nxtDisplayCenteredTextLine(3, "%d, %d", valLeft, valRight);
#endif

				//if beacon is not in sight
				if(valLeft==0 && valRight==0){
					motor[leftMotor] = -75;
					motor[rightMotor] = 75;
					break;
				}

				//if beacon is on the left
				if(valLeft<=5 && valLeft>0 && valRight<=5 && valRight>0){
						//turn left
						motor[leftMotor] = 0;
						motor[rightMotor] = 100;
						break;
				}
				//if beacon is on the right
				if(valLeft>5 && valRight>5){
						//turn right
						motor[leftMotor] = 100;
						motor[rightMotor] = 0;
						break;
				}
				//if beacon is straight ahead
				if(valLeft>5 && valRight<5){
						//stay on course
						motor[leftMotor] = 80;
						motor[rightMotor] = 80;
						break;
				}
				//if beacon is right in front
				if(valLeft==7 && valRight==3){
						//stop
						motor[leftMotor] = 0;
						motor[rightMotor] = 0;
						break;
				}


			}

}

void dropblock() {  // function for dropping the block; dropblock

}

void linefinder() {  // function to get to the line, go along line, and park on ramp
	bool seekingline = true;
	while(seekingline==true)
		{
			 int sensor4 = SensorValue[color];

#ifdef DEBUGCOLOUR
			nxtDisplayCenteredTextLine(3, "%d, %d", sensor4);
#endif

			if(SensorValue(color)==2){
					motor[leftMotor] = 50;
					motor[rightMotor] = 100;

				}
				else {
					motor[leftMotor] = 100;
					motor[rightMotor] = 50;
				}
	//wait1Msec(3000);
	}
}

task main()
{
initializerobot();
waitForStart();
seekbeacon();
dropblock();
linefinder();


}
