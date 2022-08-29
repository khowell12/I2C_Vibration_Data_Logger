
#include <Wire.h>

int previousMillis; //To be used in data log timer
int currentMillis; //To be used in data log timer
int aY = A1; // Analog input Slave 2 is Y-axis
int count = 0;//

void setup() {
  Wire.begin(9);                // join i2c bus with address #9
  Wire.onRequest(requestEvent); // register event
  pinMode(15, INPUT);           // signal pin to trigger data log function
  digitalWrite(15, LOW);        // Initialize pin LOW
  attachInterrupt(digitalPinToInterrupt(15),dataLog,RISING); // wait for trigger signal on pin 15, call datalog function on rising signal
}

void loop() {
  digitalWrite(15, LOW); // Keep pin low, do I need this?
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("hello from 2 \n"); // respond with message of 14 bytes
                                 // as expected by master
}
//Data log function called when pin is triggered via interrupt
//Data sent to master for writing to SD card in this function
//Do I need to transmit data using a request event?
void dataLog() {
  String dy = count + "\n"; //Start datalog of y-axis with count

  //set timers
  currentMillis = millis(); // set both so that difference is close to 0
  previousMillis = millis();
  
  //read data off of analog input
  while (currentMillis - previousMillis < 8000){ // Need to setup to read for 8 seconds
    float sensor = analogRead(aY);               // Read value on analog pin
    float volt = sensor * 4.4 /1023;             // 216 Ohm resistor * 20ma = 4.4V
    dy += String(volt) + "\n";                          // add data to string
    currentMillis = millis();                    // adjust variables for timer
    delay(100);                                  // Try with and without delay 
    }
    
  //Send data to master
  Wire.write(dy); // What do i need to do to transmit this to master?
  count += 1; //Keep track of how many times dataLog is called
}
