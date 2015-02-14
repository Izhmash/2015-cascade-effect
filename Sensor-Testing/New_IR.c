#pragma config(Sensor, S1,     IR,              sensorI2CCustom)

#include "hitechnic-irseeker-v2.h"

task main()
{
	tHTIRS2 irSeeker;
	initSensor(&irSeeker, S1);

	while (true) {
		readSensor(&irSeeker);
      	displayTextLine(1, "D:%4d %4d 3%d", irSeeker.dcDirection, irSeeker.acDirection, irSeeker.enhDirection);
      	displayTextLine(2, "0:%4d %d", irSeeker.dcValues[0], irSeeker.acValues[0]);
      	displayTextLine(3, "0:%4d %4d", irSeeker.dcValues[1], irSeeker.acValues[1]);
      	displayTextLine(4, "0:%4d %4d %3d", irSeeker.dcValues[2], irSeeker.acValues[2], irSeeker.enhStrength);
      	displayTextLine(5, "0:%4d %4d", irSeeker.dcValues[3], irSeeker.acValues[3]);
      	displayTextLine(6, "0:%4d %4d", irSeeker.dcValues[4], irSeeker.acValues[4]);
     	displayTextLine(7, "Enter to switch");
	}
}
