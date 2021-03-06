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
#include "JoystickDriver.c"								// for the waitForStart() command.

const tMUXSensor irLeft = msensor_S4_3;		// configuring the IR and sonar sensor over the SMUX.
const tMUXSensor irRight = msensor_S4_2;
const tMUXSensor sonarLeft = msensor_S4_4;
const tMUXSensor sonarRight = msensor_S4_1;

int compassAngle, nCompassHeading, compassOrigin; //used for turning and configuring compass

void turnleft(int compassTarget) {
	compassAngle = 0;											//TURNING CODE
	nCompassHeading = SensorValue[compass];
	compassOrigin = nCompassHeading;
	while(abs(compassAngle)!=compassTarget){
		nCompassHeading = SensorValue[compass];
		compassAngle = abs(compassOrigin - nCompassHeading);
		if(abs(compassAngle)<90){
			motor[leftWheel] = 10;												//and we stop the motors and exit
			motor[rightWheel] = -10;
		}
		if(abs(compassAngle)>90){
			motor[leftWheel] = -10;
			motor[rightWheel] = 10;
		}
	}
}

void turnright(int compassTarget) {
	compassAngle = 0;											//TURNING CODE
	nCompassHeading  = SensorValue[compass];
	compassOrigin = nCompassHeading;
	while(abs(compassAngle)!=compassTarget){
		nCompassHeading = SensorValue[compass];
		compassAngle = abs(compassOrigin - nCompassHeading);
		if(abs(compassAngle)>90){												//Might need testing, if does not work, switch '<' with '>' and '>' with '<' in if statements
			motor[leftWheel] = 10;												//and we stop the motors and exit
			motor[rightWheel] = -10;
		}
		if(abs(compassAngle)<90){
			motor[leftWheel] = -10;
			motor[rightWheel] = 10;
		}
		else {
			motor[leftWheel] = 0;
			motor[rightWheel] = 0;
		}
	}
}

float strengthLeft(){
	int ac1,ac2,ac3,ac4,ac5 = 0;			// reading of all sensors to compute "strength"
	float s;											  	// strenght value

	HTIRS2readAllACStrength(irLeft, ac1, ac2, ac3, ac4, ac5 ); // reading the strength of all the sensors of the left beacon
	s = ac1+ac2+ac3+ac4+ac5;

	return(s);												// return the strength
}


float strengthRight(){
	int ac1,ac2,ac3,ac4,ac5 = 0;			// reading of all sensors to compute "strength"
	float s;

	HTIRS2readAllACStrength(irRight, ac1, ac2, ac3, ac4, ac5 ); // reading the strength of all the sensors of the left beacon
	s = ac1+ac2+ac3+ac4+ac5;

	return(s);
}


void kindOfAllOfAutonomous() // program to go to the IR beacon and drop the block and get on the bridge
{
	int leftWheelPwr = 0;
	int rightWheelPwr = 0;
	float sL, sR;											  // strenght left and right

motor[slide] = 100;
		wait1Msec(1500); //CALIBRATE
		motor[slide] = 0;
	motor[leftWheel] = 30;						// move forward
	motor[rightWheel] = 30;


	sL = strengthLeft();
	sR = strengthRight();

	while(sL/sR<2.0 && sL/sR>0.5 ){			// if the strength are within a factor of 2 of each other
		sL = strengthLeft();
		sR = strengthRight();
	}

	if(sL>sR)					// see which side the IR is...
	{									// it is on the left!
		while(HTIRS2readACDir(irLeft) != 5) // while we're not in front of the beacon.
		{
			sL = USreadDist(sonarLeft);
			if(sL<50){
				motor[leftWheel]  = 30+ 0.5*(20-sL) ;		// try to keep 20cm distance
				motor[rightWheel] = 30- 0.5*(20-sL) ;
			}
		}
		// we should now be in front of the beacon and the beacon is on the left

		turnleft(55);
		motor[leftWheel] = 15;
		motor[rightWheel] = 15;
		wait1Msec(750); //CALIBRATE
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
		motor[block] = -100;
		wait1Msec(3000);
		motor[block] = 0;
		motor[leftWheel] = -15;
		motor[rightWheel] = -15;
		wait1Msec(750); //CALIBRATE same as above
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
		motor[slide] = -100;
		wait1Msec(1500);
		motor[slide] = 0;
		turnright(55);
		while(SensorValue[sonarLeft]<35){ //CALIBRATE THE AMOUNT OF CENTIMETERS
			motor[leftWheel] = -15;
			motor[rightWheel] = -15;
		}
		turnleft(55);
		float cs = 0;
		short nRawValues[4];
		while(cs<3.5){
			getColorSensorData(color, colorAtoD,&nRawValues[0]);
			cs = (float)(nRawValues[0]+nRawValues[1]+nRawValues[2])/(3.0*nRawValues[3]);
		}
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
		turnleft(55);
		motor[leftWheel] = 60;
		motor[rightWheel] = 60;
		wait1Msec(3000);
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
	}
	else	// the beacon is on the right
	{
		while(HTIRS2readACDir(irRight) != 5) // while we're not in front of the beacon.
		{
			sR = USreadDist(sonarRight);
			if(sR<50){ 													//CALIBRATE
				motor[leftWheel]  = 30- 0.5*(20-sL) ;
				motor[rightWheel] = 30+ 0.5*(20-sL) ;
			}
		}
		turnright(55);
		motor[leftWheel] = 15;
		motor[rightWheel] = 15;
		wait1Msec(750); //CALIBRATE...kind of
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
		motor[block] = -100;
		wait1Msec(3000);
		motor[block] = 0;
		motor[leftWheel] = -15;
		motor[rightWheel] = -15;
		wait1Msec(55); //CALIBRATE same as above
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
		motor[slide] = -100;
		wait1Msec(1500);
		motor[slide] = 0;
		turnleft(55);
		while(SensorValue[sonarRight]<35){ // Calibrate
			motor[leftWheel] = -30;
			motor[rightWheel] = -30;
		}
		turnright(55);
		float cs = 0;
		short nRawValues[4];
		while(cs<3.5){
			getColorSensorData(color, colorAtoD,&nRawValues[0]);
			cs = (float)(nRawValues[0]+nRawValues[1]+nRawValues[2])/(3.0*nRawValues[3]);
		}
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
		turnright(55);
		motor[leftWheel] = 60;
		motor[rightWheel] = 60;
		wait1Msec(3000);
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;

	}

	//we are done...

}


task main()
{
kindOfAllOfAutonomous();
}
