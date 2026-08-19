int readPin = A2;

void setup() {
  pinMode(readPin, INPUT);
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  int sensorValue = analogRead(readPin);
  float voltage =
      sensorValue * (5.0 / 1023.0); // Convert the analog reading to voltage
  Serial.print("Voltage: ");
  Serial.println(voltage);
  delay(1000); // Wait for 1 second before the next reading
}