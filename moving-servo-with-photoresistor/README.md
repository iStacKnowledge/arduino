# Moving Servo with Photoresistor (LDR) & RGB LED Indicator

An Arduino project that controls a Servo Motor's angular position dynamically based on ambient light intensity detected by a Photoresistor (Light Dependent Resistor / LDR). The system also features a visual **RGB LED indicator** that shifts colors through the rainbow spectrum (VIBGYOR) corresponding to the angle/light level.

---

## 📌 Features

- **Light-Controlled Actuation**: Converts analog ambient light readings (0–1023) to servo rotation angles (0°–180°).
- **Visual Color Feedback**: Uses an RGB LED with PWM intensity values to display distinct color stages (Violet $\rightarrow$ Indigo $\rightarrow$ Blue $\rightarrow$ Green $\rightarrow$ Yellow $\rightarrow$ Orange $\rightarrow$ Red).
- **Real-Time Serial Monitoring**: Outputs ambient light values and converted servo angles over Serial communication at 9600 baud.

---

## 🛠️ Bill of Materials (BOM)

| Component | Quantity | Description |
| :--- | :---: | :--- |
| **Arduino Microcontroller** | 1 | Arduino Uno R3, Nano, or Mega |
| **Servo Motor** | 1 | Micro Servo Motor (e.g., SG90 or MG90S) |
| **Photoresistor (LDR)** | 1 | Standard 5mm Light Dependent Resistor |
| **RGB LED** | 1 | Common Cathode RGB LED (or 3 individual R, G, B LEDs) |
| **10 kΩ Resistor** | 1 | Pull-down resistor for LDR voltage divider |
| **220 Ω - 330 Ω Resistors** | 3 | Current-limiting resistors for RGB pins |
| **Breadboard & Jumper Wires** | 1 | Standard breadboard and M/M jumper wires |
| **Power Supply / USB Cable** | 1 | USB Type-A to Type-B cable for power and flashing |

---

## ⚡ Pin Connections

| Arduino Pin | Connected Component | Details / Wire Color |
| :--- | :--- | :--- |
| **5V** | LDR Pin 1 & Servo VCC | Power (+5V supply) |
| **GND** | 10kΩ Resistor, Servo GND, RGB LED Common Cathode | Ground reference |
| **A0** | LDR Pin 2 & 10kΩ Resistor Junction | Analog input for light sensor |
| **Pin 3 (PWM)** | RGB Red Anode (via 220Ω resistor) | PWM Red control |
| **Pin 5 (PWM)** | RGB Green Anode (via 220Ω resistor) | PWM Green control |
| **Pin 6 (PWM)** | RGB Blue Anode (via 220Ω resistor) | PWM Blue control |
| **Pin 9 (PWM)** | Servo Signal (Orange / Yellow Wire) | PWM Servo pulse control |

---

## 🌈 Color & Angle Mapping Table

| Servo Angle Range | Calculated Angle (`servoVal`) | Color Displayed | PWM Red (Pin 3) | PWM Green (Pin 5) | PWM Blue (Pin 6) | Hex Preview |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| $0^\circ \le \theta < 25^\circ$ | $< 25^\circ$ | **Violet** | 148 | 0 | 211 | `#9400D3` |
| $25^\circ \le \theta < 51^\circ$ | $< 51^\circ$ | **Indigo** | 75 | 0 | 130 | `#4B0082` |
| $51^\circ \le \theta < 77^\circ$ | $< 77^\circ$ | **Blue** | 0 | 0 | 255 | `#0000FF` |
| $77^\circ \le \theta < 103^\circ$ | $< 103^\circ$ | **Green** | 0 | 255 | 0 | `#00FF00` |
| $103^\circ \le \theta < 128^\circ$ | $< 128^\circ$ | **Yellow** | 255 | 255 | 0 | `#FFFF00` |
| $128^\circ \le \theta < 154^\circ$ | $< 154^\circ$ | **Orange** | 255 | 127 | 0 | `#FF7F00` |
| $154^\circ \le \theta < 180^\circ$ | $< 180^\circ$ | **Red** | 255 | 0 | 0 | `#FF0000` |
| $\ge 180^\circ$ | $\ge 180^\circ$ | **OFF** | 0 | 0 | 0 | `#000000` |

---

## 🧠 Code Walkthrough

1. **Sensor Reading & Scaling**:
   ```cpp
   readVal = analogRead(readPin);             // Read 0 to 1023 analog value from LDR
   servoVal = (readVal * 180.) / 1024.;       // Convert to floating point angle (0 to 180 degrees)
   ```
2. **Servo Actuation**:
   ```cpp
   myServo.write(servoVal);                   // Move servo shaft to the mapped angle
   ```
3. **RGB Indicator Control**:
   - The conditional `if-else if` block evaluates `servoVal` and updates the PWM duty cycle on digital pins 3, 5, and 6 to produce vibrant color transitions.

---

## 🚀 How to Run

1. Connect your Arduino board to your computer via USB.
2. Assemble the components according to the [Circuit Diagrams](#-circuit-diagrams).
3. Open [`moving-servo-with-photoresistor.ino`](moving-servo-with-photoresistor.ino) in **Arduino IDE**.
4. Make sure the default `<Servo.h>` library is available (included with standard Arduino IDE).
5. Select your target **Board** (e.g., *Arduino Uno*) and correct **COM Port** under `Tools`.
6. Click **Upload** ($\rightarrow$).
7. Open the **Serial Monitor** at **9600 baud** to view real-time sensor output values and mapped servo angles.
