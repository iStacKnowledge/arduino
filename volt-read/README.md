# Voltage Reader (volt-read)

An Arduino sketch to measure DC voltage (0–5V) using an analog input pin (`A2`) and print real-time voltage readings to the Serial Monitor.

---

## 📌 Overview

This project reads analog signals through Arduino's built-in 10-bit Analog-to-Digital Converter (ADC). It samples the input pin, converts the integer reading (0–1023) into an actual voltage value in volts (0.00V – 5.00V), and outputs the result via serial communication every second.

---

## ⚙️ Hardware Components

- **Arduino Board** (e.g., Uno, Nano, Mega)
- **Signal Source / Component to Measure** (e.g., potentiometer, battery with $< 5\text{V}$, or sensor output)
- **Breadboard & Jumper Wires**

---

## 🔌 Circuit Connection

| Arduino Pin | Connection | Note |
|---|---|---|
| **A2** | Analog Voltage Input (+) | Connect to signal / voltage source |
| **GND** | Ground (-) | Common ground with the measured source |

> [!WARNING]
> **Input Voltage Limits:** Arduino analog pins support a maximum input voltage of **5.0V DC** (when operating at 5V logic). Applying higher voltages or negative voltages can damage your microcontroller. To measure higher voltages, use a proper resistor voltage divider.

---

## 💻 Code Explanation

```cpp
int readPin = A2;

void setup() {
  pinMode(readPin, INPUT);
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  int sensorValue = analogRead(readPin);
  float voltage = sensorValue * (5.0 / 1023.0); // Convert the analog reading to voltage
  Serial.print("Voltage: ");
  Serial.println(voltage);
  delay(1000); // Wait for 1 second before the next reading
}
```

### Key Highlights
- **`analogRead(A2)`**: Returns an integer from `0` to `1023` corresponding to voltages between `0V` and `5V`.
- **Voltage Formula**: 
  $$\text{Voltage} = \text{sensorValue} \times \left(\frac{5.0}{1023.0}\right)$$
- **`Serial.begin(9600)`**: Configures serial transmission speed to 9600 baud.
- **`delay(1000)`**: Introduces a 1-second delay between consecutive readings.

---

## 🚀 How to Use

1. Open [`volt-read.ino`](volt-read.ino) in the **Arduino IDE**.
2. Connect your Arduino board to your computer via USB.
3. In the IDE, go to **Tools > Board** and select your Arduino model.
4. Go to **Tools > Port** and select the appropriate COM port.
5. Click **Upload** (Ctrl+U / Cmd+U).
6. Open the **Serial Monitor** (Ctrl+Shift+M / Cmd+Shift+M) and ensure the baud rate is set to **9600 baud**.
7. Observe the continuous voltage measurements printed every second.
