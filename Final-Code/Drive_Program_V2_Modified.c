#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C3_1,     roller,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     liftR,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     chassisR,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     chassisL,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     liftL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorI,        tmotorNXT, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    trailerServoL,        tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    trailerServoR,        tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    gateServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    bucketServoL,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    bucketServoR,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task liftLPresets();
task liftRPresets();

void init();
void driveChassis(bool t);
void driveRoller();

static float fullFactor = 0.781;
static float halfFactor = 0.391;
static float liftPower = 0.630;

task main()
{
	nVolume = 4;
	//setup
	bool chassisToggle = false;
	init();
	startTask(liftLPresets);
	startTask(liftRPresets);
	//main drive
	while (true) {
		getJoystickSettings(joystick);
		nxtDisplayTextLine(2, "%d", nMotorEncoder[liftL]);
		nxtDisplayTextLine(4, "%d", nMotorEncoder[liftR]);
		if (joy1Btn(2)) {
			chassisToggle = true;
			playImmediateTone((rand() % (800-300)) + 300, 5);
		}
		if(joy1Btn(3)) {
			chassisToggle = false;
			playImmediateTone((rand() % (800-300)) + 300, 5);
		}

		driveChassis(chassisToggle);
		driveRoller();

		//trailer
		if (joy1Btn(6)) {
			//close
			servo[trailerServoL] = 75;
			servo[trailerServoR] = 180;
		}
		if (joy1Btn(5)) {
			//open
			servo[trailerServoL] = 255;
			servo[trailerServoR] = 0;
		}
		//gate
		if (joy2Btn(6)) {
			//open
			servo[gateServo] = 110;
		}
		if (joy2Btn(5)) {
			//close
			servo[gateServo] = 0;
		}

		if (joy2Btn(9) && joy2Btn(10)) {
			nMotorEncoder[liftL] = 0;
			nMotorEncoder[liftR] = 0;
		}
		delay(1);
	}
}

//inits encoders and servos
void init() {
	nMotorEncoder[liftL] = 0;
	nMotorEncoder[liftR] = 0;
	nMotorEncoder[chassisL] = 0;
	nMotorEncoder[chassisR] = 0;
	servo[trailerServoL] = 255;
	servo[trailerServoR] = 155;
	servo[gateServo] = 0;
}

//controls drive motors and determines speed toggle
void driveChassis(bool t) {
	if (t) {
		motor[chassisL] = -joystick.joy1_y1 * fullFactor;
		motor[chassisR] = joystick.joy1_y2 * fullFactor;
	} else {
		motor[chassisL] = -joystick.joy1_y1 * halfFactor;
		motor[chassisR] = joystick.joy1_y2 * halfFactor;
	}
}

//controls the roller
void driveRoller() {
	if (joy1Btn(8) || joy2Btn(8)) {
		motor[roller] = 100;
	} else if (joy1Btn(7) || joy2Btn(7)) {
		motor[roller] = -100;
	} else {
		motor[roller] = 0;
	}
}

//drive the lift, has 5 presets
task liftLPresets() {
	while (true) {
		getJoystickSettings(joystick);
		//highest setting
		if (joy2Btn(3) && nMotorEncoder[liftL] > -5500) {
			while (nMotorEncoder[liftL] > -5500) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = -100;
				motor[liftR] = 100;
			}
		}
		// medium-high setting
		if (joy2Btn(4) && nMotorEncoder[liftL] < 3959) {
			while (nMotorEncoder[liftL] < 3959) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = 100;
				//motor[liftR] = 100;
			}
		} else if (joy2Btn(4)) {
			while (nMotorEncoder[liftL] > 3959) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = -15;
				//motor[liftR] = -25;
			}
		}
		// medium-low setting
		if (joy2Btn(1) && nMotorEncoder[liftL] < 3040) {
			while (nMotorEncoder[liftL] < 3040) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = 100;
				//motor[liftR] = 100;
			}
		} else if (joy2Btn(1)) {
			while (nMotorEncoder[liftL] > 3040) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = -15;
				//motor[liftR] = -25;
			}
		}
		// low setting
		if (joy2Btn(2) && nMotorEncoder[liftL] < 2000) {
			while (nMotorEncoder[liftL] < 2000) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = 100;
				//motor[liftR] = -100;
			}
		} else if (joy2Btn(2)) {
			while (nMotorEncoder[liftL] > 2000) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = -15;
				//motor[liftR] = 15;
			}
		}
		// ground setting
		if (joystick.joy2_TopHat == 0) {
			while (nMotorEncoder[liftL] > 0) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = -15;
				//motor[liftR] = 15;
			}
			while (nMotorEncoder[liftL] < 0) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = 15;
				//motor[liftR] = 15;
			}
		}

		//manual lift control
		motor[liftL] = joystick.joy2_y1 * fullFactor;
		//motor[liftR] = -joystick.joy2_y1 * fullFactor;
		delay(1);
	}
}

//drive the lift, has 5 presets
task liftRPresets() {
	while (true) {
		getJoystickSettings(joystick);
		//highest setting
		if (joy2Btn(3) && nMotorEncoder[liftL] > -5500) {
			while (nMotorEncoder[liftL] > -5500) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftL] = -100;
				motor[liftR] = 100;
			}
		}
		// medium-high setting
		if (joy2Btn(4) && nMotorEncoder[liftR] > -3959) {
			while (nMotorEncoder[liftR] > -3959) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftR] = -100;
				//motor[liftR] = 100;
			}
		} else if (joy2Btn(4)) {
			while (nMotorEncoder[liftR] < -3959) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				//motor[liftL] = -15;
				motor[liftR] = 15;
			}
		}
		// medium-low setting
		if (joy2Btn(1) && nMotorEncoder[liftR] > -3040) {
			while (nMotorEncoder[liftR] > -3040) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftR] = -100;
				//motor[liftR] = 100;
			}
		} else if (joy2Btn(1)) {
			while (nMotorEncoder[liftR] < -3040) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				//motor[liftL] = -15;
				motor[liftR] = 15;
			}
		}
		// low setting
		if (joy2Btn(2) && nMotorEncoder[liftR] > -2000) {
			while (nMotorEncoder[liftR] > -2000) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				//motor[liftL] = 100;
				motor[liftR] = -100;
			}
		} else if (joy2Btn(2)) {
			while (nMotorEncoder[liftR] < -2000) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				//motor[liftL] = -15;
				motor[liftR] = 15;
			}
		}
		// ground setting
		if (joystick.joy2_TopHat == 0) {
			while (nMotorEncoder[liftR] < 0) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				//motor[liftL] = -15;
				motor[liftR] = 15;
			}
			while (nMotorEncoder[liftR] > 0) {
				if (joy2Btn(11) && joy2Btn(12)) {
					break;
				}
				motor[liftR] = -15;
			}
		}

		//manual lift control
		//motor[liftL] = joystick.joy2_y1 * fullFactor;
		motor[liftR] = -joystick.joy2_y1 * fullFactor;
		delay(1);
	}
}
