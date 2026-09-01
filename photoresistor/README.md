# Photoresistor Light Sensor Indicator (`photoresistor`)

An Arduino project that measures ambient light levels using a photoresistor (Light Dependent Resistor / LDR) configured in a voltage divider circuit and toggles between a Green and Red LED based on a configurable brightness threshold (`400` / ~1.95V), while streaming live analog telemetry to the Serial Monitor.

---

## 📌 Overview

A photoresistor (LDR) is a light-controlled variable resistor whose resistance decreases significantly as light intensity increases. Because an Arduino's analog pins only measure *voltage* (not raw resistance), the LDR is paired with a fixed $10\text{ k}\Omega$ resistor to form a **voltage divider**.

The Arduino continuously reads the analog voltage at pin **A0** (quantized from `0` to `1023`), prints the raw ADC value over Serial every 250 ms, and evaluates the light level:
- **Bright / Illuminated** (`readVal > 400`): Turns **ON** the **Green LED** (Pin 12) and turns **OFF** the **Red LED** (Pin 13).
- **Dark / Shadowed** (`readVal <= 400`): Turns **ON** the **Red LED** (Pin 13) and turns **OFF** the **Green LED** (Pin 12).

### Key Features
- **Analog Light Sensing**: Continuously samples ambient brightness using Arduino's 10-bit ADC (`A0`).
- **Dual-State Threshold Logic**: Clean visual status indication via Green (adequate light) and Red (low light / dark) LEDs.
- **Real-Time Serial Telemetry**: Streams live sensor readings over UART at `9600` baud.
- **Low Power & Responsive**: Updates every 250 ms for smooth and prompt state transitions.

---

## 🛠️ Components Required

| Component | Quantity | Description / Notes |
| :--- | :---: | :--- |
| **Arduino Board** | 1 | Arduino Uno, Nano, Mega, or compatible |
| **Photoresistor (LDR)** | 1 | Standard 5mm Light Dependent Resistor (e.g., GL5528) |
| **Voltage Divider Resistor** | 1 | $10\text{ k}\Omega$ resistor (Brown-Black-Orange) |
| **Current Limiting Resistors** | 2 | $220\Omega\text{ to }330\Omega$ (for Red and Green LEDs) |
| **LED (Green)** | 1 | Standard 5mm LED for "Light Detected" state |
| **LED (Red)** | 1 | Standard 5mm LED for "Dark / Low Light" state |
| **Breadboard** | 1 | Solderless breadboard for prototyping |
| **Jumper Wires** | Several | Male-to-Male (M-M) jumper wires |
| **USB Cable** | 1 | Type-A/B or Mini/Micro-USB for programming & power |

---

## 💡 How the Circuit Works

### 1. The LDR Voltage Divider Principle

An LDR's resistance ($R_{\text{LDR}}$) is dynamic:
- In **bright light**: Resistance drops to $\approx 500\Omega - 5\text{ k}\Omega$.
- In **complete darkness**: Resistance increases to $\approx 100\text{ k}\Omega - 2\text{ M}\Omega$.

By placing the LDR in series with a fixed $R_{\text{fixed}} = 10\text{ k}\Omega$ resistor connected between **5V** and **GND**, the voltage sampled at the center junction ($V_{\text{A0}}$) is:

$$V_{\text{A0}} = 5\text{V} \times \left( \frac{R_{\text{fixed}}}{R_{\text{LDR}} + R_{\text{fixed}}} \right) = 5\text{V} \times \left( \frac{10\text{ k}\Omega}{R_{\text{LDR}} + 10\text{ k}\Omega} \right)$$

- **Bright light** $\rightarrow R_{\text{LDR}}$ is low $\rightarrow$ Most of the 5V drops across $R_{\text{fixed}} \rightarrow V_{\text{A0}}$ **rises** (higher ADC value).
- **Darkness** $\rightarrow R_{\text{LDR}}$ is high $\rightarrow$ Most voltage drops across the LDR $\rightarrow V_{\text{A0}}$ **falls** (lower ADC value).

