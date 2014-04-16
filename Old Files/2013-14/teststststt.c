#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     color,          sensorCOLORFULL)
#pragma config(Sensor, S3,     compass,        sensorI2CHiTechnicCompass)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     slide,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     block,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     tail,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     arm,         tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-sensormux.h"	// just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-ultrasound.h"

const tMUXSensor irLeft = msensor_S4_3;		// configuring the IR and sonar sensor over the SMUX.
const tMUXSensor irRight = msensor_S4_2;
const tMUXSensor sonarLeft = msensor_S4_4;
const tMUXSensor sonarRight = msensor_S4_1;

int compassAngle, compassTarget, nCompassHeading, compassOrigin; //used for turning and configuring compass+9*=
bool okay=false;

void turnleft(int angleInput) {
	compassAngle = 0;											//TURNING CODE
	compassOrigin = SensorValue[compass];
	compassTarget = SensorValue[compass]-angleInput%360;
	while(SensorValue[compass]!=compassTarget){
		compassAngle = abs(compassOrigin-SensorValue[compass])%360; //calib
		nxtDisplayBigStringAt(0, 31, "%d, %d", SensorValue[compass], compassTarget);
		if(compassAngle<compassTarget){
			motor[leftWheel] = 10;												//and we stop the motors and exit
			motor[rightWheel] = -10;
			okay = false;
		}
		else if(compassAngle>compassTarget){
			motor[leftWheel] = -10;
			motor[rightWheel] = 10;
			okay = false;
		}
		else if(compassAngle == compassTarget) {
			motor[leftWheel] = 0;
			motor[leftWheel] = 0;
			okay = true;
		}
	}
}

void turnright(int angleInput) {
	compassAngle = 0;											//TURNING CODE
	compassOrigin = SensorValue[compass];
	compassTarget = (SensorValue[compass]+angleInput)%360;
	while(SensorValue[compass]!=compassTarget){
		compassAngle = compassOrigin-SensorValue[compass]%360; //calib
		nxtDisplayBigStringAt(0, 31, "%d, %d", SensorValue[compass], compassTarget);
		//if(compassAngle<compassTarget){												//Might need testing, if does not work, switch '<' with '>' and '>' with '<' in if statements
			motor[leftWheel] = -10;												//and we stop the motors and exit
			motor[rightWheel] = 10;
/*		}
		else if(compassAngle>compassTarget){
			motor[leftWheel] = 10;
			motor[rightWheel] = -10;
		}
		else if(compassAngle == compassTarget) {
			motor[leftWheel] = 0;
			motor[rightWheel] = 0;
		}
		*/
	}
}

task main()
{
//kindOfAllOfAutonomous();
turnright(280);
}
