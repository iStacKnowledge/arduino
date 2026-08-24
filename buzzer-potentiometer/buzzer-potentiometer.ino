int buzzPin = 8;
int potPin = A3;
int potVal;

void setup() {
  pinMode(buzzPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  potVal = analogRead(potPin);
  while(potVal > 1000){
    digitalWrite(buzzPin, HIGH);
    potVal=analogRead(potPin);
  }
  digitalWrite(buzzPin, LOW);
}
