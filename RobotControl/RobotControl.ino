// sample robot control program. plain led color varies with pot value
// servo shakes robot's arm after the fsr is pressed and then released

#include <Servo.h> 

int potPin = A0;       // the pot's value. use analog input pin A0-A5
int potValue = 0;

int ledPin = 11;       // an unused pwm pin: 3, 5, 6, 9, 10, 11 or 13

int fsrPin = A4;       // the fsr's value. use analog input pin A0-A5
int fsrValue = 0;

int pressValue = 32;   // force greater than threshold to shake hands
int releaseValue = 16; // value below which to expect fsr is released

boolean pressed;       // indicates if fsr is currently being pressed

Servo myservo;         // creates a servo object (from servo library)
int servoPin = 5;      // an unused pwm pin: 3, 5, 6, 9, 10, 11 or 13

// initialize led, servo pins. attach servo and set its position to 0

void setup() {
  pinMode(ledPin, OUTPUT);
  
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);

  myservo.write(0);
  delay(5);
}

// we divide both potVal and fsrVal by 4 because the arduino's analog
// input ranges from 0-1023 but analog (pwm) output ranges from 0-256

void loop() {
  potValue = analogRead(potPin) / 4;
  analogWrite(ledPin, potValue);
  
  fsrValue = analogRead(fsrPin) / 4;
  if (fsrValue > pressValue) {
    pressed = true;
  }
  
  if (pressed) {
    if (fsrValue < releaseValue) {
      for (int pos = 0; pos <= 90; pos++) {
        myservo.write(pos);
        delay(5);
      } 
      for (int pos = 90; pos >= 0; pos--) {
        myservo.write(pos);
        delay(5);
      }
      pressed = false;
    }
  }
}
