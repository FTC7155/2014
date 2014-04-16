#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     controller,     sensorI2CMuxController)
#pragma config(Sensor, S2,     color,          sensorCOLORFULL)
#pragma config(Sensor, S3,     blockSonar,     sensorSONAR)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  motorA,          leftPick,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightPick,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel,    tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C1_1,    topLeft,              tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    bottomLeft,           tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    tail,                 tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_1,    topRight,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    bottomRight,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-sensormux.h"	// just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"

int armState = 1;												//  the last state of the arm...  should be "home" as left by autonomous


void home()														  // home position - packing and driving position
{
	servo[bottomLeft] = 64-5;
	servo[bottomRight] = 64+5;
	servo[topLeft] = 64-11;
	servo[topRight] =64+11;
}

void drop()
{														// drop arm position
	servo[bottomLeft] = 64-5;
	servo[bottomRight] = 64+5;
	servo[topLeft] = 64-5;
	servo[topRight] = 64+5;
}

void spit()
{
	motor[leftPick] = 100;
	motor[rightPick] = 100;
	wait10Msec(100);
	motor[leftPick] = 0;
	motor[rightPick] = 0;
}

void pick()
{													 // pick up block - arm position
	servo[bottomLeft] = 64-3;
	servo[bottomRight] = 64+3;
	servo[topLeft] = 64-8;
	servo[topRight] = 64+8 ;

	motor[leftPick] = 100;
	motor[rightPick] = 100;

	int threshold = 10;		// this should work both both orientations of the block (flat face or holes)

	while(SensorValue(blockSonar)>=threshold && joy1Btn(4)!=1){		// make sure the button is working!
		motor[leftPick]=-30;
		motor[rightPick]=-30;
	}

	motor[leftPick]=0;

	motor[rightPick]=0;
}

void inter()
{
	servo[bottomLeft] = 64-8;
	servo[bottomRight] = 64+8;
	servo[topLeft] = 64-8;
	servo[topRight] = 64+8;
}


task baseDrive()
{
	int leftWheelPower, rightWheelPower;
	while(true)
	{
		getJoystickSettings(joystick);

		if(abs(joystick.joy1_y2)<10)								// this deals with joystick "noise"
			leftWheelPower = 0;
		else
			leftWheelPower = joystick.joy1_y2/12.8;

		if(abs(joystick.joy1_y1)<10)
			rightWheelPower = 0;
		else
			rightWheelPower = joystick.joy1_y1/12.8;

		leftWheelPower *= leftWheelPower*sgn(leftWheelPower);			//square it...
		rightWheelPower *= rightWheelPower*sgn(rightWheelPower);

		motor[leftWheel] = leftWheelPower;
		motor[rightWheel] = rightWheelPower;

		if (joy1Btn(1) == 1)									// start tail command
			servo[tail] = 0;  // or 255

		if (joy1Btn(2) == 1)									// stop tail
			servo[tail] = 127;

	}
}

task armDrive()
{
	int topLeftCom = 0;
	int topRightCom = 0;
	int bottomLeftCom = 0;
	int bottomRightCom = 0;

	while(true)
	{
		getJoystickSettings(joystick);

		if (joy2Btn(1) == 1)			// go to home position
		{

			switch(armState) {
			case 1:
				break;
			case 2:
				inter();
				wait10Msec(50);
				home();
				wait10Msec(50);
				break;
			case 3:
				home();
				wait10Msec(50);
				break;
			default:
				break;
			}
			armState = 1;
		}


		if (joy2Btn(2) == 1)		// go to pick up...
		{
			switch(armState){
			case 1:
			case 3:
				inter();
				wait10Msec(50);
				pick();
				wait10Msec(50);
				break;

			case 2:
				break;

			default:
				break;
			}
			armState = 2;						// 2 -- pick up
		}


		if (joy2Btn(3) == 1)
		{

			switch(armState){
			case 1:
				drop();
				wait10Msec(50);
				break;
			case 2:
				inter();
				wait10Msec(50);
				drop();
				wait10Msec(50);
				break;
			case 3:
			default:
				break;
			}
			armState = 3;					  // 3 -- drop
		}

		if (joy2Btn(4) == 1)			// 4 -- manual spit
		{
			//	if(armState==3)
			spit();
		}

		if (joystick.joy2_TopHat == 0)
		{
			topLeftCom = ServoValue[topLeft];
			topRightCom = ServoValue[topRight];
			topLeftCom++;
			topRightCom--;
			servo[topLeft] = topLeftCom;
			servo[topRight] = topRightCom;
		}

		if (joystick.joy2_TopHat == 4)
		{
			topLeftCom = ServoValue[topLeft];
			topRightCom = ServoValue[topRight];
			topLeftCom--;
			topRightCom++;
			servo[topLeft] = topLeftCom;
			servo[topRight] = topRightCom;
		}

		if (joystick.joy2_TopHat == 6)
		{
			bottomLeftCom = ServoValue[bottomLeft];
			bottomRightCom = ServoValue[bottomRight];
			//if ((bottomLeftCom+1)</*59*/)
			//{
				bottomLeftCom++;
				bottomRightCom--;
			//}
			servo[bottomLeft] = bottomLeftCom;
			servo[bottomRight] = bottomRightCom;
		}

		if (joystick.joy2_TopHat == 2)
		{
			bottomLeftCom = ServoValue[bottomLeft];
			bottomRightCom = ServoValue[bottomRight];
			bottomLeftCom--;
			bottomRightCom++;
			servo[bottomLeft] = bottomLeftCom;
			servo[bottomRight] = bottomRightCom;
		}
	}
}

task main()
{
	home(); // keep the robot in home position
	wait10Msec(100);
	StartTask (baseDrive);	// start the baseDrive task
	StartTask (armDrive);		// start the armDrive
	while(true)							// main thread does nothing but wait...
		wait10Msec(50);

}
