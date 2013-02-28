#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,     none)
#pragma config(Motor,  mtr_S1_C1_1,     driveTrainL, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     armL,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     armR,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     intake,      tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     driveTrainR, tmotorNormal, openLoop)


task main()
{
	const double armRatio = 1/18;
	const int threshold = 30;
	bool intake = false;
	while(true){
		getJoystickSettings(joystick);
		if(joy1Btn(5)){
			motor[armL] = -100;
			motor[armR] = -100;
		}
		else if(joy1Btn(6)){
			motor[armL] = 100;
			motor[armR] = 100;
		}
		else{
			motor[armL] = 0;
			motor[armR] = 0;
		}
		if(joy1Btn(1)){
			while(joy1Btn(1)){
			}
			intake=!intake;
		}
		if(abs(joystick.joy1_y1)>threshold){
			motor[driveTrainL] = joystick.joy1_y1*.5;
		}
		else{
			motor[driveTrainL] = 0;
		}
		if(abs(joystick.joy1_y2)>threshold){
			motor[driveTrainR] = joystick.joy1_y2*.5;
		}
		else{
			motor[driveTrainR] = 0;
		}
		if(intake){
			motor[intake] = 100;
		}
		else{
			motor[intake] = 0;
		}
	}
}
