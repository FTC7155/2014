#pragma config(Sensor, S1,     IR1,            sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S2,     IR2,            sensorHiTechnicIRSeeker1200)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

	while(true)
	{
		int sensor1 = SensorValue[IR1];
		int sensor2 = SensorValue[IR2];
		nxtDisplayCenteredTextLine(3, "%d, %d", sensor1, sensor2);
	}


}