```
          +5V (VCC)
             │
             │
         ┌───┴───┐
         │  LDR  │  (Light Dependent Resistor)
         └───┬───┘
             │
             ├───────────────> To Analog Pin A0 (readPin)
             │
         ┌───┴───┐
         │  10kΩ │  (Fixed Pull-Down Resistor)
         └───┬───┘
             │
             │
          GND (Ground)
```

---

### 2. Component Pinouts

#### Photoresistor (LDR)
The photoresistor is non-polar (either leg can connect to 5V or the A0 junction).
```
         ┌─────────┐
         │ ( ~ ~ ) │  Light-sensitive face
         └──┬───┬──┘
            │   │     (No polarity)
```

#### Standard 5mm LEDs
LEDs are polarized components:
```
             ┌─────┐
             │ LED │
             └──┬──┘
                │ │
      Anode (+) │ │ Cathode (-) [Flat notch side / Shorter leg]
     [Long Leg] │ │
```

---

## 🔌 Pin Connections & Wiring Table

| Arduino Pin | Connected Component | Component Pin / Terminal | Notes |
| :--- | :--- | :--- | :--- |
| **5V** | Photoresistor (LDR) | Leg 1 | Connected to +5V Power Rail |
| **Analog A0** | LDR + $10\text{ k}\Omega$ Resistor | Common Junction | Samples variable voltage ($0\text{V} - 5\text{V}$) |
| **GND** | $10\text{ k}\Omega$ Resistor | Leg 2 | Connected to common Ground Rail |
| **Digital 12** | $220\Omega$ Resistor $\rightarrow$ Green LED | Resistor $\rightarrow$ Anode (+) | Drives Green LED (`HIGH` when `readVal > 400`) |
| **Digital 13** | $220\Omega$ Resistor $\rightarrow$ Red LED | Resistor $\rightarrow$ Anode (+) | Drives Red LED (`HIGH` when `readVal <= 400`) |
| **GND** | Green LED & Red LED | Cathode (-) [Shorter leg] | Both cathodes connected to Ground Rail |

---

## 💻 How the Code Works

Here is the complete sketch code from [`photoresistor.ino`](./photoresistor.ino):

```cpp
int readPin = A0;
int readVal;
int dv = 250;
int redPin = 13;
int greenPin = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readVal = analogRead(readPin);
  Serial.println(readVal);
  delay(dv);
  if(readVal > 400){
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
  }else{
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
}
```

### Step-by-Step Breakdown:

1. **Pin & Variable Declarations**:
   - `readPin = A0`: Assigns analog pin `A0` to read voltage from the LDR voltage divider.
   - `redPin = 13` & `greenPin = 12`: Digital pins driving the red and green indicator LEDs.
   - `dv = 250`: Delay duration in milliseconds between sensor read cycles (4 samples per second).

2. **Initialization (`setup`)**:
   - `pinMode(readPin, INPUT)` configures pin `A0` for analog voltage measurement.
   - `pinMode(redPin, OUTPUT)` and `pinMode(greenPin, OUTPUT)` set pins `13` and `12` as output drivers.
   - `Serial.begin(9600)` initializes UART communication at 9600 baud for telemetry output.

3. **Analog Conversion (`analogRead`)**:
   - `readVal = analogRead(readPin)` quantizes the voltage ($0\text{V} - 5\text{V}$) into an integer between `0` and `1023`:
     $$V_{\text{in}} = \frac{\text{readVal}}{1023} \times 5.0\text{V}$$
   - At threshold `readVal = 400`:
     $$V_{\text{threshold}} = \frac{400}{1023} \times 5.0\text{V} \approx 1.955\text{ V}$$

4. **Conditional Threshold Logic (`if-else`)**:
   - **When `readVal > 400`** (Bright environment / Light detected):
     - `digitalWrite(greenPin, HIGH)` $\rightarrow$ Lights up the Green LED.
     - `digitalWrite(redPin, LOW)` $\rightarrow$ Turns off the Red LED.
   - **When `readVal <= 400`** (Dark environment / Sensor covered):
     - `digitalWrite(redPin, HIGH)` $\rightarrow$ Lights up the Red LED.
     - `digitalWrite(greenPin, LOW)` $\rightarrow$ Turns off the Green LED.

