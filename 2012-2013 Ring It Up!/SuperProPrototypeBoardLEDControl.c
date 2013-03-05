#pragma config(Sensor, S3,     HTSPB,                sensorI2CCustom9V)

#include "JoystickDriver.c"
#include "/hitechnic-superpro.h"

task main()
{
  HTSPBsetupIO(HTSPB, 0x1);

	while(true){
		getJoystickSettings(joystick);

		if(joy1Btn(1))
  		HTSPBwriteIO(HTSPB,0x01);
		else
  		HTSPBwriteIO(HTSPB,0x00);

	}
}
