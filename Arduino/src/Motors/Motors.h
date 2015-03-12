#ifndef Motors_H
#define Motors_H

#include <arduino.h>

class Motors{
	
	Motors(int * MotorPins);
	~Motors();
	void DriveForward();
	void DriveBackward();
	void TurnLeft();
	void TurnRight();

private:
	int p1, p2, p3 p4;
};

#endif