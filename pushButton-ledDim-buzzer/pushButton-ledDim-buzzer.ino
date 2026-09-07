int plusBtn = A2;
int minusBtn = A3;
int ledPin = 9;
int buzzPin = 10;
int ledBrightness = 0;
int btnPlusVal;
int btnMinusVal;

void setup() {
  pinMode(plusBtn, INPUT);
  pinMode(minusBtn, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  btnPlusVal = digitalRead(plusBtn);
  btnMinusVal = digitalRead(minusBtn);
  if(btnPlusVal == 1){
    Serial.print("Increase button pressed. Current brightness: ");
    Serial.println(ledBrightness);
    if(ledBrightness == 255){
      ledBrightness = 255;
      digitalWrite(buzzPin, HIGH);
      delay(200);
      digitalWrite(buzzPin, LOW);
    } else {
      ledBrightness += 10;
    }
    if(ledBrightness > 255){
      ledBrightness = 255;
    }
    analogWrite(ledPin, ledBrightness);
    delay(200); // Debounce delay
  }
  if(btnMinusVal == 1){
    Serial.print("Decrease button pressed. Current brightness: ");
    Serial.println(ledBrightness);
    if(ledBrightness < 10){
      ledBrightness = 0;
      digitalWrite(buzzPin, HIGH);
      delay(200);
      digitalWrite(buzzPin, LOW);
    } else {
      ledBrightness -= 10;
    }
    analogWrite(ledPin, ledBrightness);
    delay(200); // Debounce delay
  }
}
