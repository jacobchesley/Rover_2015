/**
*	@author Jacob Chesley
*	@date 3/12/2015
*/

#ifndef Compass_H
#define Compass_H

#include <arduino.h>
#include <Wire.h>

/**
*	
*	This reads and interprets magnetometer data from the MAG3110.
*	
*	For use with Arduino - i2c connection
*	
*	@brief The Compasss Class for Arduino
*/
class Compass{
public:

	/**
	* 	Constructor for Compass
	*/
	Compass();

	/**
	*	Destructor for Compass
	*/
	~Compass();

	/**
	*	Configures the MAG3110
	*/
	void Configure();

	/**
	*	Calibrates the MAG3110.  Spin the device several times full circle for the
	*	duration of time specified in the parameter.  This reads data coming in, gathers
	* 	minimum and maximum data values for each axis, then takes the difference of max-min
	*	for each axis.  This is used to scale the data read from the magnometer to generate
	*	degrees pointed from north.
	*/
	void Calibrate(int numberSeconds);

	/**
	*	Get degrees from north pole
	*
	*	@return degrees from north
	*/
	float GetDegrees();

	/**
	*	Get magnetometer data from X axis
	*
	*	@return X Axis magnet data
	*/
	int GetMagX();

	/**
	*	Get magnetometer data from Y axis
	*
	*	@return Y Axis magnet data
	*/
	int GetMagY();

	/**
	*	Get magnetometer data from Z axis
	*
	*	@return Z Axis magnet data
	*/
	int GetMagZ();

private:
	
	int ReadData(char reg_address1, char reg_address2);
	// Device address
	char address;

	// scale data
	float minX;
	float minY;
	float minZ;

	float maxX;
	float maxY;
	float maxZ;

	float scaleX;
	float scaleY;
	float scaleZ;

	float offsetX;
	float offsetY;
	float offsetZ;

	float degreesInRad;
	float pi;

};

#endif