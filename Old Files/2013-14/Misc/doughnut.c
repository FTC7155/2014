#pragma config(Sensor, S1,     touch,          sensorTouch)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          motor2,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          motor1,        tmotorNXT, PIDControl, encoder)

task main()
{
	int doughnutturn = 0;
		while(true){
			if(SensorValue[touch]==1){
				switch(doughnutturn){
					case 0:
					doughnutturn = 1;
					break;
					case 1:
					doughnutturn = 0;
					break;
					}
				}
			if(doughnutturn == 0)
			{
				motor[motor1] = 100;
				motor[motor2] = 25;

			}
			if(doughnutturn == 1)
			{
				motor[motor1] = 25;
				motor[motor2] = 100;
			}
	}
}
