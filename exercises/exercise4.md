# Exercise 4: Visualize the IMU Data

The next step is to use an Arduino program you downloaded in [Exercise 2](exercise2.md) to capture motion data from the IMU.

1. Open __tinyml-workshop/ArduinoSketches/IMU_Capture/IMU_Capture.ino__ in the Arduino IDE.
1. Compile the sketch and upload it to the board: `Sketch -> Upload`
1. Open the Serial Monitor: `Tools -> Serial Monitor`
1. Shake the board. The change in acceleration will start recording data from the IMU in the Serial Monitor
1. Close the Serial Monitor window
1. Open the Serial Plotter: `Tools -> Serial Plotter`
1. Shake the board. The change in acceleration will start graphing data in the Serial Plotter
1. Repeat capturing various gestures to get a sense of what the training data will look like
1. Close the Serial Plotter

![screenshot of serial monitor with IMU data](images/serial-monitor-imu.png)

![screenshot of serial plotter with IMU data](images/serial-plotter-imu.png)

Next [Exercise 5: Gather the Training Data](exercise5.md)


