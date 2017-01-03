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

bool speedMode = true;
bool liftMode = false;
int threshold = 10;
int speedLeft;
int speedRight;

bool autoLaunch = true;

//SETSPEED FUNCTION
void setSpeed(char* motorName,int speed){

	if(speed > 127) speed = 127;
	if(speed < -127) speed = -127;

	int absSpeed = trueSpeed[abs(speed)]*(speed/abs(speed+0.0001));

	if(motorName == "ptoOutRight") motor[ptoOutRight] = absSpeed;
	else if(motorName == "ptoInRight") motor[ptoInRight] = absSpeed;
	else if(motorName == "rightLift") motor[rightLift] = absSpeed;
	else if(motorName == "righTDrive") motor[rightDrive] = absSpeed;
	else if(motorName == "leftDrive") motor[leftDrive] = absSpeed;
	else if(motorName == "leftLift") motor[leftLift] = absSpeed;
	else if(motorName == "ptoInLeft") motor[ptoInLeft] = absSpeed;
	else if(motorName == "ptoOutLeft") motor[ptoOutLeft] = absSpeed;

}

//DRIVEMOTORS FUNCTION
void driveMotors(int speed){

	if(!liftMode){
		setSpeed("ptoOutLeft",speed);
		setSpeed("ptoInLeft",speed);
		setSpeed("leftDrive",speed);
		setSpeed("ptoOutRight",speed);
		setSpeed("ptoInRight",speed);
		setSpeed("rightDrive",speed);
	}
	else{
		setSpeed("leftDrive",speed);
		setSpeed("rightDrive",speed);
	}

}

//LEFTDRIVEMOTORS FUNCTION
void leftDriveMotors(int speed){

	if(!liftMode){
		setSpeed("leftDrive",speed);
		setSpeed("ptoOutLeft",speed);
		setSpeed("ptoInLeft",speed);
	}
	else{
		setSpeed("leftDrive",speed);
	}

}

//RIGHTDRIVEMOTORS FUNCTION
void rightDriveMotors(int speed){

	if(!liftMode){
		setSpeed("rightDrive",speed);
		setSpeed("ptoOutRight",speed);
		setSpeed("ptoInRight",speed);
	}
	else{
		setSpeed("rightDrive",speed);
	}

}

//PTOFLIP FUNCTION
void PTOFlip(char* PTOSet){

	if(PTOSet == "Drive"){
		motor[driveToLiftPTO] = 0;
		liftMode = false;
	}
	else if(PTOSet == "Lift"){
		motor[driveToLiftPTO] = 127;
		liftMode = true;
	}
	else if(PTOSet == "Speed"){
		SensorValue[driveToDrivePTO] = 0;
		speedMode = true;
	}
	else if(PTOSet == "Torque"){
		SensorValue[driveToDrivePTO] = 1;
		speedMode = false;
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

//LIFTCONTROL FUNCTION
void liftControl(){

	if(liftMode){
		if(vexRT[Btn6U] == 1){
			setSpeed("leftLift",127);
			setSpeed("rightLift",127);
			setSpeed("ptoOutLeft",-127);
			setSpeed("ptoInLeft",-127);
			setSpeed("ptoOutRight",-127);
			setSpeed("ptoInRight",-127);
		}
		else if(vexRT[Btn6D] == 1){
			setSpeed("leftLift",-127);
			setSpeed("rightLift",-127);
			setSpeed("ptoOutLeft",127);
			setSpeed("ptoInLeft",127);
			setSpeed("ptoOutRight",127);
			setSpeed("ptoInRight",127);
		}
		else{
			setSpeed("leftLift",0);
			setSpeed("rightLift",0);
			setSpeed("ptoOutLeft",0);
			setSpeed("ptoInLeft",0);
			setSpeed("ptoOutRight",0);
			setSpeed("ptoInRight",0);
		}
	}
	else{
		if(vexRT[Btn6U] == 1){
			setSpeed("leftLift",127);
			setSpeed("rightLift",127);
		}
		else if(vexRT[Btn6D] == 1){
			setSpeed("leftLift",-60);
			setSpeed("rightLift",-60);
		}
		else{
			setSpeed("leftLift",0);
			setSpeed("rightLift",0);
		}
	}

}

//PNEUMATICCONTROL FUNCTION
void pneumaticControl(){

	if(vexRT[Btn5UXmtr2] == 1 && liftMode) PTOFlip("Drive");
	if(vexRT[Btn5DXmtr2] == 1 && !liftMode) PTOFlip("Lift");
	if(vexRT[Btn6UXmtr2] == 1 && !speedMode) PTOFlip("Speed");
	if(vexRT[Btn6DXmtr2] == 1 && speedMode) PTOFlip("Torque");

}

//INTAKECONTROL FUNCTION
void intakeControl(){

	if(vexRT[Btn8UXmtr2] == 1) autoLaunch = !autoLaunch;

	if(autoLaunch){
		if(SensorValue[liftPot] >= 100) SensorValue[claw] = 0;
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

			driveKp = .7;
			driveKi = .001;
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
