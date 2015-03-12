/**
*	@author Jacob Chesley
*	@date 3/12/2015
*
*/

#ifndef Motors_H
#define Motors_H

#include <arduino.h>

/**
*	
*	This controls a set of 2 motors using the L298N motor controller
*
*	Included several functions that are useful when motors are facing
*	opposite directions and paralled and coplanar with eachother
*	
*	For use with Arduino
*	
*	@brief The L298N Motor Controller Class for Arduino
*/
class Motors{
public:

	/**
	* 	Constructor for L298N Motor Controller
	*
	*	@param pin1 - IN1 on L298N Driver Board
	*	@param pin2 - IN2 on L298N Driver Board
	*	@param pin3 - IN3 on L298N Driver Board
	*	@param pin4 - IN4 on L298N Driver Board
	*/
	Motors(int pin1, int pin2, int pin3, int pin4);

	/**
	*	Destructor for L298N Motor Controller
	*/
	~Motors();

	/**
	*	Enables arduino pins for L298N Motor Controller
	*/
	void Configure();

	/**
	*	Turns both motors in same direction - Forward
	*/
	void DriveForward();

	/**
	*	Turns both motors in same direction - Backward
	*/
	void DriveBackward();

	/**
	*	Turns both motors in opposite direction - Left
	*/
	void TurnLeft();

	/**
	*	Turns both motors in opposite direction - Right
	*/
	void TurnRight();

	/**
	*	Disables both motors
	*/
	void Stop();

private:
	int p1;
	int p2;
	int p3;
	int p4;
};

#endif