#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeftFront,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorLeftBack,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     ramp,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arms,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorRightFront,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorRightBack,   tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    clawLeft,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    clawRight,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    button,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    button2,               tServoStandard)
#pragma config(Sensor, S3,     LEGOLS,              sensorLightInactive)
#pragma config(Sensor, S4,     HTSMUX,              sensorI2CCustom)


#include "JoystickDriver.c"
#include "/hitechnic-sensormux.h"
#include "/lego-light.h"
#include "/lego-touch.h"
#include "/hitechnic-superpro.h"
#include "/hitechnic-irseeker-v2.h"

#define OPEN 100
#define CLOSED 7
#define BLACK 0
//Field Values of White ADJUST AS NEEDED
#define ARM_UP_WHITE 275
#define WHITE 425

//const tMUXSensor HTIRS2 = msensor_S1_1;

//Movement Functions
void forward(int powerLevel)
{
	motor[motorLeftFront]=powerLevel;
	motor[motorLeftBack]=powerLevel;
	motor[motorRightFront]=powerLevel;
	motor[motorRightBack]=powerLevel;
}

void forwardUntil(int powerLevel,int color)
{
	while(true)
	{
		if(color==0){
			if(SensorValue[LEGOLS]<425)
				break;
	  }
		else{
			if(SensorValue[LEGOLS]>color)
				break;
		}
		forward(powerLevel);
		nxtDisplayCenteredTextLine(1,"%i",SensorValue[LEGOLS]);
	}
}

void reverse(int powerLevel)
{
	motor[motorLeftFront]=-powerLevel;
	motor[motorLeftBack]=-powerLevel;
	motor[motorRightFront]=-powerLevel;
	motor[motorRightBack]=-powerLevel;
}

void reverseUntil(int powerLevel,int color)
{
	while(true)
	{
		if(color==0){
			if(color<425)
				break;
		}
		else{
			if(SensorValue[LEGOLS]>color)
				break;
		}
		reverse(powerLevel);
	}
}

void pivotRight(int powerLevel)
{
	motor[motorLeftFront]=powerLevel;
	motor[motorLeftBack]=powerLevel;
	motor[motorRightFront]=-powerLevel;
	motor[motorRightBack]=-powerLevel;
}

void pivotRightUntil(int powerLevel,int color)
{
	while(true)
	{
		if(color==0){
			if(color<425)
				break;
		}
		else{
			if(SensorValue[LEGOLS]>color)
				break;
		}
		pivotRight(powerLevel);
	}
}

void pivotLeft(int powerLevel)
{
	motor[motorLeftFront]=-powerLevel;
	motor[motorLeftBack]=-powerLevel;
	motor[motorRightFront]=powerLevel;
	motor[motorRightBack]=powerLevel;
}

void pivotLeftUntil(int powerLevel,int color)
{
	while(true)
	{
		if(color==0){
			if(color<425)
				break;
		}
		else{
			if(SensorValue[LEGOLS]>color)
				break;
		}
		pivotLeft(powerLevel);
	}
}

void right(int powerLevel)
{
	motor[motorLeftFront]=powerLevel;
	motor[motorLeftBack]=powerLevel;
	motor[motorRightFront]=0;
	motor[motorRightBack]=0;
}

void rightUntil(int powerLevel,int color)
{
	while(true)
	{
		if(color==0){
			if(color<425)
				break;
		}
		else{
			if(SensorValue[LEGOLS]>color)
				break;
		}
		right(powerLevel);
	}
}

void left(int powerLevel)
{
	motor[motorLeftFront]=0;
	motor[motorLeftBack]=0;
	motor[motorRightFront]=powerLevel;
	motor[motorRightBack]=powerLevel;
}

void leftUntil(int powerLevel,int color)
{
	while(true)
	{
		if(color==0){
			if(color<425)
				break;
		}
		else{
			if(SensorValue[LEGOLS]>color)
				break;
		}
		left(powerLevel);
	}
}

//Claw Functions
void openClaw(){
	servo[clawLeft]=OPEN;
	servo[clawRight]=210-OPEN;
}

void closeClaw(){
	servo[clawLeft]=CLOSED;
	servo[clawRight]=210-CLOSED;
}

//Arm Functions
void armUp(int powerLevel)
{
	motor[arms]=powerLevel;
}

void armDown(int powerLevel)
{
	motor[arms]=-powerLevel;
}

void armUpUntil(int powerLevel,int encoderVal)
{
	while(nMotorEncoder[arms]>encoderVal)
		motor[arms]=powerLevel;
}

void armDownUntil(int powerLevel,int encoderVal)
{
	while(nMotorEncoder[arms]<encoderVal)
		motor[arms]=-powerLevel;
}

void stop()
{
	motor[motorLeftFront]=0;
	motor[motorLeftBack]=0;
	motor[motorRightFront]=0;
	motor[motorRightBack]=0;
	motor[ramp]=0;
	motor[arms]=0;
}

task main()
{
	forward(20);
	wait1Msec(10000);
}
