# RGB LED VIBGYOR Rainbow Spectrum

A project demonstrating color mixing with a Common Cathode RGB LED and an Arduino using Pulse Width Modulation (PWM) to cycle through all 7 colors of the rainbow spectrum (**VIBGYOR**): Violet, Indigo, Blue, Green, Yellow, Orange, and Red.

---

## 📌 Overview

An RGB LED contains three separate Light Emitting Diodes (Red, Green, and Blue) inside a single package. By applying varying analog voltages using Arduino's PWM pins (`analogWrite(pin, 0-255)`), we can mix the intensities of the three primary colors to generate intermediate colors in the visible spectrum.

This sketch cycles through the 7 rainbow (VIBGYOR) colors sequentially with a 1-second delay between each transition, logging the color index to the Serial Monitor at 9600 baud.

### PWM Output Pins:
- **Red LED**: Pin `3` (PWM ~)
- **Green LED**: Pin `5` (PWM ~)
- **Blue LED**: Pin `6` (PWM ~)

---

## 🛠️ Components Required

| Component | Quantity | Description / Notes |
| :--- | :--- | :--- |
| **Arduino Board** | 1 | Arduino Uno, Nano, or compatible board |
| **RGB LED** | 1 | **Common Cathode** (4-pin diffused or clear) |
| **Current Limiting Resistors** | 3 | 220Ω – 330Ω (for Red, Green, and Blue channels) |
| **Breadboard** | 1 | Standard half or full breadboard |
| **Jumper Wires** | Several | Male-to-Male jumper wires |
| **USB Cable** | 1 | For powering & programming the Arduino |

---

## 💡 RGB LED Pinout (Common Cathode)

Looking at the flat side / legs of the 4-pin RGB LED:

```
        ┌─────────────┐
        │   RGB LED   │
        └──────┬──────┘
         │  │  │  │
         │  │  │  │
         │  │  │  └──── Pin 4: Blue Anode (+)
         │  │  └─────── Pin 3: Green Anode (+)
         │  └────────── Pin 2: Common Cathode (-) [Longest Leg]
         └───────────── Pin 1: Red Anode (+)
```

> [!NOTE]
> The **Common Cathode** (longest leg) connects to **GND**. The other three pins are positive anodes for each color channel.

---

## 🔌 Circuit Connection & Wiring

| Arduino Pin | RGB LED Pin | Component in Series | Notes |
| :--- | :--- | :--- | :--- |
| **Digital Pin 3 (PWM ~)** | **Pin 1 (Red Anode)** | 220Ω Resistor | Controls Red brightness (0–255) |
| **GND** | **Pin 2 (Cathode)** | Direct connection | Common Ground (Longest leg) |
| **Digital Pin 5 (PWM ~)** | **Pin 3 (Green Anode)**| 220Ω Resistor | Controls Green brightness (0–255) |
| **Digital Pin 6 (PWM ~)** | **Pin 4 (Blue Anode)** | 220Ω Resistor | Controls Blue brightness (0–255) |

---

## 📐 Circuit Diagram

### Schematic View

```
                 +-----------------------------------+
                 |            ARDUINO UNO            |
                 |                                   |
                 |  [D3 (PWM ~)] ---[ 220Ω ]----+----> Pin 1 (Red Anode)
                 |                                   |
                 |  [  GND     ] --------------------> Pin 2 (Common Cathode)
                 |                                   |   (Longest Leg)
                 |  [D5 (PWM ~)] ---[ 220Ω ]----+----> Pin 3 (Green Anode)
                 |                                   |
                 |  [D6 (PWM ~)] ---[ 220Ω ]----+----> Pin 4 (Blue Anode)
                 |                                   |
                 +-----------------------------------+
```

## 🌈 VIBGYOR Color & PWM Values Table

The code implements the standard 7 VIBGYOR rainbow spectrum colors using 8-bit PWM values (range `0` to `255`):

| Index | Color | Color Sample | Red (Pin 3) | Green (Pin 5) | Blue (Pin 6) | Hex Code |
| :---: | :--- | :---: | :---: | :---: | :---: | :---: |
| **0** | **Violet** | 🟪 | `148` | `0` | `211` | `#9400D3` |
| **1** | **Indigo** | 🟦 | `75` | `0` | `130` | `#4B0082` |
| **2** | **Blue** | 🟦 | `0` | `0` | `255` | `#0000FF` |
| **3** | **Green** | 🟩 | `0` | `255` | `0` | `#00FF00` |
| **4** | **Yellow** | 🟨 | `255` | `255` | `0` | `#FFFF00` |
| **5** | **Orange** | 🟧 | `255` | `127` | `0` | `#FF7F00` |
| **6** | **Red** | 🟥 | `255` | `0` | `0` | `#FF0000` |

---

## 💻 How the Code Works

1. **Pin Initialization**: Digital pins 3, 5, and 6 are configured as `OUTPUT` in `setup()` and Serial communication is started at 9600 baud.
2. **Loop Sequence**: A `for` loop cycles through index `0` to `6`:
   ```cpp
   for (int i = 0; i < 7; i++) {
       writeLEDs(i);
       delay(1000); // Wait for 1 second per color
   }
   ```
3. **Color Modulation (`analogWrite`)**: The `writeLEDs()` helper matches the index against pre-calibrated RGB duty cycles to emit the corresponding wavelength/hue.

---

## ⚠️ Common Anode vs Common Cathode

If using a **Common Anode** RGB LED instead:
- Connect Pin 2 (longest leg) to **5V** instead of GND.
- Invert the PWM values in code: replace `value` with `255 - value` (e.g. `analogWrite(ledRed, 255 - 148)`).

---

## 🚀 Getting Started

1. Connect the circuit on your breadboard as shown above.
2. Open [`rbg-led-vibgyor.ino`](./rbg-led-vibgyor.ino) in the Arduino IDE.
3. Connect your Arduino board via USB.
4. Select your board model (**Tools** $\rightarrow$ **Board**) and the appropriate COM port (**Tools** $\rightarrow$ **Port**).
5. Click **Upload** (Ctrl+U / Cmd+U).
6. Open the **Serial Monitor** (Ctrl+Shift+M) at 9600 baud to observe the color index changing every second!
