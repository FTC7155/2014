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

task main()
{

motor[leftWheel] = 50;
motor[rightWheel] = 50;
wait1Msec(1000);

}
