#include <Servo.h>

int readPin = A0;
int readVal;
int dv = 250;
int ledRed = 3;
int ledGreen = 5;
int ledBlue = 6;
int servoPin = 9;
float servoVal = 0;
Servo myServo;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  readVal = analogRead(readPin);
  Serial.print(readVal);
  servoVal = (readVal * 180.) / 1024.;
  Serial.print(" => ");
  Serial.println(servoVal);
  myServo.write(servoVal);
  if (servoVal < 25) {
    analogWrite(ledRed, 148);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 211);
  } else if (servoVal < 51) {
    analogWrite(ledRed, 75);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 130);
  } else if (servoVal < 77) {
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 255);
  } else if (servoVal < 103) {
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 255);
    analogWrite(ledBlue, 0);
  } else if (servoVal < 128) {
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 255);
    analogWrite(ledBlue, 0);
  } else if (servoVal < 154) {
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 127);
    analogWrite(ledBlue, 0);
  } else if (servoVal < 180) {
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 0);
  } else {
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 0);
  }
  myServo.write(servoVal);
  delay(dv);
}
