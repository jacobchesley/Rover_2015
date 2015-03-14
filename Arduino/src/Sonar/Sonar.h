/**
*	@author Jacob Chesley
*	@date 3/12/2015
*/

#ifndef Sonar_H
#define Sonar_H

#include <arduino.h>

/**
*	
*	This controls the HC-SR04 range detector
*	
*	For use with Arduino
*	
*	@brief The Sonar Class for Arduino
*/
class Sonar{
public:

	/**
	* 	Constructor for Sonar Controller
	*
	*	@param trigger - pin number trigger is attached to
	*
	*	@param echo - pin number echo is attached to
	*/
	Sonar(int trigger, int echo);

	/**
	*	Destructor for Sonar Controller
	*/
	~Sonar();

	/**
	*	Enables arduino pins for Sonar
	*/
	void Configure();

	/**
	*	@return distance in centimeters
	*/
	float GetDistanceCM();

	/**
	*	@return distance in inches
	*/
	float GetDistanceIN();


private:

	/**
	*	@return microseconds of sonar - used to calculate distance
	*/
	long Ping();
	
	int echoPin;
	int triggerPin;
};

#endif