#include "drivers/hitechnic-sensormux.h"  // just files to make the SMUX work.
#include "drivers/hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"               // the files for the Logitech controller to work by USB to the laptop and then by bluetooth/USB to the NXT, NOT by samantha module.
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
const tMUXSensor irLeft = msensor_S4_1; // configuring the IR sensor over the SMUX.
const tMUXSensor irRight = msensor_S4_2;
task main()
{
while(true)
{
	int	leftEye = HTIRS2readACDir(irLeft);
	int	rightEye = HTIRS2readACDir(irRight);
	eraseDisplay();
	nxtDisplayStringAt(10, 10,"%d, %d", leftEye, rightEye);
}


}
