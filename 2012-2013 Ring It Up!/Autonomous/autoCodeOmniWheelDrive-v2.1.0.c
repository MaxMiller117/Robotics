#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBR,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,        tmotorNormal, openLoop, reversed)
#pragma config(Sensor, S2,     IRSensor,               sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)
#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)

#include "/hitechnic-irseeker-v2.h"

//Global Variables
int threshold=30;
int powerLevel=50;
int dcS1,dcS2,dcS3,dcS4,dcS5;
bool foundSensor=false;

////////////////////Autonomous Ring Placement////////////
void placeRing(){

}

///////////////////////Movement Functions////////////////
void forward(){
	motor[motorFL] = -powerLevel;
  motor[motorFR] = -powerLevel;
  motor[motorBR] = -powerLevel;
  motor[motorBL] = -powerLevel;
}
void reverse(){
	motor[motorFL] = powerLevel;
  motor[motorFR] = powerLevel;
  motor[motorBR] = powerLevel;
  motor[motorBL] = powerLevel;
}
void left(){
	motor[motorFL] = powerLevel;
  motor[motorFR] = -powerLevel;
  motor[motorBR] = powerLevel;
  motor[motorBL] = -powerLevel;
}
void right(){
	motor[motorFL] = -powerLevel;
  motor[motorFR] = powerLevel;
  motor[motorBR] = -powerLevel;
  motor[motorBL] = powerLevel;
}
void rotateLeft(){
	motor[motorFL] = powerLevel;
  motor[motorFR] = -powerLevel;
  motor[motorBR] = -powerLevel;
  motor[motorBL] = powerLevel;
}
void rotateRight(){
	motor[motorFL] = -powerLevel;
  motor[motorFR] = powerLevel;
  motor[motorBR] = powerLevel;
  motor[motorBL] = -powerLevel;
}
void fLeft(){
}
void fRight(){
}
void rLeft(){
}
void rRight(){
}
////////////////////////////////////////////////////////////
/*
void checkForBeacon(){
	while(wait1Msec(1000)){
		rotateLeft();
		if(dcS3>10)
			foundSensor=true;
	}
	while(SensorValue[lightSensor]<50){
		rotateRight();
	}
	while(wait1Msec(1000)){
		rotateRight();
		if(dcS3>10)
			foundSensor=true;
	}
	while(SensorValue[lightSensor]<50){
		rotateLeft();
	}
}*/
//////////////////////////////////////////////////////////

task main()
{
	int lines=0;
	int prevColor=0;
	while(SensorValue[lightSensor]<threshold&&dcS3<10){
		forward();
    HTIRS2readAllDCStrength(IRSensor, dcS1, dcS2, dcS3, dcS4, dcS5);
    nxtDisplayCenteredTextLine(1,"IRSensor: %i",SensorValue[IRSensor]);
	}
	stop();
	if(dcS3>15){
		while(true){
			nxtDisplayCenteredTextLine(1,"IRBeacon Found");
			placeRing();
		}
	}
}
