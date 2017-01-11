const unsigned int trueSpeed[128] =
{
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127
};

bool lockMode = false;
bool liftMode = false;
int threshold = 10;
int speedLeft;
int speedRight;

bool autoLaunch = true;
int liftTicks;

float liftKp = 2;
float pLift;
int liftError = 0;
int pMax = 127;

//SETSPEED FUNCTION
void setSpeed(char* motorName,int speed){

	if(speed > 127) speed = 127;
	if(speed < -127) speed = -127;

	int absSpeed = trueSpeed[abs(speed)]*(speed/abs(speed+0.0001));

	if(motorName == "ptoRight") motor[ptoRight] = absSpeed;
	else if(motorName == "rightDriveOut") motor[rightDriveOut] = absSpeed;
	else if(motorName == "rightLift") motor[rightLift] = absSpeed;
	else if(motorName == "rightDriveIn") motor[rightDriveIn] = absSpeed;
	else if(motorName == "leftDriveIn") motor[leftDriveIn] = absSpeed;
	else if(motorName == "leftLift") motor[leftLift] = absSpeed;
	else if(motorName == "leftDriveOut") motor[leftDriveOut] = absSpeed;
	else if(motorName == "ptoLeft") motor[ptoLeft] = absSpeed;

}

//DRIVEMOTORS FUNCTION
void driveMotors(int speed){

	if(SensorValue[driveToLiftPTO] == 0){
		setSpeed("ptoLeft",speed);
		setSpeed("leftDriveIn",speed);
		setSpeed("leftDriveOut",speed);
		setSpeed("ptoRight",speed);
		setSpeed("rightDriveIn",speed);
		setSpeed("rightDriveOut",speed);
	}
	else{
		setSpeed("leftDriveIn",speed);
		setSpeed("leftDriveOut",speed);
		setSpeed("rightDriveIn",speed);
		setSpeed("rightDriveOut",speed);
	}

}

//LEFTDRIVEMOTORS FUNCTION
void leftDriveMotors(int speed){

	if(SensorValue[driveToLiftPTO] == 0){
		setSpeed("leftDriveIn",speed);
		setSpeed("leftDriveOut",speed);
		setSpeed("ptoLeft",speed);
	}
	else{
		setSpeed("leftDriveIn",speed);
		setSpeed("leftDriveOut",speed);
	}

}

//RIGHTDRIVEMOTORS FUNCTION
void rightDriveMotors(int speed){

	if(SensorValue[driveToLiftPTO] == 0){
		setSpeed("rightDriveIn",speed);
		setSpeed("rightDriveOut",speed);
		setSpeed("ptoRight",speed);
	}
	else if(SensorValue[driveToLiftPTO] == 1){
		setSpeed("rightDriveIn",speed);
		setSpeed("rightDriveOut",speed);
	}

}

//LIFTMOTORS FUNCTION
void liftMotors(int speed){

	if(liftMode){
		setSpeed("leftLift",-speed);
		setSpeed("rightLift",-speed);
		setSpeed("ptoLeft",speed);
		setSpeed("ptoRight",speed);
	}
	else{
		setSpeed("leftLift",-speed);
		setSpeed("rightLift",-speed);
	}

}

//PTOFLIP FUNCTION
void PTOFlip(char* PTOSet){

	if(PTOSet == "Drive"){
		SensorValue[driveToLiftPTO] = 0;
		liftMode = false;
	}
	else if(PTOSet == "Lift"){
		SensorValue[driveToLiftPTO] = 1;
		liftMode = true;
	}
	else if(PTOSet == "Lock"){
		SensorValue[lock] = 0;
		lockMode = true;
	}
	else if(PTOSet == "Unlock"){
		SensorValue[lock] = 1;
		lockMode = false;
	}

}

//DRIVECONTROL FUNCTION
void driveControl(){

	speedLeft = vexRT[Ch3];
	speedRight = vexRT[Ch2];

	if(speedLeft > threshold || speedLeft < threshold){
		leftDriveMotors(speedLeft);
	}
	else{
		leftDriveMotors(0);
	}
	if(speedRight > threshold || speedRight < threshold){
		rightDriveMotors(speedRight);
	}
	else{
		rightDriveMotors(0);
	}

}

//LIFTHOLDFUNCTION
void liftHold(){

	liftError = liftTicks - (SensorValue[liftQuad]);

	pLift = (liftKp * liftError);

	if((pLift > 0) && (pLift > pMax)) pLift = pMax;
	else if((pLift < 0) && (pLift < -(pMax))) pLift = -(pMax);

	liftMotors(pLift);

	wait1Msec(5);

}

