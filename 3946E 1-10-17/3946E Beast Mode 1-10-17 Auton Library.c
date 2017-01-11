void flipClaw(){
	SensorValue[claw] = 1;
	wait1Msec(100);
	SensorValue[claw] = 0;
	driveMotors(127);
	wait1Msec(100);
	driveMotors(0);
}

void redPoleMain(){
}

void redPoleAlt(){//Three on fence (red pole and blue load)
	flipClaw();
	setSpeed("leftLift",-127);
	setSpeed("rightLift",-127);
	wait1Msec(950);
	setSpeed("leftLift",-10);
	setSpeed("rightLift",-10);
	wait1Msec(500);
	driveMotors(127);
	wait1Msec(1100);
	driveMotors(0);
	wait1Msec(2000);
	driveMotors(-127);
	wait1Msec(300);
	driveMotors(0);
	wait1Msec(50);
}

void redLoadMain(){
}

void redLoadAlt(){//Cube into near
	driveMotors(-127);
	wait1Msec(2000);
	driveMotors(0);
	wait1Msec(500);
	driveMotors(127);
	wait1Msec(500);
	driveMotors(0);
	wait1Msec(50);
}

void bluePoleMain(){
}

void bluePoleAlt(){//Three on fence (blue pole and red load)
	liftMotors(127);
	wait1Msec(950);
	liftMotors(10);
	wait1Msec(500);
	driveMotors(127);
	wait1Msec(1100);
	driveMotors(0);
	wait1Msec(2000);
	driveMotors(-127);
	wait1Msec(300);
	driveMotors(0);
	wait1Msec(50);
}

void blueLoadMain(){

}

void blueLoadAlt(){//Cube into near
	driveMotors(127);
	wait1Msec(2000);
	driveMotors(0);
	wait1Msec(50);
}

void programmingSkills(){
}
