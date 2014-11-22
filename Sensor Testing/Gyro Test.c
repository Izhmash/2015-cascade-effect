#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)

#include "hitechnic-gyro.h"

double gyroRaw;
double tempW;
double avgW;
double angle;
double count;

task main()
{
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
		if(abs(gyroRaw) > 15){
			time1[T1] = 0;
			while(abs(gyroRaw) > 15){
				gyroRaw = HTGYROreadRot(HTGYRO);
				tempW += gyroRaw;
				count++;
			}
			avgW = (tempW / count);
			angle = avgW*time1[T1]/1000;
			time1[T1] = 0;
		}
		nxtDisplayCenteredBigTextLine(3, "%d", angle);
		delay(100);
	}
}
