# Introduction

## TDLR

We'll be covering the full embedded machine learning (ML) lifecycle: data capturing, model training, model. [Skip to Exercise 1: Development Environment](exercise1.md).


## Inspiration

This project was inspired by [Charlie Gerard's street fighter project](https://dev.to/devdevcharlie/play-street-fighter-with-body-movements-using-arduino-and-tensorflow-js-4kbi).

![Charlie Gerard's motion controlled Street Fighter demo](images/charlie_gerard_street_fighter.gif)

Instead of using JavaScript with TensorFlow.js and Johnny Five (which is great) we’ll develop the model in TensorFlow and run on a microcontroller (MCU) with TensorFlow Lite.

JSConf talk link: https://www.youtube.com/watch?v=rwFiFWI23Rw

## Goal

Build an motion / gesture based emoji keyboard!

Detect punching vs flexing ...

## AI / ML overview

Quick overview, we can't teach you everything in 2 hours ...

### What is Machine Learning (ML) ?

“A field of study that gives computers the ability to learn without being explicitly programmed.” 
- Attributed to Arthur Samuel

Excerpt from "Grokking Deep Learning" by Andrew Trask 

...

Machine Learning =~ Monkey see, monkey do

🐵


Progamming:

```
             +----------+
Algorithm -> |          |
             |          | -> *Answers*
Input     -> |          |
             +----------+
```

Machine Learning:

```
             +----------+
*Answers* -> |          |
             |          | -> Algorithm
Input     -> |          |
             +----------+
```

Supervised Learning:

```
                 +---------------------+
What you know -> | Supervised Learning | -> What you want to know
                 +---------------------+
```

## What we'll be using

* Python
* Jupyter Notebooks / Google Colab
* TensorFlow
* NumPy
* Pandas
* mathplotlib

## What's TinyML

Running ML models on microcontrollers. Low power, below 1 mW.

## Arduino Nano 33 BLE Sense board

Based on the Nordic nRF52840
* Arm Cortex-M4F running at 64 MHz
* 256 kB RAM
* 1 MB Flash
* Bluetooth 5 radio

Onboard Sensors
* IMU (measure motion: acceleration, gyro)
* Temperature, pressure, humidity, light, color
* PDM microphone

## What is an IMU?

IMU - Inertial Measurement Unit

This board uses the ST Micro LSM9DS1.

* Gyroscope - measures angular velocity -- that is "how fast, and along which axis, am I rotating?"
* Accelerometer - measures acceleration, which indicates how fast velocity is changing -- "how fast am I speeding up or slowing down?" 
* Magnetometer - which measures the power and direction of magnetic fields

We're only using the accelerometer and gyroscope for this project.


## Workshop

* Record IMU data
* Use data to train ML model
* Convert model to run on microcontroller
* Run the model on the Arduino

## Why is ML / TinyML a good fit

* It’s definitely possible to develop an algorithm to detect punches using classical programming techniques, but … how would you account for following
  * People might punch differently?
  * Different styles of punching?
  * You want to be able to detect more than one type of gesture
* Things get complicated!
* ML is also “cool”, that’s why we’re all here today? Why not try it out!

## IMU input data


The Arduino library enables the sensor to report 119 data points every second, this means a new set of data is received every 8.4ms


We’ll focus on the accelerometer and gyroscope inputs (ignore magnetometer). Each input has 3 axis = X, Y, Z

The inputs for the model will be 1 second of data = 119 samples

Each sample will be [Ax, Ay, Az, Gx, Gy, Gz]


```
[ax, ay, az, gx, gy, gz]
```

Each gesture recording contains 119 rows of 6 points of data record in one second

We’ll pass 119 x 6 inputs as an array and expect the type of gesture.


```
  [Ax1, Ay1, Az1, Gx1, Gy1, Gz1, Ax2, Ay2, Az2, Gx2, Gy2, Gz2,… Ax119, Ay119, Az119, Gx119, Gy119, Gz119]
```

Sample data file

```
aX,aY,aZ,gX,gY,gZ
0.569,-0.698,0.592,50.110,-43.762,22.888
0.590,-0.756,0.629,55.542,-32.654,19.592
0.553,-0.727,0.644,50.964,-34.912,16.479
0.549,-0.761,0.670,45.471,-34.363,13.062
0.577,-0.844,0.666,47.119,-29.236,11.780
0.576,-0.867,0.707,50.781,-19.592,13.123
0.600,-0.862,0.720,55.786,-14.343,16.235
0.589,-0.841,0.721,57.556,-8.301,18.372
0.578,-0.842,0.741,56.763,-1.099,20.020

```

We flatten the data before we pass it to Kera rather than passing a 2 dimensional array.
(We could have passed a 2 dimensional array, but then we could need a Keras flatten layer)
The flattened array or vector makes the Arduino code simpler too.


```
[ax1, ay1, az1, gx1, gy1, gz1, ax2, ay2, az2, gx2, gy2, gz2,…, ax119, ay119, az119, gx119, gy119, gz119]
```

# Post workshop

TinyML: http://shop.oreilly.com/product/0636920254508.do
* Will feature the same board we used today
* The content of this workshop is based on it
* Includes other examples, such as “micro speech”, voice keyword detection (“yes” vs “no”)


Grokking Deep Learning: https://www.manning.com/books/grokking-deep-learning
* Covers theory of Deep Learning, teaches you at lower level using Python with Numpy

Next [Exercise 1: Development Environment](exercise1.md)