//LIFTCONTROL FUNCTION
void liftControl(){

	if(liftMode){
		if(vexRT[Btn6U] == 1){
			setSpeed("leftLift",-127);
			setSpeed("rightLift",-127);
			setSpeed("ptoLeft",127);
			setSpeed("ptoRight",127);
			liftTicks = SensorValue[liftQuad]+20;
		}
		else if(vexRT[Btn6D] == 1){
			setSpeed("leftLift",127);
			setSpeed("rightLift",127);
			setSpeed("ptoLeft",-127);
			setSpeed("ptoRight",-127);
			liftTicks = SensorValue[liftQuad]-3;
		}
		else{
			if(SensorValue[liftQuad] > 10){
				liftHold();
			}
			else{
				setSpeed("leftLift",0);
				setSpeed("rightLift",0);
				setSpeed("ptoLeft",0);
				setSpeed("ptoRight",0);
			}
		}
		}else{
		if(vexRT[Btn6U] == 1){
			setSpeed("leftLift",-127);
			setSpeed("rightLift",-127);
			liftTicks = SensorValue[liftQuad]+20;
		}
		else if(vexRT[Btn6D] == 1){
			setSpeed("leftLift",60);
			setSpeed("rightLift",60);
			if(liftTicks < 0) liftTicks = 0;
			else liftTicks = SensorValue[liftQuad]-7;
		}
		else{
			if(SensorValue[liftQuad] > 10){
				liftHold();
			}
			else{
				setSpeed("leftLift",0);
				setSpeed("rightLift",0);
			}
		}
	}
}

//PNEUMATICCONTROL FUNCTION
void pneumaticControl(){

	if((vexRT[Btn5UXmtr2] == 1 || vexRT[Btn7L] == 1) && liftMode) PTOFlip("Drive");
	if((vexRT[Btn5DXmtr2] == 1 || vexRT[Btn7R] == 1) && !liftMode) PTOFlip("Lift");
	if((vexRT[Btn6UXmtr2] == 1 || vexRT[Btn8L] == 1) && !lockMode) PTOFlip("Lock");
	if((vexRT[Btn6DXmtr2] == 1 || vexRT[Btn8R] == 1) && lockMode) PTOFlip("Unlock");

}

//INTAKECONTROL FUNCTION
void intakeControl(){

	if(vexRT[Btn8DXmtr2] == 1) autoLaunch = !autoLaunch;

	if(vexRT[Btn8UXmtr2] == 1) SensorValue[liftQuad] = 0;

	if(autoLaunch){
		if(SensorValue[liftQuad] >= 95) SensorValue[claw] = 0;
	}

	if(vexRT[Btn5U] == 1){
		SensorValue[claw] = 1;
	}
	else if(vexRT[Btn5D] == 1){
		SensorValue[claw] = 0;
	}

}

//PDRIVE FUNCTION
void pDrive (char* direction, int ticks, float pMax){ // pLoop for distance

	float driveKp = 1.2;
	float pMin = 30;
	float driveKi = 0.001;
	SensorValue[rightDriveQuad] = 0;
	SensorValue[leftDriveQuad] = 0;

	float pDrive;
	int counter = 0;
	int time;
	int totalTime = 0;
	int error = 0;
	float integral = 0;

	int side = 0;
	if(direction == "sRight") side = 1;
	else if(direction == "sLeft") side = -1;
	else if(direction == "right") side = 2;
	else if(direction == "left") side = -2;

	if(side == 0){ //both sides

		time = 400;

	}
	else if(side == 1){//strafe right side

		time = 200;

	}
	else if(side == -1){//strafe left side

		time = 200;

	}
	else if(side == 2){//right side

		time = 200;

	}
	else if(side == -2){//left side

		time = 200;

	}


	while(counter < 15 && totalTime < time){

		integral+=error;

		if(side == 0){ //both sides

			driveKp = .1;
			driveKi = 0;
			error = ticks - ((SensorValue[rightDriveQuad]+SensorValue[leftDriveQuad])/2);

		}
		else if(side == 1){//strafe right side

			driveKp = 4;
			driveKi = .001;
			error = ticks - (SensorValue[rightDriveQuad]);

		}
		else if(side == -1){//strafe left side

			driveKp = 4;
			driveKi = .001;
			error = ticks - (SensorValue[leftDriveQuad]);

		}
		else if(side == 2){//right side

			driveKp = 4;
			driveKi = .001;
			error = ticks - ((SensorValue[leftDriveQuad]-SensorValue[rightDriveQuad])/2);

		}
		else if(side == -2){//left side

			driveKp = 4;
			driveKi = .001;
			error = ticks - ((SensorValue[rightDriveQuad]-SensorValue[leftDriveQuad])/2);

		}

		if(abs(error) < 6){

			counter++;

		}
		else{

			counter = 0;

		}

		pDrive = (driveKp * error) + (integral * driveKi);

		if((pDrive > 0) && (pDrive > pMax)){

			pDrive = pMax;//75 motor value

		}
		else if((pDrive < 0) && (pDrive < -(pMax))){

			pDrive = -(pMax);

		}
		else if((pDrive > 0) && (pDrive < pMin)){
			pDrive = pMin;
		}
		else if((pDrive < 0) && (pDrive > -(pMin))){

			pDrive = -(pMin);

		}

		if(side == 0){

			driveMotors(pDrive);

		}
		else if(side == 1){

			rightDriveMotors(pDrive);

		}
		else if(side == -1){

			leftDriveMotors(pDrive);

		}
		else if(side == 2){

			leftDriveMotors(pDrive);
			rightDriveMotors(-pDrive);

		}
		else if(side == -2){

			leftDriveMotors(-pDrive);
			rightDriveMotors(pDrive);

		}

		totalTime++;

		wait1Msec(25);


	}

	driveMotors(0);

}
