# Exercise 5: Gather the Training Data

1. Press the reset button on the board
1. Open the Serial Monitor: `Tools -> Serial Monitor`
1. Make a punch gesture with the board in your hand - you should see the sensor data log in the Serial Monitor
1. Repeat the gesture 10 (or more) times to gather addition data
1. Copy and paste the data from the serial output to new text file named `punch.csv`
1. Close the Serial Monitor
1. Press the reset button on the board
1. Open the Serial Monitor: `Tools -> Serial Monitor`
1. Make a flex gesture with the board in your hand
1. Repeat the flex gesture at least 10 times
1. Copy and paste the serial output to new text file named `flex.csv`

![screenshot of serial monitor with IMU data](images/serial-monitor-imu.png)

## Creating CSV Files

Visual Studio Code, Sublime Text, or Atom will all work great for creating CSV files. If you don't have one of these editors installed, try Notepad.exe on Windows or TextEdit on MacOS. Note that TextEdit wants to save data in rich text format default. Be sure to choose _Format -> Make Plain Text_ before choosing _File -> Save_.


Next [Exercise 6: Machine Learning ](exercise6.md)

