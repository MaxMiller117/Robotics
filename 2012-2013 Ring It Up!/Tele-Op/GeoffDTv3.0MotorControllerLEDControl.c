#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S2, HTMotor,  none,  none,  none)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeftFront,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorLeftBack,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     ramp,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     arms,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorRightFront,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorRightBack,   tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    clawLeft,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    clawRight,               tServoStandard)
#pragma config(Motor,  mtr_S2_C1_1,     LED,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     LED2,   tmotorNormal, openLoop)
#pragma config(Sensor, S3,     HTSPB,                sensorI2CCustom9V)
#pragma config(Sensor, S4,     HTSMUX,              sensorI2CCustom)


#include "JoystickDriver.c"
#include "/hitechnic-sensormux.h"
#include "/lego-light.h"
#include "/lego-touch.h"
#include "/hitechnic-superpro.h"
#include "/hitechnic-force.h"

#define threshold 25

const tMUXSensor HTFORCE1 = msensor_S4_3;
const tMUXSensor HTFORCE2 = msensor_S4_4;

bool rampLocked,speedToggleOne,speedToggleTwo,touched,weighted;
float speedContOne,speedContTwo;
int clawVal,force1,force2;

void init(){
	//Initiate SuperPro pinout
  //HTSPBsetupIO(HTSPB, 0xFF); //Set all digital i/o as outputs

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

}

void updateSensors()
{
	force1=HTFreadSensor(HTFORCE1);
	force2=HTFreadSensor(HTFORCE2);
}

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

}

void joystickControllerTwo()
{

		getJoystickSettings(joystick);

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
		servo[clawRight]=210-clawVal;
		/////////////////////////////7
}

void debug()
{
	nxtDisplayCenteredTextLine(0,"Force1:%i",force1);
	nxtDisplayCenteredTextLine(1,"Force2:%i",force2);
	nxtDisplayCenteredTextLine(2,"");
	nxtDisplayCenteredTextLine(3,"");
	nxtDisplayCenteredTextLine(4,"");
	nxtDisplayCenteredTextLine(5,"");
	nxtDisplayCenteredTextLine(6,"");
	nxtDisplayCenteredTextLine(7,"");
}

task main()
{
	init();

	ClearTimer(T1);
	while(true){
	  //Update Sensors
		updateSensors();

	  //Weighted Ring Checker
	  if(force1<1000)
	  	force1+=1000;
	 	if(force2<1000)
	 		force2+=1000;
	 	if(force1>1475&&force2>1300)
	 		motor[LED2]=100;
	 	else
	 		motor[LED2]=0;
	  if(force1>1475){
		 	motor[LED]=100;
		}
	 	else if(force2>1460){
	 		motor[LED]=100;
		}
	 	else
	 		motor[LED]=0;

	  //SuperPro LED control for weighted
	  /*if(weighted)
      HTSPBwriteIO(HTSPB, 0x01);
    else
      HTSPBwriteIO(HTSPB, 0x00);*/

    //Joystick Control
		joystickControllerOne();
		joystickControllerTwo();

		debug();
	}
}
