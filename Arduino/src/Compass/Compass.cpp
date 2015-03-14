/**
*	@author Jacob Chesley
*	@date 3/12/2015
*/

#include <Compass.h>

//#define MAG_ADDR 0x0E
Compass::Compass(){

	address = 0x0E;
	degreesInRad = 57.2957795;
	pi = 3.14159265359;
}

Compass::~Compass(){
	
}

void Compass::Configure(){

	Wire.beginTransmission(address); 
	Wire.write(0x11); // control register2
	Wire.write(0x80); // eenable auto resets
	Wire.endTransmission();   
  
	delay(15);

	Wire.beginTransmission(address); 
	Wire.write(0x10); // control register 1
	Wire.write(1); // Active mode
	Wire.endTransmission();
}

void Compass::Calibrate(int numberSeconds){

	// First values
	minX = GetMagX();
	minY = GetMagY();
	minZ = GetMagZ();

	// Set max values to miniumum
	maxX = minX;
	maxY = minY;
	maxZ = minZ;

	float tmpX = 0.0f;
	float tmpY = 0.0f;
	float tmpZ = 0.0f;

	// Look for max and min for X, Y and Z values, with a 20 millisecond delay
	for(int i = 0; i < (numberSeconds * 50); i++){

		tmpX = GetMagX();
		tmpY = GetMagY();
		tmpZ = GetMagZ();

		if(tmpX > maxX){
			maxX = tmpX;
		}
		if(tmpX < minX){
			minX = tmpX;
		}

		if(tmpY > maxY){
			maxY = tmpY;
		}
		if(tmpY < minY){
			minY = tmpY;
		}

		if(tmpZ > maxZ){
			maxZ = tmpZ;
		}
		if(tmpZ < minZ){
			minZ = tmpZ;
		}
		delay(20);
	}

	// Scale the values to 0 to 1 range
	scaleX = 1.0f/(maxX - minX);
	scaleY = 1.0f/(maxY - minY);
	scaleZ = 1.0f/(maxZ - minZ);

	// Offset the values to -0.5 to 0.5 range
	offsetX = (minX + maxX) * 0.5f;
	offsetY = (minY + maxY) * 0.5f;
	offsetZ = (minZ + maxZ) * 0.5f;

}

float Compass::GetDegrees(){

	// Get data for each axis
	float x = (float)GetMagX();
	float y = (float)GetMagY();
	float z = (float)GetMagZ();

	// Offset and scale values
	x -= offsetX;
	y -= offsetY;
	z -= offsetZ;

	x *= scaleX;
	z *= scaleZ;

	// Get the radians 
	float heading = atan2(-z, x); 

	// Make sure heading is in 0- 2PI range
	if(heading < 0.0f){
		heading += 2.0f * pi;
	}

	// Convert to degrees
	return heading * degreesInRad;
}

int Compass::GetMagX(){
	return ReadData(0x01, 0x02);
}

int Compass::GetMagY(){
	return ReadData(0x03, 0x04);
}

int Compass::GetMagZ(){
	return ReadData(0x05, 0x06);
}

int Compass::ReadData(char reg_address1, char reg_address2){

int lsb, msb;  //define the MSB and LSB

	Wire.beginTransmission(address);
	Wire.write(reg_address1);              // x MSB reg
	Wire.endTransmission();       

	delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
	Wire.requestFrom(address, 1);
	while(Wire.available()){ 
		msb = Wire.read(); 
	}

	delayMicroseconds(2); //needs at least 1.3us free time between start and stop

	Wire.beginTransmission(address); 
	Wire.write(reg_address2);              // x LSB reg
	Wire.endTransmission();

	delayMicroseconds(2); //needs at least 1.3us free time between start and stop

	Wire.requestFrom(address, 1); 
	while(Wire.available()) { 
		lsb = Wire.read(); 
	}

	int out =  (lsb|(msb << 8)); //concatenate the MSB and LSB
	return out;
}
