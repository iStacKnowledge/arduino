# Potentiometer LED Dimmer (`potentiometer-led-dim`)

An Arduino project that controls the brightness of an LED using a rotary potentiometer via Pulse Width Modulation (PWM) and outputs real-time ADC and PWM telemetry to the Serial Monitor.

---

## 📌 Overview

This project demonstrates how to read a variable analog input voltage from a potentiometer and convert it into a PWM duty cycle to smoothly dim or brighten an LED.

As the potentiometer knob turns, the voltage at analog pin **A2** varies between `0V` and `5V`. The Arduino's 10-bit Analog-to-Digital Converter (ADC) translates this into an integer between `0` and `1023`. The sketch scales this reading and uses `analogWrite()` on PWM pin **11** to modulate the average power delivered to the LED.

### Key Features
- **Analog Sensing**: Continuously reads potentiometer wiper voltage on analog pin **A2** (`0–1023`).
- **PWM Brightness Control**: Modulates LED brightness on digital PWM pin **11** (`analogWrite()`, 8-bit resolution `0–255`).
- **Serial Telemetry**: Streams real-time `potVal => LEDVal` readings to the Serial Monitor at `9600` baud.

---

## 🛠️ Components Required

| Component | Quantity | Description / Notes |
| :--- | :---: | :--- |
| **Arduino Board** | 1 | Arduino Uno, Nano, Mega, or compatible |
| **Potentiometer** | 1 | 10kΩ (or 5kΩ / 50kΩ / 100kΩ) rotary or slide potentiometer |
| **LED** | 1 | Green LED (or standard 5mm LED of any color) |
| **Current Limiting Resistor** | 1 | 220Ω – 330Ω (prevents excess current through LED) |
| **Breadboard** | 1 | Solderless breadboard |
| **Jumper Wires** | Several | Male-to-Male (M-M) jumper wires |
| **USB Cable** | 1 | Type-A/B or Mini/Micro-USB for programming & power |

---

## 💡 Component Pinouts

### 1. Rotary Potentiometer (3 Pins)
```
          [ Knob / Dial ]
         ┌───────────────┐
         │               │
         └───┬───┬───┬───┘
             │   │   │
             │   │   └──── Pin 3: GND (Ground)
             │   └──────── Pin 2: Wiper / Signal Output (0 to 5V)
             └──────────── Pin 1: VCC (+5V)
```

### 2. Standard 5mm LED
```
             ┌─────┐
             │ LED │
             └──┬──┘
               │ │
     Anode (+) │ │ Cathode (-) [Flat side / Shorter leg]
    [Long Leg] │ │
```

---

## 🔌 Pin Connections & Wiring Table

| Arduino Pin | Component | Component Pin / Terminal | Notes |
| :--- | :--- | :--- | :--- |
| **5V** | Potentiometer | **Pin 1 (VCC)** | Outer pin connected to 5V power rail |
| **GND** | Potentiometer | **Pin 3 (GND)** | Outer pin connected to common Ground rail |
| **Analog A2** | Potentiometer | **Pin 2 (Wiper / SIG)** | Center wiper pin: variable 0–5V output |
| **Digital 11 (PWM ~)** | Resistor (220Ω) | **Terminal 1** | PWM brightness output pin |
| — | Resistor (220Ω) $\rightarrow$ LED | **Resistor T2 $\rightarrow$ Anode (+)** | Resistor in series with LED long leg |
| **GND** | LED | **Cathode (-)** | LED short leg connected to common Ground rail |

---

## 💻 How the Code Works

Here is the complete sketch code from [`potentiometer-led-dim.ino`](./potentiometer-led-dim.ino):

```cpp
int potPin = A2;
int gPin = 11;
int potVal;
float LEDVal;

void setup() {
  pinMode(potPin, INPUT);
  pinMode(gPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(potPin);

  LEDVal = (255. / 511.) * potVal;
  analogWrite(gPin, LEDVal);
  Serial.print(potVal);
  Serial.print("=>");
  Serial.println(LEDVal);
}
```

### Step-by-Step Breakdown:

