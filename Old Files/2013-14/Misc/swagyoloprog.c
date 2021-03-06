#pragma config(Sensor, S1,     touch,          sensorTouch)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          motor2,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          motor1,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true)
	{
		motor[motor1] = 100;
		motor[motor2] = 100;

		while(SensorValue[sonar]<25)
		{
			motor[motor1] = -100;
			motor[motor2] = -100;
			PlayImmediateTone(1500, 100);
			wait1Msec(3000);
			motor[motor1] = -50;
			motor[motor2] = 50;
			wait1Msec(750);
		}
		while(SensorValue[touch]==1)
			{
				motor[motor1] = 100;
				motor[motor2] = 100;
				PlayImmediateTone(1500, 100);
				wait1Msec(3000);
				motor[motor1] = -50;
				motor[motor2] = 50;
				wait1Msec(750);
			}
	}
}
