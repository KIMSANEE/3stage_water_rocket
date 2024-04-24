#include <Servo.h>

// Define the servo motor
Servo myServo1;
Servo myServo2;

// Define the switch pin
const int SW = 10; // Change this to the pin you connect the switch to

// Variables to store the servo position and switch state
int servoPos = 0;
int switchState = 0;
int lastSwitchState = 0;

void setup() {
  // Attach the servo to pin 9
  myServo1.attach(5); // Change this to the pin you connect the servo to
  myServo2.attach(6);
  // Set the switch pin as input
}

void loop() {
  // Read the state of the switch
  switchState = digitalRead(SW);

  // If the switch state has changed
  if (switchState != lastSwitchState) {
    // If the switch is pressed
    if (switchState == HIGH) {
      // Rotate the servo to +90 degrees
      servoPos = 80;
      myServo1.write(75);
      myServo2.write(servoPos);
      delay(500);
    } else {
      // If the switch is released, return to -90 degrees
      servoPos = -80;
      myServo1.write(-75);
      myServo2.write(servoPos);
      delay(500);
    }
  }

  // Update the last switch state
  lastSwitchState = switchState;
}