1. **Variable & Pin Setup (`setup`)**:
   - `potPin = A2`: Designates analog pin `A2` as the input from the potentiometer wiper.
   - `gPin = 11`: Designates digital pin `11` (a hardware PWM pin denoted by `~`) as the LED output.
   - `Serial.begin(9600)`: Initializes UART communication at 9600 baud for telemetry output.

2. **Analog-to-Digital Sampling (`analogRead`)**:
   - `potVal = analogRead(potPin);` samples the analog voltage on pin `A2`.
   - The 10-bit ADC quantizes the voltage ($0\text{V} - 5\text{V}$) into integer values from `0` to `1023`:
     $$V_{\text{in}} = \frac{\text{potVal}}{1023} \times 5.0\text{V}$$

3. **Scaling & Transfer Function**:
   - The scaling formula used is:
     $$\text{LEDVal} = \left(\frac{255.0}{511.0}\right) \times \text{potVal} \approx 0.49902 \times \text{potVal}$$
   - **Range characteristics**:
     - At `potVal = 0` ($0\text{V}$), $\text{LEDVal} = 0$ (LED completely off).
     - At `potVal = 511` ($\approx 2.5\text{V}$, half knob turn), $\text{LEDVal} = 255.0$ (LED at 100% full brightness).
     - Full brightness is reached by the midpoint of the potentiometer travel.

4. **Pulse Width Modulation (`analogWrite`)**:
   - `analogWrite(gPin, LEDVal)` generates a rectangular wave at ~490 Hz on pin 11.
   - By modulating the duty cycle ($0\% \rightarrow 100\%$), the effective forward current and perceived brightness of the LED are smoothly controlled without flickering.

5. **Serial Telemetry Logging**:
   - `Serial.print(potVal); Serial.print("=>"); Serial.println(LEDVal);` streams the raw input and mapped output values to the Serial Monitor.

---

## 📊 Value Mapping Reference Table

| Potentiometer Position | Input Voltage ($V_{\text{in}}$) | ADC Value (`potVal`) | Calculated `LEDVal` | PWM Duty Cycle | LED State / Perceived Brightness |
| :---: | :---: | :---: | :---: | :---: | :--- |
| **Minimum (0%)** | $0.00\text{V}$ | `0` | `0.0` | $0\%$ | **OFF** |
| **Quarter Turn (25%)** | $1.25\text{V}$ | `256` | `127.7` | $50\%$ | **Medium Brightness** |
| **Half Turn (50%)** | $2.50\text{V}$ | `511` | `255.0` | $100\%$ | **Full Maximum Brightness** |
| **Three-Quarter (75%)** | $3.75\text{V}$ | `768` | `383.2` | $>100\%$ | **Full Brightness / Over-range** |
| **Maximum (100%)** | $5.00\text{V}$ | `1023` | `510.5` | $>100\%$ | **Full Brightness / Over-range** |

> [!TIP]
> **Full-Range Mapping Option:**
> If you wish to map the entire potentiometer rotation ($0\text{V} \rightarrow 5\text{V}$) across the full PWM range ($0 \rightarrow 255$), you can use Arduino's built-in `map()` function or scale by `(255. / 1023.)`:
> ```cpp
> LEDVal = map(potVal, 0, 1023, 0, 255);
> // OR
> LEDVal = (255.0 / 1023.0) * potVal;
> ```

---

## 🚀 Getting Started & Upload Instructions

1. **Assemble the Circuit**: Connect the potentiometer, resistor, and LED on the breadboard following the wiring table and circuit diagram above.
2. **Open the Sketch**: Launch the Arduino IDE and open [`potentiometer-led-dim.ino`](./potentiometer-led-dim.ino).
3. **Select Board & Port**:
   - Go to **Tools > Board** and choose your board (e.g., *Arduino Uno*).
   - Go to **Tools > Port** and choose the active serial COM port.
4. **Compile & Upload**:
   - Click **Verify** (✓) to check for syntax errors.
   - Click **Upload** (➔) to flash the program onto the Arduino.
5. **Open Serial Monitor / Plotter**:
   - Press `Ctrl + Shift + M` (Windows/Linux) or `Cmd + Shift + M` (macOS) to open the **Serial Monitor**.
   - Set the baud rate dropdown to **9600 baud**.
   - Rotate the potentiometer knob to watch the LED dim/brighten in real time while tracking the live readings!
