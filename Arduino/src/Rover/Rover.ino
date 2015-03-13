#include <Motors.h>
#include <Solenoids.h>
#include <Accelerometer.h>
#include <Compass.h>

#include <QTRSensors.h>
#include <Wire.h>

// Custom rover classes


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

#define MAG_ADDR 0x0E //7-bit address for the MAG3110, doesn't change


// Reflactance sensors
QTRSensorsAnalog qtr((unsigned char[]) {REFLECTANCE_0, REFLECTANCE_1}, 2);

// Motor conroller
Motors motors(MOTOR_ENABLE_A0, MOTOR_ENABLE_A1, MOTOR_ENABLE_B0, MOTOR_ENABLE_B1);

// Solenoid controller
Solenoids solenoids((int[]) {SOLENOID_0, SOLENOID_1, SOLENOID_2}, 3);

Accelerometer accelerometer(true);

void setup() {

  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin (9600);
  
  configureMagnetometer(); // turn the MAG3110 on
  
  // Calibrate magnetometer and reflectance sensors for 10 seconds.
  // To do this, spin the rover around a full 360 degrees several times.
  // This will calibrate the magnetometer.
  // At the same time, the wheels will spin to calibrate the reflectance sensors
  
  for (int i = 0; i < 500; i++){
    
  }

  
  // Setup sonar pins
  pinMode(SONAR_TRIGGER, OUTPUT);
  pinMode(SONAR_ECHO, INPUT);
  
  // Enable motor output pins
  motors.Configure();
  
  // Enable solenoid output pins
  solenoids.Configure();
  
  // Enable accelerometer
  accelerometer.Configure();
}

void loop() {
    float test = accelerometer.GetAccelerationZ();
    Serial.println((float)test, 3);
    delay(100);
}

// Get distance from sonar in centimeters
int getDistance(){
  
  long duration, distance;
  digitalWrite(SONAR_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIGGER, LOW);
  duration = pulseIn(SONAR_ECHO, HIGH);
  return microsecondsToCentimeters(duration);
}


long microsecondsToCentimeters(long microseconds){
  
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}


/* ========================================================================================== */

/* ==========================================================================================
                                      Read Magnetometer Data
============================================================================================*/

void configureMagnetometer(void){
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x11);              // cntrl register2
  Wire.write(0x80);              // write 0x80, enable auto resets
  Wire.endTransmission();       // stop transmitting
  
  delay(15);
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x10);              // cntrl register1
  Wire.write(1);                 // write 0x01, active mode
  Wire.endTransmission();       // stop transmitting
}

void print_values(void)
{
  Serial.print("x=");
  Serial.print(readMagX()); 
  Serial.print(",");  
  Serial.print("y=");    
  Serial.print(readMagY());
  Serial.print(",");       
  Serial.print("z=");    
  Serial.println(readMagZ());      
}

int readMagX(void){
  
  int xl, xh;  //define the MSB and LSB
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x01);              // x MSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may write less than requested
  { 
    xh = Wire.read(); // read the byte
  }
  
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x02);              // x LSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may write less than requested
  { 
    xl = Wire.read(); // read the byte
  }
  
  int xout = (xl|(xh << 8)); //concatenate the MSB and LSB
  return xout;
}

int readMagY(void){
  
  int yl, yh;  //define the MSB and LSB
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x03);              // y MSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may write less than requested
  { 
    yh = Wire.read(); // read the byte
  }
  
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x04);              // y LSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may write less than requested
  { 
    yl = Wire.read(); // read the byte
  }
  
  int yout = (yl|(yh << 8)); //concatenate the MSB and LSB
  return yout;
}

int readMagZ(void){
  
  int zl, zh;  //define the MSB and LSB
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x05);              // z MSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may write less than requested
  { 
    zh = Wire.read(); // read the byte
  }
  
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x06);              // z LSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may write less than requested
  { 
    zl = Wire.read(); // read the byte
  }
  
  int zout = (zl|(zh << 8)); //concatenate the MSB and LSB
  return zout;
}

/* ========================================================================================== */

