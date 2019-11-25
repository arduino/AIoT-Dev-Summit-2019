/*
  IMU Capture

  This example uses the on-board IMU to start reading acceleration and gyroscope
  data from on-board IMU and prints it to the Serial Monitor for one second
  when the significant motion is detected.

  While waiting for significant motion, data is recorded in memory, to avoid
  loosing the starting portion of the gesture movement. There will be a delay
  between capturing the data and outputting it to the Serial Monitor.

  You can also use the Serial Plotter to graph the data.

  The circuit:
  - Arduino Nano 33 BLE or Arduino Nano 33 BLE Sense board.

  Created by Don Coleman, Dominic Pajak, Sandeep Mistry

  This example code is in the public domain.
*/

#include <Arduino_LSM9DS1.h>

const float ACCELERATION_RMS_THRESHOLD = 2.0;  // RMS (root mean square) threshold of significant motion in G's
const int NUM_CAPTURED_SAMPLES_PER_GESTURE = 119;
const int NUM_FEATURES_PER_SAMPLE = 6;
const int TOTAL_SAMPLES = NUM_CAPTURED_SAMPLES_PER_GESTURE * NUM_FEATURES_PER_SAMPLE;
const int THRESHOLD_SAMPLE_INDEX =  ((NUM_CAPTURED_SAMPLES_PER_GESTURE / 3) * NUM_FEATURES_PER_SAMPLE); // one-third of data comes before threshold

float samples[TOTAL_SAMPLES];

int capturedSamples = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // print the header
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;

  // wait for threshold trigger, but keep N samples before threshold occurs
  while (1) {
    // wait for both acceleration and gyroscope data to be available
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // read the acceleration and gyroscope data
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      // shift values over one position (TODO: replace memmove with for loop?)
      memmove(samples, samples + NUM_FEATURES_PER_SAMPLE, sizeof(float) * NUM_FEATURES_PER_SAMPLE * 39);

      // insert the new data at the threshold index
      samples[THRESHOLD_SAMPLE_INDEX + 0] = aX;
      samples[THRESHOLD_SAMPLE_INDEX + 1] = aY;
      samples[THRESHOLD_SAMPLE_INDEX + 2] = aZ;
      samples[THRESHOLD_SAMPLE_INDEX + 3] = gX;
      samples[THRESHOLD_SAMPLE_INDEX + 4] = gY;
      samples[THRESHOLD_SAMPLE_INDEX + 5] = gZ;

      // calculate the RMS of the acceleration
      float accelerationRMS =  sqrt(fabs(aX) + fabs(aY) + fabs(aZ));

      if (accelerationRMS > ACCELERATION_RMS_THRESHOLD) {
        // threshold reached, break the loop
        break;
      }
    }
  }

  // use the threshold index as the starting point for the remainder of the data
  capturedSamples = THRESHOLD_SAMPLE_INDEX + NUM_FEATURES_PER_SAMPLE;

  // collect the remaining samples
  while (capturedSamples < TOTAL_SAMPLES) {
    // wait for both acceleration and gyroscope data to be available
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // read the acceleration and gyroscope data
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      // insert the new data
      samples[capturedSamples + 0] = aX;
      samples[capturedSamples + 1] = aY;
      samples[capturedSamples + 2] = aZ;
      samples[capturedSamples + 3] = gX;
      samples[capturedSamples + 4] = gY;
      samples[capturedSamples + 5] = gZ;

      capturedSamples += NUM_FEATURES_PER_SAMPLE;
    }
  }

  // print the samples
  for (int i = 0; i < TOTAL_SAMPLES; i += NUM_FEATURES_PER_SAMPLE) {
    // print the data in CSV format
    Serial.print(samples[i + 0], 3);
    Serial.print(',');
    Serial.print(samples[i + 1], 3);
    Serial.print(',');
    Serial.print(samples[i + 2], 3);
    Serial.print(',');
    Serial.print(samples[i + 3], 3);
    Serial.print(',');
    Serial.print(samples[i + 4], 3);
    Serial.print(',');
    Serial.print(samples[i + 5], 3);
    Serial.println();

    delayMicroseconds(8403); // delay between each line for Serial Plotter, this matches the 119 Hz data rate of IMU
  }

  Serial.println(); // empty line
}
