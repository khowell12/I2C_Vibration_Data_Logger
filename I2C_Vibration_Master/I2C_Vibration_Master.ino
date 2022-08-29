#include <Wire.h>
#include <SPI.h>

File myFile;
const int chpSel = 10;
int sensor = A0; //Read transmitter on pin A0. X-axis
int S1 = 1 // Slave 1, Y-Axis
int S2 = 2 // Slave 2, Z-axis
int triggerPin = 5; //Pin to send trigger signal to slaves
void setup() {
  // put your setup code here, to run once:
  Wire.begin(); //join i2C bus
  Serial.begin(9600) // Serial Communication
  //Setup request functions onRequest for slaves, Master reqeusts data after analog read is complete
}

void loop() {
  // put your main code here, to run repeatedly:

  // Wait 15 mins - Delay
  // send trigger pulse
  // Slaves analog read for 8 seconds - use millis
  // Read vibration from bus - Wire.requestFrom(1) //What size to request?
  Wire.requestFrom(S1, 256);
  while (Wire.available(){
    char c = Wire.read(); // recveieve data as a character
    Serial.print(c); // print received data from S1. Store as string or something?
  }
  Wire.requestFrom(S2, 256);
  while (Wire.available(){
    char c = Wire.read(); // recveieve data as a character
    Serial.print(c); // print received data from S2. Store as string or something?
  } 
  // combine readings into 1x3 array
  // write to SD
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
  }
}
