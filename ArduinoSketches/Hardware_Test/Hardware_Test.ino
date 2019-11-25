/*
  Hardware Test

  This sketch makes sure the development environment is set up correctly.

  Load the code, then open the serial terminal. The LED should blink quickly.

  This example code is in the public domain.
*/

#include <Arduino_LSM9DS1.h>

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // Turn on the LED
  digitalWrite(LED_BUILTIN, HIGH);
 
  Serial.begin(9600);

  // wait forever for the serial monitor to open
  while (!Serial);
  
  Serial.println("Arduino TinyML Workshop Hardware Test");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.println("Things look good. You're ready to go.");
  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED
  delay(250);                        // wait for 1/4 second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED
  delay(250);                        // wait for 1/4 second
}
