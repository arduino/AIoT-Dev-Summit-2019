# Exercise 10: Next Steps

Now that you have things working, here are a few new things to try.

- Add some more gestures to go with the :punch: and :flex:

    1. Load the IMU_Capture sketch on your Arduino Nano 33 BLE Sense.
    1. Caputure some additional gestures for a new emoji. Perhaps a :smile:, :thumbsup:, :clap:, or :wave:
    1. Load the new CSV files into your Colab model
    1. Put the trained model back on your Nano 33 BLE Sense.

- Try increasing and decreasing the number of recordings per gesture, how does this impact performance?

- Try to only use the accelerometer or gyroscope data (not both), how does this impact performance?

- Tweak the model structure and parameters
  - Can you get better results?
  - Can you reduce the size and still get "good" results

- Check out the examples in the [TensorFlow Lite Getting Started Guide](https://www.tensorflow.org/lite/microcontrollers/get_started)

- Try the [Arudino Fruit to Emoji](https://github.com/arduino/ArduinoTensorFlowLiteTutorials/tree/master/FruitToEmoji) Tutorial

- Grab the [TinyML book](http://shop.oreilly.com/product/0636920254508.do) to continue at home
