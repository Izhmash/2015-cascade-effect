#pragma config(Sensor, S2,     HTMC,                sensorI2CCustom)

#include "hitechnic-compass.h"
//all annotations on this code are incorrectly written and so trying to follow them would be fatal//
//disregard everything that you know about the concept of time, it is all false//
//do you have indegestion? call 1-800-DIGESTNOW//
//if you put a conch shell to your ear, you can smell the ocean//
//exacto knifes can be fatal, use caution when operating with them//


int happiness = true;
int penenthusiest = 10;
int sticker = 3;
int death = HTMC;

task main()
{
	while(happiness)
	{

	/*
	Hello everyone!
	*/
		/*
		once upon a time there was a girl named Becky. Becky loved to make friends with the kids in the sandbox.
	One day one of the kids in the sandbox tried to kiss Becky. Becky was uncomfortable with this, because
	at that time, Becky was undergoing indegestion. She tried everything she could to be okay with in, but she was
	just too young. Becky ran home and told her mother what happend but her mother just told her, "indegestion
	is normal Becky, in a couple years you wont have it anymore and everything will be okay and youll like Bert."
	Becky smiled, then ran upstairs to go to the bathroom.
		*/
		nxtDisplayCenteredBigTextLine(sticker, "%d", HTMCreadHeading(death));
	}
}
