#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,     HTServo)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFL,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBR,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorShoulder, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorElbow,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_3,    servoWristL,    tServoNormal)
#pragma config(Servo,  srvo_S1_C4_4,    servoHandL,    tServoNormal)
#pragma config(Servo,  srvo_S1_C4_5,    servoWristR,    tServoNormal)
#pragma config(Servo,  srvo_S1_C4_6,    servoHandR,    tServoNormal)
//*Motor configurations on robot may not be same as motor names!!*//

#include "JoystickDriver.c"

task main()

{
	//Initialize variables
   /*float xyPos[2]={14.75,15.5};//target (x,y) position
 	 float l1=14.75;//length of arm1
   float l2=15.5;//length of arm2
 	 float c2=(float)(pow(xyPos[0],2)+pow(xyPos[1], 2)-pow(l1,2)-pow(l2,2))/(2*l1*l2);
   float s2=(float)sqrt(1-pow(c2, 2s);
   float theta2=(float)(acos((pow(xyPos[0], 2)+pow(xyPos[1],2)-pow(l1, 2)-pow(l2,2))/(2*l1*l2)))*(180/PI);//arm1 target angle
   float theta1=(float)(sin((xyPos[1]*(l1+l2*c2)-xyPos[0]*l2*s2)/(pow(xyPos[0],2)+pow(xyPos[1],2))))*(180/PI); //arm2 target angle
   float theta3=-(theta2+theta1);
   */
   //int theta1;
   //int theta2;
   //int theta3;
   float servoWrist1=145;
   float servoWrist2=90;
   bool clawOpen=true;

	 const int threshold = 30;
	 const int threshold2 = 20;
	 float speed=1; //Regulates power to motors//
	 int dir=0;
	 //Main Loop
	 while(true){
	  waitForStart();
    getJoystickSettings(joystick);
    //20% power to motors
	  //nxtDisplayCenteredTextLine(1,"theta1:%f",theta1);
	  //nxtDisplayCenteredTextLine(2,"theta2:%f",theta2);
    if(joy1Btn(4)&&speed!=.2){
    	while(joy1Btn(4)){
	    	speed=.2;
	    }
    	PlaySound(soundDownwardTones);
    }
    //Full power to motors
    else if(joy1Btn(3)&&speed!=1){
    	while(joy1Btn(3)){
    		speed=1;
    	}
    	PlaySound(soundFastUpwardTones);
    }

    //Rotate
    if(abs(joystick.joy1_x2)>threshold){
    	motor[motorFL] = joystick.joy1_x2*speed;
      motor[motorFR] = -joystick.joy1_x2*speed;
      motor[motorBR] = -joystick.joy1_x2*speed;
      motor[motorBL] = joystick.joy1_x2*speed;
    }
    //Diagonal Forward-Right and Back-Left
    else if(abs(joystick.joy1_y1)>threshold2&&abs(joystick.joy1_x1)>threshold2&&(joystick.joy1_x1*joystick.joy1_y1)>0){
     	motor[motorFL] = joystick.joy1_y1*speed;
      motor[motorFR] = 0;
      motor[motorBR] = 0;
      motor[motorBL] = -joystick.joy1_y1*speed;
    }
    //Diagonal Forward-Left and Back-Right
    else if(abs(joystick.joy1_y1)>threshold2&&abs(joystick.joy1_x1)>threshold2&&(joystick.joy1_x1*joystick.joy1_y1)<0){
      motor[motorFL] = 0;
      motor[motorFR] = -joystick.joy1_y1*speed;
      motor[motorBR] = joystick.joy1_y1*speed;
      motor[motorBL] = 0;
    }
    //Forwards/Backwards
    else if(abs(joystick.joy1_y1)>threshold){
    	motor[motorFL] = joystick.joy1_y1*speed;
      motor[motorFR] = -joystick.joy1_y1*speed;
      motor[motorBR] = joystick.joy1_y1*speed;
      motor[motorBL] = -joystick.joy1_y1*speed;
    }
    //Left/Right
    else if(abs(joystick.joy1_x1)>threshold){
    	motor[motorFL] = joystick.joy1_x1*speed;
      motor[motorFR] = joystick.joy1_x1*speed;
      motor[motorBR] = -joystick.joy1_x1*speed;
      motor[motorBL] = -joystick.joy1_x1*speed;
      //Rotate while driving------------------------------------------------------//
      if(joystick.joy1_x2>threshold){																							//
      	dir=abs(joystick.joy1_x1)/joystick.joy1_x1;																//
      	motor[motorBL] = (joystick.joy1_x1-(joystick.joy1_x2*dir))*speed;					//
      	motor[motorBR] = (joystick.joy1_x1-(joystick.joy1_x2*dir))*speed;					//
      }																																						//
      else if(joystick.joy1_x2<-threshold){																				//
      	dir=abs(joystick.joy1_x1)/joystick.joy1_x1;																//
      	motor[motorFR] = (joystick.joy1_x1-(abs(joystick.joy1_x2)*dir))*speed;		//
      	motor[motorFL] = (joystick.joy1_x1-(abs(joystick.joy1_x2)*dir))*speed;		//
      }																																						//
      //--------------------------------------------------------------------------//
    }
    //Stop motors
    else{
    	motor[motorFL] = 0;
      motor[motorFR] = 0;
      motor[motorBR] = 0;
      motor[motorBL] = 0;
    }
    //JOYSTICK 2 MAPPINGS//

    /*/////////////////////////////////////////////InverseKinematicsSolver///////////////////////////////////////////////////////
    if(joy2Btn(4)){
			xyPos[0]=l1+l2;
			xyPos[1]=0;
 		 	c2=(float)(pow(xyPos[0],2)+pow(xyPos[1], 2)-pow(l1,2)-pow(l2,2))/(2*l1*l2);
  	 	s2=(float)sqrt(1-pow(c2, 2));
  	 	theta2=(float)(acos((pow(xyPos[0], 2)+pow(xyPos[1],2)-pow(l1, 2)-pow(l2,2))/(2*l1*l2)))*(180/PI);//arm1 target angle
  	 	theta1=(float)(sin((xyPos[1]*(l1+l2*c2)-xyPos[0]*l2*s2)/(pow(xyPos[0],2)+pow(xyPos[1],2))))*(180/PI); //arm2 target angle
  	 	theta3=-(theta2+theta1);
 	  	nxtDisplayCenteredTextLine(1,"yes!");
 	  }*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	  if(joystick.joy2_y1>threshold){
 	  	servoWrist1+=.1;
 	  	servoWrist2-=.1;
 		}
 		else if(joystick.joy2_y1<-threshold){
 			servoWrist1-=.1;
 			servoWrist2+=.1;
 		}
 	  if(joy2Btn(1)){
 	  	while(joy2Btn(1)){
	 	  }
	 	  clawOpen=!clawOpen;
 		}
 		if(joy2Btn(5)){
	 		motor[motorElbow]=-80;
	 	}
	 	else if(joy2Btn(7)){
	 		motor[motorElbow]=80;
	 	}
	 	else{
	 		motor[motorElbow]=0;
	 	}
	 	if(joy2Btn(6)){

	 		motor[motorShoulder]=-40;
	 	}
	 	else if(joy2Btn(8)){
	 		motor[motorShoulder]=40;
	 	}
	 	else{
	 		motor[motorShoulder]=0;
	 	}
 		///////////////Servo Updates///////////////////////////////////////////////////
	 	//theta1=nMotorEncoder[motorShoulder];
	 	//theta2=nMotorEncoder[motorElbow];
	 	//theta3=-(theta1+theta2);
 		servoTarget[servoWristR]=servoWrist1;
 		servoTarget[servoWristL]=servoWrist2;
 		if(clawOpen){
 			servoTarget[servoHandR]=90;
 			servoTarget[servoHandL]=150;
 		}
 		else{
 			servoTarget[servoHandR]=356;
 			servoTarget[servoHandL]=-360;
 		}
 		///////////////////////////////////////////////////////////////////////////////
 	}
}
