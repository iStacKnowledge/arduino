int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;


void setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
}

void loop() {
    for (int i = 0; i < 16; i++) {
        writeLEDs(i);
        delay(1000); // Wait for 1 second
    }
}

void writeLEDs(int value) {
    digitalWrite(led1, (value >> 0) & 1); // Write the least significant bit to led1
    digitalWrite(led2, (value >> 1) & 1); // Write the second bit to led2
    digitalWrite(led3, (value >> 2) & 1); // Write the third bit to led3
    digitalWrite(led4, (value >> 3) & 1); // Write the fourth bit to led4
}