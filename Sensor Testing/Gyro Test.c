#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)

/**
 *	This program finds the current heading with the HT Gyro Sensor
 */

#include "hitechnic-gyro.h"

float gyroRaw;
float tempW;
float avgW;
float angle;
float count;
float heading;

task main()
{
	int safetyValue = 1;  //value to protect against poor calibration
	heading = 0;
	gyroRaw = 0;
	avgW = 0;
	//angle = 0;
	count = 0;
	HTGYROstartCal(HTGYRO);
	while(true){
		gyroRaw = HTGYROreadRot(HTGYRO);
    tempW = 0;
    avgW = 0;
    count = 0;
    //angle = 0;
		if(abs(gyroRaw) > safetyValue){
			time1[T1] = 0;
			while(abs(gyroRaw) > safetyValue){
				gyroRaw = HTGYROreadRot(HTGYRO);
				tempW += gyroRaw;
				count++;
			}
			avgW = (tempW / count);
			angle = avgW*time1[T1]/1000;  //(change in angle) = (avg angular velocity) / (time in seconds)
			time1[T1] = 0;
		}
		heading += angle;
		angle = 0;
		nxtDisplayCenteredBigTextLine(3, "%d", heading);
		//delay(100);
	}
}
