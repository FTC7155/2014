#pragma config(Sensor, S1,     touch,          sensorTouch)
#pragma config(Sensor, S2,     color,          sensorCOLORFULL)
#pragma config(Sensor, S4,     distance,       sensorSONAR)
#pragma config(Motor,  motorA,          rMotor,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          midMotor,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          lMotor,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	nVolume = 4;
	while (true)
	{
	while(SensorValue[touch] == 0 && SensorValue[distance] >=25)
	{
		motor[rMotor] = 75;
		motor[lMotor] = 75;

	}
	while(SensorValue[distance] <25)
{
		motor[rMotor] = -100;
		motor[lMotor] = -100;
		wait1Msec (750);
		motor[rMotor] = 75;
		motor[lMotor] = -75;
		PlayImmediateTone(1500, 100);
		wait1Msec (1300);
}
		while(SensorValue[touch] == 1)
		{
			motor[rMotor] = 75;
			motor[lMotor] = 75;
			wait1Msec (750);
	}
	}
}
