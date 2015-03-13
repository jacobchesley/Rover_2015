/**
*	@author Jacob Chesley
*	@date 3/12/2015
*/

#include <Compass.h>

Compass::Compass(){

	address = 0x0E;
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


	calibrationX = 1.0f/(maxX - minX);
	calibrationY = 1.0f/(maxY - minY);
	calibrationZ = 1.0f/(maxZ - minZ);
}

int Compass::GetMagX(){
	return ReadData(0x01);
}

int Compass::GetMagY(){
	return ReadData(0x03);
}

int Compass::GetMagZ(){
	return ReadData(0x05);
}

int Compass::ReadData(char reg_address){
	int msb, lsb;  //define the MSB and LSB

	Wire.beginTransmission(address);
	Wire.write(reg_address); // x MSB reg
	Wire.endTransmission();
 
	delayMicroseconds(2); //needs at least 1.3us free time between start and stop

	Wire.requestFrom(address, 2); // request 2 bytes

	while(Wire.available() < 2){ 
		msb = Wire.read();
		lsb = Wire.read();
	}

	return (lsb|(msb << 8)); //concatenate the MSB and LSB
}