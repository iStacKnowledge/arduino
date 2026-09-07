# Push Button LED Dimmer with Buzzer Alert

A feature-rich Arduino project that controls LED brightness using dual push buttons (Increase & Decrease) with pulse-width modulation (PWM). When the LED reaches its maximum (255) or minimum (0) brightness limit, an audible feedback beep is triggered using a piezo buzzer.

---

## 📌 Features

- **Dynamic PWM Dimming**: Adjust LED brightness in steps of 10 (`0` to `255`) using PWM on Pin 9.
- **Audible Limit Warning**: Buzzer emits a 200ms beep when attempting to increase past maximum (`255`) or decrease below minimum (`0`).
- **Serial Diagnostics**: Real-time logging of button presses and brightness values over Serial Monitor at `9600` baud.
- **Button Debouncing**: Software delay handling to prevent erratic reading during button presses.

---

## 🛠️ Required Components

| Component | Quantity | Description / Value |
| :--- | :---: | :--- |
| **Arduino Board** | 1 | Arduino Uno / Nano / Mega |
| **Push Buttons** | 2 | Momentary Tactile Switches (Plus & Minus) |
| **LED** | 1 | Standard 5mm LED (Any color) |
| **Resistor** | 1 | 220Ω (Current limiting for LED) |
| **Resistors** | 2 | 10kΩ (Pull-down resistors for buttons) |
| **Piezo Buzzer** | 1 | 5V Active or Passive Buzzer |
| **Breadboard & Wires** | 1 | Breadboard & Male-to-Male Jumper Wires |

---

## 🔌 Circuit Pin Connections

| Arduino Pin | Connected To | Description | Wiring Details |
| :--- | :--- | :--- | :--- |
| **A2** | Plus Button | Increase Brightness Input | Button terminal to **A2**, with 10kΩ pull-down resistor to **GND** & switch terminal to **5V** |
| **A3** | Minus Button | Decrease Brightness Input | Button terminal to **A3**, with 10kΩ pull-down resistor to **GND** & switch terminal to **5V** |
| **Pin 9 (PWM)** | LED Anode (+) | PWM Brightness Output | Pin 9 ➔ 220Ω Resistor ➔ LED Anode (+), LED Cathode (-) to **GND** |
| **Pin 10** | Buzzer (+) | Audio Alert Output | Pin 10 ➔ Buzzer (+ / Red wire), Buzzer (-) to **GND** |
| **5V** | Power Rail | Button Power | Connected to switch pin of both push buttons |
| **GND** | Ground Rail | Common Ground | Connected to LED cathode, Buzzer (-), and pull-down resistors |

---

## ⚙️ How It Works

1. **Initial State**: Brightness is initialized to `0` (LED Off).
2. **Increasing Brightness (Pin A2)**:
   - When the **Plus Button** is pressed (`A2` goes `HIGH`), `ledBrightness` increments by `10`.
   - `analogWrite(9, ledBrightness)` updates the PWM duty cycle on Pin 9.
   - If `ledBrightness` reaches maximum (`255`), pressing the Plus button sounds the buzzer on Pin 10 for `200ms`.
3. **Decreasing Brightness (Pin A3)**:
   - When the **Minus Button** is pressed (`A3` goes `HIGH`), `ledBrightness` decrements by `10`.
   - `analogWrite(9, ledBrightness)` updates the PWM duty cycle on Pin 9.
   - If `ledBrightness` drops below `10`, it resets to `0` (Off) and sounds the buzzer on Pin 10 for `200ms`.
4. **Serial Logging**: Logs the status and current brightness value to the Serial Monitor at `9600` baud.

---

## 💻 Code Reference

The primary source file is [`pushButton-ledDim-buzzer.ino`](file:///c:/Users/sharm/Documents/arduino/pushButton-ledDim-buzzer/pushButton-ledDim-buzzer.ino).

```cpp
int plusBtn = A2;
int minusBtn = A3;
int ledPin = 9;
int buzzPin = 10;
int ledBrightness = 0;
```

---

## 🚀 How to Run

1. Open [pushButton-ledDim-buzzer.ino](file:///c:/Users/sharm/Documents/arduino/pushButton-ledDim-buzzer/pushButton-ledDim-buzzer.ino) in the **Arduino IDE**.
2. Connect your Arduino board via USB and select the appropriate **Board** and **Port** under `Tools`.
3. Click **Upload** (or press `Ctrl + U`).
4. Open the **Serial Monitor** (`Ctrl + Shift + M`) set to **9600 baud** to view real-time brightness logs.
