#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,     none)
#pragma config(Motor,  mtr_S1_C1_1,     driveTrainR,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     driveTrainL,   tmotorNormal, openLoop, reversed)

#include "JoystickDriver.c"

task main()
{
	const int threshold = 30;
	while(true){
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1)>threshold){
			motor[driveTrainL] = joystick.joy1_y1;
		}
		else{
			motor[driveTrainL] = 0;
		}
		if(abs(joystick.joy1_y2)>threshold){
			motor[driveTrainR] = joystick.joy1_y2;
		}
		else{
			motor[driveTrainR] = 0;
		}
	}
}
