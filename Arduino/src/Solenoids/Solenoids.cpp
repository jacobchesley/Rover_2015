/**
*	@author Jacob Chesley
*	@date 3/12/2015
*/

#include <Solenoids.h>

Solenoids::Solenoids(int * solenoidPins, int numSolenoids){

	pins = solenoidPins;
	numPins = numSolenoids;
}

Solenoids::~Solenoids(){
	delete[] pins;
}

void Solenoids::Configure(){
	
	// Itterate through all solenoid pins, and set mode to output
	for(int i = 0; i < numPins; i++){
		pinMode(pins[i], OUTPUT);
	}
}

void Solenoids::Enable(int solenoid){

	// Verify solenoid requested to be enabled is in valid range, if not return
	if(solenoid > (numPins - 1) || solenoid < 0){
		return;
	}

	// Enable solenoid
	digitalWrite(pins[solenoid], HIGH);
}

void Solenoids::Disable(int solenoid){

	// Verify solenoid requested to be enabled is in valid range, if not return
	if(solenoid > (numPins - 1) || solenoid < 0){
		return;
	}

	// Disable solenoid
	digitalWrite(pins[solenoid], LOW);
}