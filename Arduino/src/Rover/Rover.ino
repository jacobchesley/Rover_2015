#include <Motors.h>
#include <Solenoids.h>
#include <Accelerometer.h>
#include <Compass.h>
#include <Sonar.h>
#include <QTRSensors.h>
#include <Math.h>
#include <Wire.h>

// Sonar digital ports
#define SONAR_TRIGGER 3
#define SONAR_ECHO 2

// Reflectnace sensor analog ports
#define REFLECTANCE_0 0
#define REFLECTANCE_1 1

// Solenoid enable ports
#define SOLENOID_0 53
#define SOLENOID_1 52
#define SOLENOID_2 51

// Solenoid enable time in milliseconds
#define SOLENOID_TIME 1000

// Motor drive ports
#define MOTOR_ENABLE_A0 41
#define MOTOR_ENABLE_A1 40
#define MOTOR_ENABLE_B0 39
#define MOTOR_ENABLE_B1 38

// Time to wait after landing to navigate
#define LANDING_DELAY 30

// reflectance sensor cutoff between black and white
#define REFLECTANCE_BW_CUTOFF 500

// wheel diameter in CM
#define DIAMETER 3 

// Distance to travel in CM
#define TRAVEL_DISTANCE 304.8

float pi = 3.14159265359;

// Sensor controllers
QTRSensorsAnalog reflect((unsigned char[]) {REFLECTANCE_0, REFLECTANCE_1}, 2);
Accelerometer accelerometer(true);
Compass compass;
Sonar sonar(SONAR_TRIGGER, SONAR_ECHO);

// Motor and solenoid controllers
Motors motors(MOTOR_ENABLE_A0, MOTOR_ENABLE_A1, MOTOR_ENABLE_B0, MOTOR_ENABLE_B1);
Solenoids solenoids((int[]) {SOLENOID_0, SOLENOID_1, SOLENOID_2}, 3);

void setup() {

  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin (9600);
   
  
  compass.Configure();
  sonar.Configure();
  motors.Configure();
  solenoids.Configure();
  accelerometer.Configure();
  
  Serial.println("Calibrate Magnetometer...");
 // compass.Calibrate(10);
  Serial.println("Finished calibration");  
}

void loop() {

  // Wait for launch
  while(accelerometer.GetAccelerationX() < 12.0){delay (10);}

  //*** LAUNCH OCCURRED ***!

  //wait while rover is still in rocket
  while(sonar.GetDistanceCM() < 20.0){delay (10);}

  //*** ROVER HAS BEEN EJECTED FROM ROCKET BODY ***!

  // wait while rover descends
  while(sonar.GetDistanceCM() > 10.0){delay (10);}

  //*** ROVER HAS LANDED ***!

  // wait definded number of seconds before navigating
  delay(1000 * LANDING_DELAY);

  // Drop parachute

  //*** ROVER HAS DROPPED PARACHUTE ***!
  
  // Drop marker 1
  solenoids.Enable(0);
  delay(SOLENOID_TIME);
  solenoids.Disable(0);
  
  //*** ROVER HAS DROPPED FIRST MARKER ***!
  

  //Drive forward ten feet
  bool driveForward = true;

  unsigned int reflectances[2] = {0,0};
  bool reflect0WasWhite = false;
  bool reflect1WasWhite = false;

  int leftDistanceCM = 0;
  int rightDistanceCM = 0;

  while(driveForward){
    
    // Get reflectance data to check if wheels have turned 90 degrees
    reflect.readCalibrated(reflectances);
        
    // Wheel 0 has turned 90 degrees
    if(reflectances[0] < REFLECTANCE_BW_CUTOFF && reflect0WasWhite){
      leftDistanceCM += (pi * DIAMETER) * 0.25;
      if(leftDistanceCM > TRAVEL_DISTANCE){
        driveForward = false;
        break;
      }
    }
    // Wheel 0 has turned 90 degrees
    else if(reflectances[0] > REFLECTANCE_BW_CUTOFF && (!reflect0WasWhite)){
      leftDistanceCM += (pi * DIAMETER) * 0.25;
      if(leftDistanceCM > TRAVEL_DISTANCE){
        driveForward = false;
        break;
      }
    }
    // Wheel 1 has turned 90 degrees
    if(reflectances[1] < REFLECTANCE_BW_CUTOFF && reflect1WasWhite){
      rightDistanceCM += (pi * DIAMETER) * 0.25;
      if(rightDistanceCM > TRAVEL_DISTANCE){
        driveForward = false;
        break;
      }
    }
    // Wheel 1 has turned 90 degrees
    else if(reflectances[1] > REFLECTANCE_BW_CUTOFF && (!reflect1WasWhite)){
      rightDistanceCM += (pi * DIAMETER) * 0.25;
      if(rightDistanceCM > TRAVEL_DISTANCE){
        driveForward = false;
        break;
      }
    }
    
    motors.DriveForward();
    delay(10);
  }
  
  //*** ROVER HAS DRIVEN 10 FEET FORWARD ***!
  
  // Drop marker 2
  solenoids.Enable(1);
  delay(SOLENOID_TIME);
  solenoids.Disable(1);
  
  //*** ROVER HAS DROPPED SECOND MARKER ***!
  
  // get current orientation
  float origDegrees = compass.GetDegrees();
  
  // Add 90 degrees
  float finalDegrees = origDegrees + 90.0f;
  
  // Make sure final degrees is 0 - 360 degrees
  finalDegrees = fmod(finalDegrees, 360.0f);
  
  // Turn 90 degrees    
}
