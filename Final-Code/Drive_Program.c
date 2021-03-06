#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     chassisL,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     chassisR,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     scissorL,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     scissorR,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     bucketL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     bucketR,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    trailerServo,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    gateServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    bucketServoL,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    bucketServoR,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/*
Hey ian, remeber that this is max code and disregard anything written.
One time a long time ago, betty and buddy went beihind a house to plant a garden. When they got there, buddy found a giant hole in the ground,
so naturally,  he hopped right in. Betty was a little more weary about it but she eventually went in. Suddenly
they were in another world. Filled with excitement and colors. Buddy started exploring all of the paths and all the new animals. Betty went to
the candy gardens and found a plethora of lolipops and candy trees. They were then devoured by a rock candy monster. es fin.
*/
#include "JoystickDriver.c"

task liftPresets();

void driveChassis(bool t);
void driveBucket(bool t);
void driveLift(bool t);
void initServos();

static float fullFactor = 0.781;
static float halfFactor = 0.391;

task main()
{
	initServos();
	nMotorEncoder[scissorL] = 0;
	nMotorEncoder[scissorR] = 0;
	bool chassisToggle = false;
	bool bucketToggle = false;
	bool liftToggle = false;

	srand(nSysTime);

	StartTask(liftPresets);

	while (true) {
		getJoystickSettings(joystick);
		if (joy1Btn(2)) {
			wait1Msec(200);
			chassisToggle = !chassisToggle;
			PlayImmediateTone((rand() % (800-300)) + 300, 5);
		}

		if (joy2Btn(11)) {
			wait1Msec(200);
			bucketToggle = !bucketToggle;
			PlayImmediateTone((rand() % (800-300)) + 300, 5);
		}

		if (joy2Btn(12)) {
			wait1Msec(200);
			liftToggle = !liftToggle;
			PlayImmediateTone((rand() % (800-300)) + 300, 5);
		}

		driveChassis(chassisToggle);
		driveBucket(bucketToggle);
		driveLift(liftToggle); //maxcode//
	}
}

void driveChassis(bool t)
{
	if (t) {
		motor[chassisL] = joystick.joy1_y1 * fullFactor;
		motor[chassisR] = -joystick.joy1_y2 * fullFactor;
		} else {
		motor[chassisL] = joystick.joy1_y1 * halfFactor;
		motor[chassisR] = -joystick.joy1_y2 * halfFactor;
	}
}

void driveBucket(bool t)
{
	if (t) {
		motor[bucketL] = joystick.joy2_y1 * fullFactor;
		motor[bucketR] = -joystick.joy2_y1 * fullFactor;
		} else {
		motor[bucketL] = joystick.joy2_y1 * halfFactor;
		motor[bucketR] = -joystick.joy2_y1 * halfFactor;
	}
}

void driveLift(bool t)
{
	if (t) {
		motor[scissorL] = joystick.joy2_y2 * fullFactor;
		motor[scissorR] = -joystick.joy2_y2 * fullFactor;
		} else {
		motor[scissorL] = joystick.joy2_y2 * halfFactor;
		motor[scissorR] = -joystick.joy2_y2 * halfFactor;
	}


}

void initServos()
{
	servo[trailerServo] = 127;
	servo[gateServo] = 127;
	servo[bucketServoL] = 127;
	servo[bucketServoR] = 127;
}

task liftPresets()
{
	while(true){
		if (joy2Btn(2)) {
			PlayImmediateTone((rand() % (800-300)) + 300, 100);
			if (nMotorEncoder[scissorL] < 5000) {
				while (nMotorEncoder[scissorL] < 5000) {
					motor[scissorL] = 100;
					motor[scissorR] = -100;
				}
			} else if (nMotorEncoder[scissorL] > 5000) {
				while (nMotorEncoder[scissorL] < 5000) {
					motor[scissorL] = 100;
					motor[scissorR] = -100;
				}
			} else {
				motor[scissorL] = 100;
				motor[scissorR] = -100;
			}
			motor[scissorL] = 0;
			motor[scissorR] = 0;
		}
		wait1Msec(10);
	}
}
