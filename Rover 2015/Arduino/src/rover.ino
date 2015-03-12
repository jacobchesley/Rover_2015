#include <QTRSensors.h>
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

/* ----------------------------------------------------------------------------
                        Global Variables
-------------------------------------------------------------------------------*/
float gravity = 9.80665;
/*-----------------------------------------------------------------------------*/

/* ----------------------------------------------------------------------------
                        ADXL345 Data Variables
-------------------------------------------------------------------------------*/
 
#define ADXL_345_DEVICE (0x53) // Device address as specified in data sheet - ADXL345
#define MAG_ADDR 0x0E //7-bit address for the MAG3110, doesn't change
 
 
byte ADXL_345_buffer[6];
 
char POWER_CTL = 0x2D;  //Power Control Register
char DATA_FORMAT = 0x31;
char DATAX0 = 0x32; //X-Axis Data 0
char DATAX1 = 0x33; //X-Axis Data 1
char DATAY0 = 0x34; //Y-Axis Data 0
char DATAY1 = 0x35; //Y-Axis Data 1
char DATAZ0 = 0x36; //Z-Axis Data 0
char DATAZ1 = 0x37; //Z-Axis Data 1

/*-----------------------------------------------------------------------------*/


// Reflactance sensors
QTRSensorsAnalog qtr((unsigned char[]) {REFLECTANCE_0, REFLECTANCE_1}, 2);

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
  
  // Setup Motor Pins
  pinMode(MOTOR_ENABLE_A0, OUTPUT);
  pinMode(MOTOR_ENABLE_A1, OUTPUT);
  pinMode(MOTOR_ENABLE_B0, OUTPUT);
  pinMode(MOTOR_ENABLE_B1, OUTPUT);
  
  // Setup solenoid pins
  pinMode(SOLENOID_0, OUTPUT);
  pinMode(SOLENOID_1, OUTPUT);
  pinMode(SOLENOID_2, OUTPUT);
      
  //Put the ADXL345 into +/- 16G range by writing the value 0x0B to the DATA_FORMAT register.
  //writeTo(DATA_FORMAT, 0x0B);
  //Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register.
  //writeTo(POWER_CTL, 0x08);

}

void loop() {
  

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

void driveForward(){
  digitalWrite(MOTOR_ENABLE_A0, HIGH);
  digitalWrite(MOTOR_ENABLE_A1, LOW);
  
  digitalWrite(MOTOR_ENABLE_B0, HIGH);
  digitalWrite(MOTOR_ENABLE_B1, LOW);
}

void driveBackward(){
  digitalWrite(MOTOR_ENABLE_A0, LOW);
  digitalWrite(MOTOR_ENABLE_A1, HIGH);
  
  digitalWrite(MOTOR_ENABLE_B0, LOW);
  digitalWrite(MOTOR_ENABLE_B1, HIGH);
}

void turnLeft(){
  digitalWrite(MOTOR_ENABLE_A0, LOW);
  digitalWrite(MOTOR_ENABLE_A1, HIGH);
  
  digitalWrite(MOTOR_ENABLE_B0, HIGH);
  digitalWrite(MOTOR_ENABLE_B1, LOW);
}

void turnRight(){
  digitalWrite(MOTOR_ENABLE_A0, HIGH);
  digitalWrite(MOTOR_ENABLE_A1, LOW);
  
  digitalWrite(MOTOR_ENABLE_B0, LOW);
  digitalWrite(MOTOR_ENABLE_B1, HIGH);
}

void activateSolenoid0(){
  
  digitalWrite(SOLENOID_0, HIGH);
  delay(SOLENOID_TIME);
  digitalWrite(SOLENOID_0, LOW);
}

void activateSolenoid1(){
  
  digitalWrite(SOLENOID_1, HIGH);
  delay(SOLENOID_TIME);
  digitalWrite(SOLENOID_1, LOW);
}

void activateSolenoid2(){
  
  digitalWrite(SOLENOID_2, HIGH);
  delay(SOLENOID_TIME);
  digitalWrite(SOLENOID_2, LOW);
}

/* ==========================================================================================
                                      Read Acceleration Data
============================================================================================*/

float readAcceleration(){
  uint8_t numBytes = 6;
  readFrom(DATAX0, numBytes, ADXL_345_buffer); //read the acceleration data from the ADXL345
 
  // each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
  // thus we are converting both bytes in to one int
  float x = (((int)ADXL_345_buffer[1]) << 8) | ADXL_345_buffer[0];   
  float y = (((int)ADXL_345_buffer[3]) << 8) | ADXL_345_buffer[2];
  float z = (((int)ADXL_345_buffer[5]) << 8) | ADXL_345_buffer[4];
 
  // convert the raw data to float's representing g's
  x = x * 0.0039;
  y = y * 0.0039;
  z = z * 0.0039;
   
  // return the axis you want! 
  return y * gravity;
}
 
void writeTo(byte address, byte val) {
  Wire.beginTransmission(ADXL_345_DEVICE); // start transmission to device 
  Wire.write(address);             // send register address
  Wire.write(val);                 // send value to write
  Wire.endTransmission();         // end transmission
}
 
// Reads num bytes starting from address register on device in to ADXL_345_DEVICE array
void readFrom(byte address, int num, byte ADXL_345_buffer[]) {
  Wire.beginTransmission(ADXL_345_DEVICE); // start transmission to device 
  Wire.write(address);             // sends address to read from
  Wire.endTransmission();         // end transmission
 
  Wire.beginTransmission(ADXL_345_DEVICE); // start transmission to device
  Wire.requestFrom(ADXL_345_DEVICE, num);    // request 6 bytes from device
 
  int i = 0;
  while(Wire.available())         // device may send less than requested (abnormal)
  { 
    ADXL_345_buffer[i] = Wire.read();    // receive a byte
    i++;
  }
  Wire.endTransmission();         // end transmission
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
