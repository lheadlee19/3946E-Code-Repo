#pragma config(Sensor, dgtl1,  leftDriveQuad,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightDriveQuad, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  liftQuad,       sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  claw,           sensorDigitalOut)
#pragma config(Sensor, dgtl8,  driveToLiftPTO, sensorDigitalOut)
#pragma config(Sensor, dgtl9,  lock,           sensorDigitalOut)
#pragma config(Motor,  port2,           ptoLeft,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           leftDriveOut,  tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightLift,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightDriveIn,  tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftDriveIn,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           leftLift,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           rightDriveOut, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           ptoRight,      tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"//Main competition background code...do not modify!
#include "3946E Beast Mode 1-10-17 Function Library.c"
#include "3946E Beast Mode 1-10-17 LCD Code.c"
#include "3946E Beast Mode 1-10-17 Auton Library.c"

int auton;

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton() {

	auton = LCDSelect();

}


task autonomous() {

	PTOFlip("Drive");
	PTOFlip("Unlock");

	switch(auton){
	case 1://No Autonomous
		//No Autonomous
		break;
	case 2://Red Pole Main
		redPoleMain();
		break;
	case 3://Red Pole Alt
		redPoleAlt();
		break;
	case 4://Red Load Main
		redLoadMain();
		break;
	case 5://Red Load Alt
		redLoadAlt();
		break;
	case 7://Blue Pole Main
		bluePoleMain();
		break;
	case 8://Blue Pole Alt
		bluePoleAlt();
		break;
	case 9://Blue Load Main
		blueLoadMain();
		break;
	case 10://Blue Load Alt
		blueLoadAlt();
		break;
	case 11://Programming
		programmingSkills();
		break;
	}

}


task usercontrol() {

	PTOFlip("Unlock");
	PTOFlip("Drive");

	while(true){
		driveControl();
		liftControl();
		intakeControl();
		pneumaticControl();
	}

}