# Potentiometer Threshold Buzzer Alarm (`buzzer-potentiometer`)

An Arduino project that monitors an analog input from a rotary potentiometer and triggers an audible buzzer alarm whenever the dialed value exceeds a predefined threshold (`> 1000` / ~4.89V).

---

## 📌 Overview

This project demonstrates analog input sensing coupled with digital output control. As the potentiometer knob is rotated, the Arduino continuously samples the analog voltage on pin **A3** (mapped from `0` to `1023`). When the wiper voltage reaches the upper limit (`potVal > 1000`), the Arduino drives digital pin **8** `HIGH`, activating the buzzer until the potentiometer is dialed back below the threshold.

### Key Features
- **Analog Input Sampling**: Reads variable voltage via Arduino's 10-bit ADC (`A3`).
- **Threshold-Based Trigger**: Uses a conditional `while` loop to maintain the alarm state while the threshold is breached.
- **Audible Indicator**: Activates a buzzer on digital pin **8**.

---

## 🛠️ Components Required

| Component | Quantity | Description / Notes |
| :--- | :---: | :--- |
| **Arduino Board** | 1 | Arduino Uno, Nano, Mega, or compatible |
| **Potentiometer** | 1 | 10kΩ (or 5kΩ / 50kΩ / 100kΩ) rotary or slide potentiometer |
| **Buzzer** | 1 | 5V Active Buzzer (or Piezo buzzer) |
| **Breadboard** | 1 | Standard half or full solderless breadboard |
| **Jumper Wires** | Several | Male-to-Male (M-M) jumper wires |
| **USB Cable** | 1 | Type-A/B or Mini/Micro-USB for programming & power |

---

## 🔌 Pin Connections & Wiring Table

| Arduino Pin | Component | Component Pin / Terminal | Notes |
| :--- | :--- | :--- | :--- |
| **5V** | Potentiometer | **Pin 1 (VCC)** | Outer leg connected to 5V power rail |
| **GND** | Potentiometer | **Pin 3 (GND)** | Outer leg connected to Ground rail |
| **Analog A3** | Potentiometer | **Pin 2 (Wiper / SIG)** | Center leg: variable output voltage (0–5V) |
| **Digital 8** | Buzzer | **Positive (+) / Anode (Long leg)** | Digital output control (HIGH = Sound ON) |
| **GND** | Buzzer | **Negative (-) / Cathode (Short leg)** | Common Ground return |

---

## 💻 How the Code Works

```cpp
int buzzPin = 8;
int potPin = A3;
int potVal;

void setup() {
  pinMode(buzzPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  potVal = analogRead(potPin);
  while(potVal > 1000){
    digitalWrite(buzzPin, HIGH);
    potVal = analogRead(potPin);
  }
  digitalWrite(buzzPin, LOW);
}
```

### Logic Breakdown:
1. **Pin Assignment & Configuration (`setup`)**:
   - `pinMode(buzzPin, OUTPUT)` sets pin `8` to drive the buzzer.
   - `pinMode(potPin, INPUT)` configures pin `A3` to receive analog voltage signals.

2. **Analog-to-Digital Conversion (`ADC`)**:
   - `analogRead(potPin)` samples voltage between `0V` and `5V` and quantizes it into integer values from `0` to `1023`.
   - The threshold `1000` corresponds to:
     $$\text{Trigger Voltage} = \frac{1000}{1023} \times 5.0\text{V} \approx 4.888\text{V}$$

3. **Active Alarm Loop (`while`)**:
   - If `potVal > 1000`, the program enters the `while` block, driving pin `8` `HIGH` to sound the buzzer.
   - Inside the loop, it continuously resamples `A3` (`potVal = analogRead(potPin)`).
   - Once the user rotates the potentiometer knob below the threshold ($\le 1000$), the loop exits and `digitalWrite(buzzPin, LOW)` silences the buzzer.

---

## 💡 Buzzer Notes (Active vs. Passive)

- **Active Buzzer (Recommended)**: Contains an internal oscillating circuit. Applying a DC voltage (`digitalWrite(buzzPin, HIGH)`) produces a steady tone automatically.
- **Passive Buzzer**: Requires an oscillating AC signal / PWM wave (such as using Arduino's `tone(pin, frequency)` function) to emit sound. With simple `digitalWrite` HIGH/LOW, a passive buzzer will only produce a faint click.

---

## 🚀 Getting Started & Upload Instructions

1. **Wire the Circuit**: Assemble the potentiometer and buzzer on your breadboard following the circuit diagram above.
2. **Open the Sketch**: Launch the Arduino IDE and open [`buzzer-potentiometer.ino`](./buzzer-potentiometer.ino).
3. **Select Board & Port**:
   - Navigate to **Tools > Board** and select your board (e.g. *Arduino Uno*).
   - Navigate to **Tools > Port** and select your active COM/Serial port.
4. **Compile & Upload**:
   - Click **Verify** (✓) to compile.
   - Click **Upload** (➔) to flash the code to the board.
5. **Test the Alarm**:
   - Turn the potentiometer knob clockwise towards maximum.
   - Once the dial crosses ~97.7% of its travel range (`potVal > 1000`), the buzzer will sound.
   - Rotate the knob counter-clockwise to silence the alarm.
