int ledRed = 3;
int ledGreen = 5;
int ledBlue = 6;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 7; i++) {
        writeLEDs(i);
        delay(1000); // Wait for 1 second
  }
}

void writeLEDs(int value) {
  Serial.println(value);
  if(value == 0){
    analogWrite(ledRed, 148);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 211);
  } else if(value == 1){
    analogWrite(ledRed, 75);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 130);
  } else if(value == 2){
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 255);
  } else if(value == 3){
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 255);
    analogWrite(ledBlue, 0);
  } else if(value == 4){
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 255);
    analogWrite(ledBlue, 0);
  } else if(value == 5){
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 127);
    analogWrite(ledBlue, 0);
  } else if(value == 6){
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 0);
  } else {
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 0);
  }
    
}
