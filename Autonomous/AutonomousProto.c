#pragma config(Sensor, S4,     IR,              sensorI2CCustom)

#include "hitechnic-irseeker-v2.h"

task main()
{
	tHTIRS2 irSeeker;
	initSensor(&irSeeker, S4);

	while (true) {
	}
}
