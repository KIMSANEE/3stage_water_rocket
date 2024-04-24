/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

int SW = 15;
int flag = 0;
int once = 0;

Servo myservo1;
Servo myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(115200);
  pinMode(SW, INPUT_PULLUP);
  myservo1.attach(6);
  myservo2.attach(5);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  int readValue = digitalRead(SW);
  if(readValue == LOW){
    if(flag == 0){
      flag = 1;
      Serial.println(flag);
    } else {
      flag = 0;
      Serial.println(flag);
    }
    once = 0;
  }
  delay(200);
if(once == 0){
  if(flag == 0){
    Serial.println("a");
        for(pos = 0; pos<=90; pos++){
          myservo2.write(pos);
          myservo1.write(pos);
          delay(5);
        }
        once = 1;
  } else{
    Serial.println("b");
        for(pos = 90; pos>=0; pos--){
          myservo2.write(pos);
          myservo1.write(pos);
          delay(5);
        }
        once = 1;
  }
  }



  // if(Serial.available()>0){
  //   char receivedData = Serial.read();
  //   switch (receivedData) {
  //     case 'a':
  //       Serial.println("a");
  //       for(pos = 0; pos<=90; pos++){
  //         myservo2.write(pos);
  //         myservo1.write(pos);
  //         delay(5);
  //       }
  //       break;
  //     case 'b':
  //       Serial.println("b");
  //       for(pos = 90; pos>=0; pos--){
  //         myservo2.write(pos);
  //         myservo1.write(pos);
  //         delay(5);
  //       }
  //       break;
  //     default:
  //       delay(10);
  //       break;
  //     }
  // }


 
}
