// sample robot control program. rgb led color varies with pot value,
// while servo arm shakes after the fsr is pressed and then released.

#include <Servo.h> 

int sensorPin = A0;    // any analog input pin will do: A0-A5, A6-A11
int sensorValue = 0;

int redPin = 9;        // these 3 pins must allow pwm output: for the
int greenPin = 10;     // arduino micro, use 3, 5, 6, 9, 10, 11 or 13
int bluePin = 11;

// these are new variables to hold the fsr's value and detect whether
// that force is large enough for a "press."

int fsrPin = A1;       // any analog input pin will do: A0-A5, A6-A11
int fsrValue = 0;

int pressValue = 64;   // force greater than threshold to shake hands
int releaseValue = 16; // value below which to expect fsr is released

boolean pressed;       // indicates if fsr is currently being pressed

Servo myservo;         // creates a servo object (from servo library)
int servoPin = 6;      // an unused pwm pin: 3, 5, 6, 9, 10, 11 or 13

// initialize servo object and set position to 0, then setup pin I/O.

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);
  
  myservo.write(0);
  delay(5);
}

// check the pot's position, then set eye colors based on that value.
// red brightness decreases with pot rotation. green & blue increase.

// potVal and fsrVal are divided by 4 because the nano's analog input 
// ranges from 0-1023, while its pwm output ranges (just) from 0-256.

void loop() {
  sensorValue = analogRead(sensorPin) / 4;

  analogWrite(redPin, sensorValue);
  analogWrite(greenPin, 255 - sensorValue);
  analogWrite(bluePin, sensorValue);
  
  delay(10);
  
  fsrValue = analogRead(fsrPin) / 4;
  
  if (fsrValue > pressValue) {
    pressed = true;
  }
  
  if (pressed) {
    if (fsrValue < releaseValu) {
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