5. **Telemetry & Delay**:
   - `Serial.println(readVal)` broadcasts the instantaneous reading to the Serial Monitor.
   - `delay(dv)` pauses for 250 ms before the next cycle.

---

## 🔢 Threshold & Operating State Reference

| Ambient Condition | Typical LDR Resistance ($R_{\text{LDR}}$) | Voltage at A0 ($V_{\text{A0}}$) | ADC Value (`readVal`) | Green LED (Pin 12) | Red LED (Pin 13) | System Status |
| :--- | :---: | :---: | :---: | :---: | :---: | :--- |
| **Bright Sunlight / Flashlight** | $\approx 500\Omega - 2\text{ k}\Omega$ | $4.1\text{V} - 4.7\text{V}$ | `850 – 970` | **ON** | **OFF** | High Ambient Light |
| **Typical Indoor Room Light** | $\approx 5\text{ k}\Omega - 10\text{ k}\Omega$ | $2.5\text{V} - 3.3\text{V}$ | `512 – 680` | **ON** | **OFF** | Adequate Room Light |
| **Threshold Border** | $\approx 15.5\text{ k}\Omega$ | $\approx 1.95\text{V}$ | `400` | **OFF** | **ON** | Threshold Switching Point |
| **Dim Light / Shadow** | $\approx 25\text{ k}\Omega - 50\text{ k}\Omega$ | $0.8\text{V} - 1.4\text{V}$ | `180 – 300` | **OFF** | **ON** | Low Light Detected |
| **Total Darkness (Covered)** | $> 200\text{ k}\Omega$ | $< 0.25\text{V}$ | `0 – 50` | **OFF** | **ON** | Dark / Night State |

---

## ⚙️ Calibration & Customization Tips

> [!TIP]
> **Calibrating for Your Room Lighting**:
> 1. Open the **Serial Monitor** at `9600` baud.
> 2. Observe the value in regular room light (e.g., `550`) and when covering the LDR with your finger (e.g., `120`).
> 3. Choose a midpoint value between light and dark:
>    $$\text{Threshold} = \frac{\text{Value}_{\text{Light}} + \text{Value}_{\text{Dark}}}{2}$$
> 4. Update `if (readVal > 400)` with your calibrated midpoint.

> [!NOTE]
> **Automatic Night-Light Mode (Inverted Logic)**:
> If you want an automatic night-lamp that turns ON a light only when it is dark, simply connect your lamp/LED to `redPin` (Pin 13) or invert the `if` condition:
> ```cpp
> if (readVal < 300) {
>   digitalWrite(nightLampPin, HIGH); // Turn ON light when dark
> } else {
>   digitalWrite(nightLampPin, LOW);  // Turn OFF light during day
> }
> ```

---

## 🚀 Getting Started & Upload Instructions

1. **Assemble the Circuit**: Build the voltage divider and LED circuits on your breadboard according to the wiring table and diagram above.
2. **Open the Sketch**: Launch the Arduino IDE and open [`photoresistor.ino`](./photoresistor.ino).
3. **Select Board & Port**:
   - Go to **Tools > Board** and select your board (e.g., *Arduino Uno*).
   - Go to **Tools > Port** and select the active COM/Serial port.
4. **Compile & Upload**:
   - Click **Verify** (✓) to compile the code.
   - Click **Upload** (➔) to flash the sketch onto your Arduino.
5. **Open Serial Monitor**:
   - Press `Ctrl + Shift + M` (Windows) / `Cmd + Shift + M` (macOS) and set the baud rate to **9600**.
6. **Test the Sensor**:
   - In normal room light, the **Green LED** should be ON.
   - Cover the photoresistor with your hand or finger: the Green LED will turn OFF and the **Red LED** will turn ON immediately!
