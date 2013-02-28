#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeftFront,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorLeftBack,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     ramp,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arms,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorRightFront,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorRightBack,   tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    clawLeft,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    clawRight,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    rampLock,               tServoStandard)
#pragma config(Sensor, S3,     HTSPB,                sensorI2CCustom9V)
#pragma config(Sensor, S4,     HTSMUX,              sensorI2CCustom)


#include "JoystickDriver.c"
#include "/hitechnic-sensormux.h"
#include "/lego-light.h"
#include "/lego-touch.h"
#include "/hitechnic-superpro.h"

const int threshold = 25,open = 35,closed = 100;
const tMUXSensor LEGOTS = msensor_S4_1;

bool rampLocked,speedToggleOne,speedToggleTwo,touched,weighted;
float speedContOne,speedContTwo;
int clawVal;

void init(){
	//Initiate SuperPro pinout
  HTSPBsetupIO(HTSPB, 0xFF); //Set all digital i/o as outputs

	//Initiate Variables
	rampLocked=speedToggleOne=speedToggleTwo=touched=weighted=false;
	speedContOne=speedContTwo=1;
	clawVal=7;

	//Initiate Motors
	motor[motorLeftFront]=0;
	motor[motorRightFront]=0;
	motor[motorRightFront]=0;
	motor[motorRightBack]=0;
	motor[ramp]=0;
	motor[arms]=0;

	//Initiate Servos
	servo[clawLeft]=clawVal;
	servo[clawRight]=215-clawVal;
	servo[rampLock]=closed;

}

int taskOne=0;

void joystickControllerOne()
{

		getJoystickSettings(joystick);

		//Fine Control
		if(joy1Btn(1)){
			while(joy1Btn(1)){}
			speedToggleOne=!speedToggleOne;
		}
		if(speedToggleOne)
			speedContOne=.5;
		else
			speedContOne=1;

		//Drive Train Control
		if(abs(joystick.joy1_y1)>threshold){
			motor[motorLeftFront]=joystick.joy1_y1*speedContOne;
			motor[motorLeftBack]=joystick.joy1_y1*speedContOne;
		}
		else{
			motor[motorLeftFront]=0;
			motor[motorLeftBack]=0;
		}
		if(abs(joystick.joy1_y2)>threshold){
			motor[motorRightFront]=joystick.joy1_y2*speedContOne;
			motor[motorRightBack]=joystick.joy1_y2*speedContOne;
		}
		else{
			motor[motorRightFront]=0;
			motor[motorRightBack]=0;
		}

		//Ramp Lock
		if(joy1Btn(4))
			rampLocked=!rampLocked;

		//Ramp Control
		if(joy1Btn(6))
			motor[ramp]=50*speedContOne;
		else if(joy1Btn(5))
			motor[ramp]=-75*speedContOne;
		else
			motor[ramp]=0;


		//Update Servos///////
		if(rampLocked)
			servo[rampLock]=open;
		else
			servo[rampLock]=closed;
		//////////////////////
	//}
}

int taskTwo=0;

void joystickControllerTwo()
{

		getJoystickSettings(joystick);

		//LED TEST
		if(joy2Btn(10))
			weighted=true;
		else
			weighted=false;

		//Fine Control
		if(joy2Btn(1)){
			while(joy2Btn(1)){}
			speedToggleTwo=!speedToggleTwo;
		}
		if(speedToggleTwo)
			speedContTwo=.5;
		else
			speedContTwo=1;

		//Arm Controll
		if(joy2Btn(5))
			motor[arms] = -100*speedContTwo;
		else if(joy2Btn(6))
			motor[arms] = 100*speedContTwo;
		else
			motor[arms] = 0;

		//Claw Control
			//Position Control
		if(joy2Btn(4))
			clawVal=7;
		if(joy2Btn(3))
			clawVal=100;
			//Fine Control
		if(joy2Btn(7)&&time1[T1]%10==0)
			clawVal++;
		if(joy2Btn(8)&&time1[T1]%10==0)
			clawVal--;

		//Update Servos//////////////
		servo[clawLeft]=clawVal;
		servo[clawRight]=215-clawVal;
		/////////////////////////////
//	}
}

task main()
{
	init();

	//Hog CPU to ensure tasks start at same time
	//hogCPU();
	ClearTimer(T1);
	while(true){
	  touched = TSreadState(LEGOTS);
	  if(!touched)
	  	PlaySound(soundBlip);

	  //SuperPro LED control
	  if(weighted)
      HTSPBwriteIO(HTSPB, 0x01);
    else
      HTSPBwriteIO(HTSPB, 0x00);

		joystickControllerOne();
		joystickControllerTwo();
	}
	//No longer need CPU power
	//releaseCPU();

	//Main Loop
	while(true){}
}
