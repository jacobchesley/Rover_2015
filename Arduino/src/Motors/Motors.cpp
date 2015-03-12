#include <Motors.h>

Motors::Motors(int pin1, int pin2, int pin3, int pin4){
	p1 = pin1;
	p2 = pin2;
	p3 = pin3;
	p4 = pin4;
}

Motors::~Motors(){}

void Motors::DriveForward(){

	// Motor 1 forward
	digitalWrite(p1, HIGH);
	digitalWrite(p2, LOW);

	// Motor 2 forward
	digitalWrite(p3, HIGH);
	digitalWrite(p4, LOW);
}

void Motors::DriveBackward(){

	// Motor 1 backward
	digitalWrite(p1, LOW);
	digitalWrite(p2, HIGH);

	// Motor 2 backward
	digitalWrite(p3, LOW);
	digitalWrite(p4, HIGH);
}

void Motors::TurnLeft(){

	// Motor 1 backward
	digitalWrite(p1, LOW);
	digitalWrite(p2, HIGH);

	// Motor 2 forward
	digitalWrite(p3, HIGH);
	digitalWrite(p4, LOW);
}

void Motors::TurnRight(){

	// Motor 1 forward
	digitalWrite(p1, HIGH);
	digitalWrite(p2, LOW);

	// Motor 2 backward
	digitalWrite(p3, LOW);
	digitalWrite(p4, HIGH);
}

void Motors::Stop(){

	// Motor 1 off
	digitalWrite(p1, LOW);
	digitalWrite(p2, LOW);

	// Motor 2 off
	digitalWrite(p3, LOW);
	digitalWrite(p4, LOW);
}