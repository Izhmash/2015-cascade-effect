#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftMotor,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
void controlledDriveTank()
{
	float speed;
	float factor;
	int servo1pos;
	while(true)
	{
		getJoystickSettings(joystick);  // Update Buttons and Joysticks
		if (joy1Btn(3)) { //This provides a speed toggle
			speed = !speed;
			wait1Msec(10);
		}
		if (speed) {
			factor = 0.781;
		}
		else {
			factor = .391; //Slows the driving down to a reasonable amount.
		}
		motor[rightMotor] = joystick.joy1_y1*factor;
		motor[leftMotor] = -joystick.joy1_y2*factor;
		//PlayTone(abs(joystick.joy2_y2 / 10) * (abs((int)joystick.joy2_x1 + 5 / 10)), 10);

		/*Servo Testing*/

		if((joy1Btn(1))) servo1pos += 2;
		else if((joy1Btn(2))) servo1pos -= 2;
		servo[servo1] = servo1pos;
		wait1Msec(20);
	}
}
task main()
{
	nVolume = 4;
	controlledDriveTank();
}
