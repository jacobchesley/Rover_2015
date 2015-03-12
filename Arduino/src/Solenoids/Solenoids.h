/**
*	@author Jacob Chesley
*	@date 3/12/2015
*/

#ifndef Solenoids_H
#define Solenoids_H

#include <arduino.h>

/**
*	
*	This controls a set of solenoids, using a NPN transistors
*
*	Included several functions that are useful to enable and disable solenoids;
*	
*	For use with Arduino
*	
*	@brief The Solenoid Controller Class for Arduino
*/
class Solenoids{
public:

	/**
	* 	Constructor for Solenoid Controller
	*
	*	@param solenoidPins - Array of integers representing list of solenoid pin numbers
	*	@param numSolenoids - Number of solenoids
	*/
	Solenoids(int * solenoidPins, int numSolenoids);

	/**
	*	Destructor for L298N Motor Controller
	*/
	~Solenoids();

	/**
	*	Enables arduino pins for Solenoids
	*/
	void Configure();

	/**
	*	Enables solenoid
	*
	*	@param solenoid - solenoid in sequence given in constructor to enable.
	*/
	void Enable(int solenoid);

	/**
	*	Disables solenoid
	*
	*	@param solenoid - solenoid in sequence given in constructor to disable.
	*/
	void Disable(int solenoid);

private:
	int * pins;
	int numPins;
};

#endif