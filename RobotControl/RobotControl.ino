// RobotControl
//
// Sample robot control program
//   led fade rate varies with pot value
//   servo arm shakes after the fsr is pressed and then released.
// 
// Developed on Adafruit Metro Mini (Arduino UNO clone)

#include <Servo.h> 

int potPin = A0;        // any analog input pin will do: A0-A5, A6-A11
int potValue = 0;

int ledPin = 11;        // this pin must allow pwm output: for the
                        // metro mini, use 3, 5, 6, 11 or 13
                        // note! this cannot be 9, 10 becasue the servo
                        //  library uses those and analogWrite() does
                        //  not work on them anymore

// these are new variables to hold the fsr's value and detect whether
// that force is large enough for a "press."

int fsrPin = A5;       // any analog input pin will do: A0-A5
int fsrValue = 0;

int pressValue = 64;   // force greater than threshold to shake hands
int releaseValue = 16; // value below which to expect fsr is released

boolean pressed;       // indicates if fsr is currently being pressed

Servo myservo;         // creates a servo object (from servo library)
int servoPin = 3;      // an unused pwm pin: 3, 5, 6, 9, 10, 11 or 13

// initialize servo object and set position to 0, then setup pin I/O.

void setup() {
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);
  
  myservo.write(0);
  delay(5);

  pinMode(ledPin, OUTPUT);
}

// check the pot's position, then set eye colors based on that value.
// red brightness decreases with pot rotation. green & blue increase.

// potVal and fsrVal are divided by 4 because the nano's analog input 
// ranges from 0-1023, while its pwm output ranges (just) from 0-256.

void loop() {
  potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 0, 255);

  analogWrite(ledPin, potValue);
  
  delay(10);
  
  fsrValue = analogRead(fsrPin) / 4;
  
  if (fsrValue > pressValue) {
    pressed = true;
  }
  
  if (pressed) {
    if (fsrValue < releaseValue) {
      for (int pos = 0; pos < 90; pos++) {
        myservo.write(pos);
        delay(5);
      } 
      for (int pos = 90; pos > 0; pos--) {
        myservo.write(pos);
        delay(5);
      }
      pressed = false;
    }
  }
  delay(10);
}
