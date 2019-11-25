/*
  This example sends an emoji character over USB HID when here is significant accelerometer motion

  Note: Only macOS and Linux as supported at this time, and the use of
        #define is generally discouraged in Arduino examples

  The circuit:
  - Arduino Nano 33 BLE or Arduino Nano 33 BLE Sense board.

  Created by Don Coleman, Sandeep Mistry

  This example code is in the public domain.
*/

#include <PluggableUSBHID.h>
#include <USBKeyboard.h>
#include <Arduino_LSM9DS1.h>

// Select an OS:
// #define MACOS // You'll need to enable and select the unicode keyboard: System Preferences -> Keyboard -> Input Sources -> + -> Others -> Unicode Hex Input
// #define LINUX

#if !defined(MACOS) && !defined(LINUX)
#error "Please select an OS!"
#endif

// http://www.unicode.org/emoji/charts/full-emoji-list.html
const int bicep = 0x1f4aa;
const int punch = 0x1f44a;

const float accelerationThreshold = 2.5; // threshold of significant in G's

USBKeyboard keyboard;

void setup() {
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  float aX, aY, aZ;

  if (IMU.accelerationAvailable()) {
    // read the acceleration data
    IMU.readAcceleration(aX, aY, aZ);

    // sum up the absolute values of the acceleration
    float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

    // wait for significant motion
    // check if acceleration is above the threshold
    if (aSum >= accelerationThreshold) {
      // print an emoji
      sentUtf8(bicep);
      // delay to prevent too many emojis
      delay(250);
    }
  }

}

void sentUtf8(unsigned long c) {
  String s;

#if defined(MACOS)
  // https://apple.stackexchange.com/questions/183045/how-can-i-type-unicode-characters-without-using-the-mouse

  s = String(utf8ToUtf16(c), HEX);

  for (int i = 0; i < s.length(); i++) {
    keyboard.key_code(s[i], KEY_ALT);
  }
#elif defined(LINUX)
  s = String(c, HEX);

  keyboard.key_code('u', KEY_CTRL | KEY_SHIFT);

  for (int i = 0; i < s.length(); i++) {
    keyboard.key_code(s[i]);
  }
#endif
  keyboard.key_code(' ');
}

// based on https://stackoverflow.com/a/6240819/2020087
unsigned long utf8ToUtf16(unsigned long in) {
  unsigned long result;

  in -= 0x10000;

  result |= (in & 0x3ff);
  result |= (in << 6) & 0x03ff0000;
  result |= 0xd800dc00;

  return result;
}
