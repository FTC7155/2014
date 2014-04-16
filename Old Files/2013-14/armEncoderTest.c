#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     color,          sensorCOLORFULL)
#pragma config(Sensor, S3,     compass,        sensorI2CHiTechnicCompass)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     slide,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     block,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     tail,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     arm,           tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-sensormux.h"	// just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-ultrasound.h"
#include "JoystickDriver.c"								// for the waitForStart() command.

const tMUXSensor irLeft = msensor_S4_3;		// configuring the IR and sonar sensor over the SMUX.
const tMUXSensor irRight = msensor_S4_2;
const tMUXSensor sonarLeft = msensor_S4_4;
const tMUXSensor sonarRight = msensor_S4_1;



task main()
{

	nMotorEncoder[arm] = 0;
	nMotorEncoderTarget[arm] = 10;
	motor[arm] = 10;
	while(nMotorRunState[arm] != runStateIdle)
	{

	}
	motor[arm] = 0;

}
