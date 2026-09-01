int readPin = A0;
int readVal;
int dv = 250;
int redPin = 13;
int greenPin = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readVal = analogRead(readPin);
  Serial.println(readVal);
  delay(dv);
  if(readVal > 400){
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
  }else{
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
}
