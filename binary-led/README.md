# 4-Bit Binary LED Counter

A sample assembly of 4 LEDs configured with an Arduino to demonstrate counting from 0 to 15 (16 states) in binary format.

---

## 📌 Overview

This project uses 4 digital output pins on an Arduino board connected to 4 LEDs. Each LED represents a binary bit (from Least Significant Bit to Most Significant Bit):
- **LED 1 (Bit 0 / LSB - $2^0$)**: Pin 13
- **LED 2 (Bit 1 - $2^1$)**: Pin 12
- **LED 3 (Bit 2 - $2^2$)**: Pin 11
- **LED 4 (Bit 3 / MSB - $2^3$)**: Pin 10

The Arduino loops through values `0` to `15`, displaying each number as a 4-bit binary value with a 1-second delay between increments.

---

## 🛠️ Components Required

| Component | Quantity | Notes |
| :--- | :--- | :--- |
| **Arduino Board** (Uno / Nano / etc.) | 1 | Microcontroller |
| **LEDs** | 4 | Any color (e.g., Red / Green / Blue / Yellow) |
| **Current Limiting Resistors** | 4 | 220Ω to 330Ω |
| **Breadboard** | 1 | For assembly |
| **Jumper Wires** | Several | Male-to-Male |

---

## 🔌 Circuit Connection

1. Connect the **Anode** (longer leg) of each LED to the respective Arduino digital pin through a 220Ω resistor:
   - **LED 1 (LSB)** $\rightarrow$ **Pin 13**
   - **LED 2** $\rightarrow$ **Pin 12**
   - **LED 3** $\rightarrow$ **Pin 11**
   - **LED 4 (MSB)** $\rightarrow$ **Pin 10**
2. Connect the **Cathode** (shorter leg) of all 4 LEDs to the common **GND** rail on the breadboard.
3. Connect the breadboard **GND** rail to the Arduino **GND** pin.

---

## 🔢 Binary State Reference Table

| Decimal | Binary (MSB $\rightarrow$ LSB) | LED 4 (Pin 10) | LED 3 (Pin 11) | LED 2 (Pin 12) | LED 1 (Pin 13) |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **0** | `0000` | OFF | OFF | OFF | OFF |
| **1** | `0001` | OFF | OFF | OFF | ON |
| **2** | `0010` | OFF | OFF | ON | OFF |
| **3** | `0011` | OFF | OFF | ON | ON |
| **4** | `0100` | OFF | ON | OFF | OFF |
| **5** | `0101` | OFF | ON | OFF | ON |
| **6** | `0110` | OFF | ON | ON | OFF |
| **7** | `0111` | OFF | ON | ON | ON |
| **8** | `1000` | ON | OFF | OFF | OFF |
| **9** | `1001` | ON | OFF | OFF | ON |
| **10** | `1010` | ON | OFF | ON | OFF |
| **11** | `1011` | ON | OFF | ON | ON |
| **12** | `1100` | ON | ON | OFF | OFF |
| **13** | `1101` | ON | ON | OFF | ON |
| **14** | `1110` | ON | ON | ON | OFF |
| **15** | `1111` | ON | ON | ON | ON |

---

## 💻 How the Code Works

The core binary decoding is performed in the `writeLEDs` function using bitwise right-shift (`>>`) and bitwise AND (`&`):

```cpp
void writeLEDs(int value) {
    digitalWrite(led1, (value >> 0) & 1); // Extract bit 0 (LSB)
    digitalWrite(led2, (value >> 1) & 1); // Extract bit 1
    digitalWrite(led3, (value >> 2) & 1); // Extract bit 2
    digitalWrite(led4, (value >> 3) & 1); // Extract bit 3 (MSB)
}
```

---

## 🚀 Getting Started

1. Open [`binary-led.ino`](./binary-led.ino) in the Arduino IDE.
2. Select your board and COM port under **Tools**.
3. Click **Upload** and watch the LEDs count in binary!