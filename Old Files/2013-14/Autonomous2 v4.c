#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     controller,     sensorNone)
#pragma config(Sensor, S2,     color,          sensorCOLORFULL)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  motorA,          collectMotor,  tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     backSlide,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     tailMotor,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    topLeft,              tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    bottomLeft,           tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_1,    topRight,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    bottomRight,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard!!*//

#include "drivers/hitechnic-sensormux.h"	// just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/hitechnic-compass.h" //added compass smux config -Jonathan
//#include "JoystickDriver.c"

const tMUXSensor irLeft = msensor_S4_1;		// configuring the IR sensor over the SMUX.
const tMUXSensor irRight = msensor_S4_2;
const tMUXSensor compass = msensor_S4_3;

int lhist[200],rhist[200],nsteps,dt;			// used to keep the history of commands
int totrot = 0;														// total accumulated rotation

int compassAngle, nCompassHeading, compassOrigin; //used for turning and configuring compass
bool left;


// These are some standard positions for the arm
void turnleft(int compassTarget) {
	compassAngle = 0;    //TURNING CODE
	nCompassHeading = SensorValue[compass];
	compassOrigin = nCompassHeading;
	while(abs(compassAngle)!=compassTarget){
		compassAngle = abs(compassOrigin - nCompassHeading);
		if(abs(compassAngle)<90){
			motor[leftWheel] = -50;												//and we stop the motors and exit
			motor[rightWheel] = 50;
		}
		if(abs(compassAngle)>90){
			motor[leftWheel] = 50;
			motor[rightWheel] = -50;
		}
	}
}

void turnright(int compassTarget) {
	compassAngle = 0;											//TURNING CODE
	nCompassHeading
	compassOrigin = nCompassHeading;
	while(abs(compassAngle)!=compassTarget){
		compassAngle = abs(compassOrigin - nCompassHeading);
		if(abs(compassAngle)>90){												//Might need testing, if does not work, switch '<' with '>' and '>' with '<' in if statements
			motor[leftWheel] = 50;												//and we stop the motors and exit
			motor[rightWheel] = -50;
		}
		if(abs(compassAngle)<90){
			motor[leftWheel] = -50;
			motor[rightWheel] = 50;
		}
		else {
			motor[leftWheel] = 0;
			motor[rightWheel] = 0;
		}
	}
}

void seek_beacon(){									 //search for IR beacon and stop in front of it...

	int leftReading=0;								// reading of IR position on left side
	int rightReading=0;								// reading of IR position on right side
	int t,r,acc = 0;
	int ac1,ac2,ac3,ac4,ac5 = 0;			// reading of all sensors to compute "strength"
	int strength,speed=0;							// the strength of the IR beacon and the speed of the robot
	int flag = 0;											// will be 1 when the IR beacon is found
	int t0;														// initial time


	SensorType[compass] = sensorI2CCustom; //conf compass
	SensorSubType[compass] = sensorI2CHiTechnicCompass;

	nsteps=0;													// number of steps taken

	t0 = nPgmTime;

	while(!flag)
	{

		HTIRS2readAllACStrength(irLeft, ac1, ac2, ac3, ac4, ac5 ); // reading the strength of all the sensors of the left beacon
		acc = ac1+ac2+ac3+ac4+ac5;
		HTIRS2readAllACStrength(irRight, ac1, ac2, ac3, ac4, ac5 ); // reading the strength of all the sensors of the right beacon
		acc = acc+ac1+ac2+ac3+ac4+ac5;

		strength = 0.75*strength+0.25*acc;						// compute strength and smooth the strength over time

		if(strength<200)										// if stregnth is small we are far away and move fast
			speed = 0.8*speed+0.2*35;
		else																// when we get closer we move slower and we also smooth speed over time
			speed = 0.8*speed+0.2*15;

		// CALIBRATE -- (6,4) are the target values for the distance, but it may need to be calibrated in the real field.

		leftReading	 = HTIRS2readACDir(irLeft)	-5;		// compute error for left and right eyes
		rightReading = HTIRS2readACDir(irRight) -5;
		nCompassHeading = SensorValue[compass];
		totrot += r*t;

		if(leftReading == 0){		//if the errors are zero we reached the target
			left = true;
			turnleft(90); //turn left 90 degrees
			flag = 1;
		}

		}
		if(rightReading == 0) {
			left = false;
			turnright(90);
			flag = 1;
		}
		else {														// we are still searching

			lhist[nsteps] = speed*(t-0.6*r);		// keep a history of our movements commands
			rhist[nsteps] = speed*(t+0.6*r);

			motor[leftWheel]	= lhist[nsteps];	// set the new commands
			motor[rightWheel] = rhist[nsteps];

			nsteps++;														// keep the number of commands steps...
		}
		while(SensorValue[sonar]>10){ //conf later
			motor[leftWheel] = 60;
			motor[rightWheel] = 60;
		}
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
		motor[collectMotor] = -100;
		wait1Msec(3000);

	t0 = nPgmTime-t0;												// how long we needed to get to the target
	dt = t0/nsteps;													// calculate average delay between commands

}

void dropblock(){
	while(SensorValue[sonar]>10){ //conf later
			motor[leftWheel] = 60;
			motor[rightWheel] = 60;
		}
		motor[collectMotor] = -100;
		wait1Msec(3000);
		motor[collectMotor] = 0;
		motor[leftWheel] = -60;
		motor[rightWheel] = -60;
		if(left==true){
			turnright(90);
		}
		if(left==false){
			turnleft(90);
		}
		wait1Msec(1000);
}



void gobackhome(){												// returns to start position by playing back the history of motor commands

	while(--nsteps>=0){											// play back history in reverse
		motor[rightWheel] = -rhist[nsteps];
		motor[leftWheel] = -lhist[nsteps];
		wait1Msec(dt);
	}
	motor[rightWheel] = 0;									// stop motors
	motor[leftWheel] = 0;
}


void lookforline(){												// looks for the white line

	short nRawValues[4];
	float tmp;

	tmp = 0;
	while(SensorValue[sonar]>10){
		motor[leftWheel] = 50;									// move forward
		motor[rightWheel] = 50;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
	if(left==true){
		turnleft(90);
	}
	if(left==false){
		turnright(90);
	}

	while(tmp<3.5){													// keep moving until we find the line...
		getColorSensorData(color, colorAtoD,&nRawValues[0]);
		tmp = (float)(nRawValues[0]+nRawValues[1]+nRawValues[2])/(3.0*nRawValues[3]);
	}

	motor[leftWheel] = 0;										// stop
	motor[rightWheel] = 0;

	if(left==true){
		turnleft(90);
	}
	if(left==false){
		turnright(90);
	}
	motor[leftWheel] = 100;
	motor[rightWheel] = 100;
	wait1Msec(2000);
}



task main()
{

	bSystemLeaveServosEnabledOnProgramStop=false;	 // leaves power on so we are in home position after autonomous period, and so that the robot doesn't just fall down.
	seek_beacon();
	dropblock();
	lookforline();


}