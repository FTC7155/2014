#pragma config(Hubs,  S3, HTMotor,  HTServo,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     controller,     sensorNone)
#pragma config(Sensor, S2,     color,          sensorCOLORFULL)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S3_C1_1,     leftKnot,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C1_2,     rightKnot,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C3_1,     leftWheel,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C3_2,     rightWheel,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S3_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S3_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S3_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S3_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C2_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S3_C4_1,    servo7,               tServoNone)
#pragma config(Servo,  srvo_S3_C4_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S3_C4_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S3_C4_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S3_C4_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S3_C4_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-sensormux.h"  // just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"

void MissionImpossible()
{
  //        100 = Tempo
  //          6 = Default octave
  //    Quarter = Default note length
  //        10% = Break between notes
  //
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  988,    7); wait1Msec(  75);  // Note(E, Duration(32th))
  PlayTone( 1047,    7); wait1Msec(  75);  // Note(F, Duration(32th))
  PlayTone( 1109,    7); wait1Msec(  75);  // Note(F#, Duration(32th))
  PlayTone( 1175,    7); wait1Msec(  75);  // Note(G, Duration(32th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(  880,  108); wait1Msec(1200);  // Note(D, Duration(Half))
  PlayTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(  831,  108); wait1Msec(1200);  // Note(C#, Duration(Half))
  PlayTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(  784,  108); wait1Msec(1200);  // Note(C, Duration(Half))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone(  932,   14); wait1Msec( 150);  // Note(A#5, Duration(16th))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
  return;
}

task main()
{
	while(true){
	motor[leftWheel] = 50;
	motor[rightWheel] = 50;
	}
}