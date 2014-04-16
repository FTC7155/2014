#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     color,          sensorCOLORFULL)
#pragma config(Sensor, S3,     compass,        sensorI2CHiTechnicCompass)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     slide,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     block,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftWheel,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     rightWheel,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     tail,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-sensormux.h"	// just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-ultrasound.h"
#include "JoystickDriver.c"								// for the waitForStart() command.

const tMUXSensor irLeft = msensor_S4_3;		// configuring the IR and sonar sensor over the SMUX.
const tMUXSensor irRight = msensor_S4_2;
const tMUXSensor sonarLeft = msensor_S4_4;
const tMUXSensor sonarRight = msensor_S4_1;


task slide_up(){
	motor[slide] = 100;
	wait1Msec(4500); //CALIBRATE
	motor[slide] = 0;
}


task slide_down(){
	motor[slide] = -100;
	wait1Msec(3000); //CALIBRATE
	motor[slide] = 0;
}


void turn (float angle){

	motor[leftWheel] = -sgn(angle)*15;
	motor[rightWheel] = sgn(angle)*15;
	wait10Msec(2.42*abs(angle)); //used to be 2.42
	motor[leftWheel] = 0;
	motor[rightWheel] = 0;

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


void kindOfAllOfAutonomous() 					// program to go to the IR beacon and drop the block and get on the bridge
{

	float sL, sR;											  // strenght left and right

	StartTask(slide_up);

	motor[leftWheel] = 25;							// move forward
	motor[rightWheel] = 25;

	sL = strengthLeft();								// compute strengths of IR sensors
	sR = strengthRight();

	while((float)sL/(float)sR<4.0 && (float)sL/(float)sR>0.25 ){			// if the strength are within a factor of 2 of each other
		sL = strengthLeft();
		sR = strengthRight();
	}


	if(sL>sR)					// see which side the IR is...
	{									// it is on the left!

		while(HTIRS2readACDir(irLeft) != 5) // while we're not in front of the beacon.
		{
			sL = USreadDist(sonarLeft);
			if(sL<50){
				motor[leftWheel]  = 25+ 0.5*(40-sL) ;		// try to keep 20cm distance
				motor[rightWheel] = 25- 0.5*(40-sL) ;
			}
		}

		motor[leftWheel] = 0;
		motor[rightWheel] = 0;


		// we should now be in front of the beacon and the beacon is on the left



		turn(-90.0);			// turn left

		//motor[leftWheel] = 15; 			// get closer to basket
		//motor[rightWheel] = 15;
		//wait1Msec(750); //CALIBRATE
		//motor[leftWheel] = 0;
		//motor[rightWheel] = 0;

		motor[block] = -100;			// spit it out...
		wait1Msec(1000);
		motor[block] = 0;

		//move back a bit...

		motor[leftWheel] = - 25;
		motor[rightWheel] = -25;
		wait1Msec(250); //CALIBRATE same as above
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;

		StartTask(slide_down);

		turn(90);								//turn right

		sL = USreadDist(sonarLeft);
		while(sL<200){
			motor[leftWheel]  = -25- 0.5*(37-sL) ;		// try to keep 20cm distance
			motor[rightWheel] = -25+ 0.5*(37-sL) ;
			sL = USreadDist(sonarLeft);
		}

		wait1Msec(200);

		motor[leftWheel] = 0;		// stop
		motor[rightWheel] = 0;

		turn(-90);						// turn left and go for the line...

		motor[leftWheel] = 25; 	//move forward
		motor[rightWheel] = 25;

		float cs = 0;					// find the line...
		short nRawValues[4];
		while(cs<5){                    //THIS IS THE THRESHOLD TO CHANGE IF THE FIELD IS TOO LIGHT!!!!! IT'S OVER HERE!!!!!
			getColorSensorData(color, colorAtoD,&nRawValues[0]);
			cs = (float)(nRawValues[0]+nRawValues[1]+nRawValues[2])/(3.0*nRawValues[3]);
		}
		motor[leftWheel] = 0;		// stop
		motor[rightWheel] = 0;

		turn(90);								// turn right

		motor[leftWheel] = 25;
		motor[rightWheel] = 25;
		wait1Msec(3600);				//CALIBRATE
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;


	}
	else	// the beacon is on the right
	{

		while(HTIRS2readACDir(irRight) != 5) // while we're not in front of the beacon.
		{
			sR = USreadDist(sonarRight);

			if(sR<50){
				motor[leftWheel]  = 25- 0.5*(37-sR) ;		// try to keep 20cm distance
				motor[rightWheel] = 25+ 0.5*(37-sR) ;
			}
		}

		motor[leftWheel] = 0;
		motor[rightWheel] = 0;


		// we should now be in front of the beacon and the beacon is on the left



		turn(90.0);			// turn right

		//motor[leftWheel] = 15; 			// get closer to basket
		//motor[rightWheel] = 15;
		//wait1Msec(750); //CALIBRATE
		//motor[leftWheel] = 0;
		//motor[rightWheel] = 0;

		motor[block] = -100;			// spit it out...
		wait1Msec(1000);
		motor[block] = 0;

		//move back a bit...

		motor[leftWheel] = -25;
		motor[rightWheel] = -25;
		wait1Msec(250); //CALIBRATE same as above
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;

		StartTask(slide_down);

		turn(-90);								//turn right

		sR = USreadDist(sonarRight);
		while(sR<200){
			motor[leftWheel]  = -25+ 0.5*(37-sR) ;		// try to keep 20cm distance
			motor[rightWheel] = -25- 0.5*(37-sR) ;
			sR = USreadDist(sonarRight);
		}

		wait1Msec(200);

		motor[leftWheel] = 0;		// stop
		motor[rightWheel] = 0;

		turn(90);						// turn left and go for the line...

		motor[leftWheel] = 25; 	//move forward
		motor[rightWheel] = 25;

		float cs = 0;					// find the line...
		short nRawValues[4];
		while(cs<5){
			getColorSensorData(color, colorAtoD,&nRawValues[0]);
			cs = (float)(nRawValues[0]+nRawValues[1]+nRawValues[2])/(3.0*nRawValues[3]);
		}
		motor[leftWheel] = 0;		// stop
		motor[rightWheel] = 0;

		turn(-90);								// turn right

		motor[leftWheel] = 25;
		motor[rightWheel] = 25;
		wait1Msec(3600);				//CALIBRATE
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;



	}

	//we are done...

}

task main()
{

	waitForStart(); 			//take out comment for the FCS.
  motor[slide]=30;
  wait1Msec(100);
	kindOfAllOfAutonomous();


}
