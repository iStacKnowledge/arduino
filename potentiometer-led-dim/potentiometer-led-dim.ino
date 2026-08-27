int potPin = A2;
int gPin = 11;
int potVal;
float LEDVal;

void setup() {
  pinMode(potPin, INPUT);
  pinMode(gPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(potPin);

  LEDVal = (255. / 511.) * potVal;
  analogWrite(gPin, LEDVal);
  Serial.print(potVal);
  Serial.print("=>");
  Serial.println(LEDVal);
}
