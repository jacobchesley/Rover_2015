/**
*	@author Jacob Chesley
*	@date 3/12/2015
*/

#include <Sonar.h>

Sonar::Sonar(int trigger, int echo){

		echoPin = echo;
		triggerPin = trigger;
}

Sonar::~Sonar(){
}

void Sonar::Configure(){
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

float Sonar::GetDistanceCM(){
	// Speed of sound is 29.386 microseconds per centimeter.  
	// Devide by 2 because sound goes from device, to object then back to device.
	return Ping() / 29.386f / 2.0f;
}

float Sonar::GetDistanceIN(){
	// Speed of sound is 74.642 microseconds per centimeter.  
	// Devide by 2 because sound goes from device, to object then back to device.
	return Ping() / 74.642f / 2.0f;
}

long Sonar::Ping(){		

	long duration, distance;

	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);

	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);

	digitalWrite(triggerPin, LOW);

	duration = pulseIn(echoPin, HIGH);

	return duration;
}