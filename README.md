# Arduino Hobby Experiments & Learning

Welcome to my personal Arduino repository! 👋

This repository contains a collection of very basic sample Arduino experiments, circuits, and sketches created as I learn electronics and embedded programming as a hobby. Each project folder contains the sketch code (`.ino`), circuit diagrams/visuals, and documentation on how the circuit works.

---

## 🛠️ Basic Setup & Getting Started

### 1. Software Setup
To upload and run these experiments:
1. **Download & Install Arduino IDE**:
   - Download the latest [Arduino IDE](https://www.arduino.cc/en/software).
2. **Drivers (if needed)**:
   - Official boards install drivers automatically. If using clone boards with CH340 or CP2102 chips, ensure the appropriate USB-to-Serial drivers are installed.
3. **Configure Board & Port**:
   - Go to **Tools** > **Board** and select your board model (e.g., *Arduino Uno*, *Arduino Nano*).
   - Go to **Tools** > **Port** and select the active COM port assigned to your connected board.

---

### 2. Standard Hardware & Prototyping Essentials
Most experiments in this repository use standard starter kit components:
- **Microcontroller**: Arduino Uno R3, Nano, or compatible board
- **USB Cable**: Type-A/B (Uno) or Mini/Micro-USB (Nano) for power and programming
- **Prototyping**: Solderless breadboard and jumper wires (Male-to-Male / Male-to-Female)
- **Passive Components**: Current-limiting resistors (220Ω, 330Ω, 1kΩ, 10kΩ)
- **Output / Input Devices**: Standard LEDs, RGB LED, potentiometers, switches, etc.

---

### 3. How to Run an Experiment

1. **Clone or Download** this repository.
2. Open the desired experiment directory (e.g., `binary-led/`).
3. Open the `.ino` file in the **Arduino IDE**.
4. Connect the physical circuit according to the instructions and circuit diagram in the experiment's `README.md`.
5. Connect your Arduino board to your computer via USB.
6. Click **Verify** (✓) to compile the code.
7. Click **Upload** (➔) to flash the code to the board.
8. If the experiment uses serial output, open the **Serial Monitor** (`Ctrl + Shift + M` / `Cmd + Shift + M`) and set the baud rate matching `Serial.begin(...)` (e.g., `9600`).

---

## 📂 Included Experiments

| Experiment | Description | Key Concepts |
| :--- | :--- | :--- |
| [**binary-led**](./binary-led/) | 4-bit binary counter displaying 0 to 15 across 4 LEDs. | Digital outputs, binary logic, `digitalWrite()`, bitwise operations. |
| [**buzzer-potentiometer**](./buzzer-potentiometer/) | Threshold-triggered buzzer alarm controlled via analog potentiometer. | Analog input sensing, `analogRead()`, digital output threshold triggering. |
| [**potentiometer-led-dim**](./potentiometer-led-dim/) | LED brightness / dimmer control using rotary potentiometer. | ADC sampling (`analogRead`), PWM duty cycle modulation (`analogWrite`), Serial logging. |
| [**rbg-led-vibgyor**](./rbg-led-vibgyor/) | Color cycling an RGB LED through the VIBGYOR rainbow spectrum. | Pulse Width Modulation (PWM), `analogWrite()`, color mixing. |
| [**volt-read**](./volt-read/) | Reading analog input voltage and reporting it to the Serial Monitor. | ADC conversion, `analogRead()`, Serial communication (`Serial.print`). |

---

## 📝 Notes & Disclaimer

- These projects are basic hobby experiments created for self-learning and experimentation.
- Always double-check resistor values and polarities (especially for LEDs and external components) before powering your board to prevent component damage.

---

## 🙏 Acknowledgments & Special Thanks

A huge thank you to **Paul McWhorter** ([@paulmcwhorter](https://www.youtube.com/@paulmcwhorter)) — learned everything from his incredible Arduino tutorials and electronics lessons!

