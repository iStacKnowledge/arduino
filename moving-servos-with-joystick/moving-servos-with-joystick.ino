#include <Servo.h>

int servoxPin = 9;
int servoyPin = 10;
int buzzPin = 11;
int ledPin = 12;
int readxPin = A0;
int readyPin = A1;
int switchPin = A2;
float servoxVal = 0;
float servoyVal = 0;
int dv = 250;

Servo xServo;
Servo yServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(readxPin, INPUT);
  pinMode(readyPin, INPUT);
  pinMode(switchPin, INPUT);
  xServo.attach(servoxPin);
  yServo.attach(servoyPin);
  xServo.write(0);
  yServo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int switchReadVal = analogRead(switchPin);
  Serial.print("Switch value: ");
  Serial.println(switchReadVal);
  if (switchReadVal == 0) {
    flash();
  }

  float tempServoxVal = analogRead(readxPin);
  float tempServoyVal = analogRead(readyPin);
  Serial.print("X value: ");
  Serial.print(tempServoxVal);
  Serial.print("Y value: ");
  Serial.print(tempServoyVal);
  if (tempServoxVal < 510) {
    if (servoxVal <= 0) {
      buzz();
      servoxVal = 0;
    } else {
      servoxVal = servoxVal - 5;
    }
  } else if (tempServoxVal > 520) {
    if (servoxVal >= 180) {
      buzz();
      servoxVal = 180;
    } else {
      servoxVal = servoxVal + 5;
    }
  }

  if (tempServoyVal < 510) {
    if (servoyVal <= 0) {
      buzz();
      servoyVal = 0;
    } else {
      servoyVal = servoyVal - 5;
    }
  } else if (tempServoyVal > 520) {
    if (servoyVal >= 180) {
      buzz();
      servoyVal = 180;
    } else {
      servoyVal = servoyVal + 5;
    }
  }

  xServo.write(servoxVal);
  yServo.write(servoyVal);
  Serial.print(" | ");
  Serial.print("X value: ");
  Serial.print(servoxVal);
  Serial.print("Y value: ");
  Serial.println(servoyVal);
  delay(dv);
}

void buzz() {
  digitalWrite(buzzPin, HIGH);
  delay(200);
  digitalWrite(buzzPin, LOW);
}

void flash() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
}