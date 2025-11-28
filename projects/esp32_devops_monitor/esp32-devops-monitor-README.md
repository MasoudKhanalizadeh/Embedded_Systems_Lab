# ESP32 DevOps Mini Monitor

A small, closed, skill-focused embedded project that turns an ESP32 into a tiny “DevOps-style” monitor.  
It periodically reads **temperature**, **humidity**, and **ambient light**, displays them on an **OLED**, and prints structured logs to the **Serial Monitor**.

This project is part of my `embedded-systems-lab` – a collection of small embedded systems projects designed to strengthen low-level C, real-time loops, and system-level thinking.

---

## 🖼 Project Preview

**Photo:**  
![ESP32 DevOps Mini Monitor](./photo_2025-11-29_00-56-15.jpg)

**Demo Video:**  
*(Embedded_Systems_Lab/projects/esp32_devops_monitor/doc_2025-11-29_00-55-46.mp4)*

---

## 🎯 Objectives

This project is intentionally **small and closed**.  
The main learning goals are:

- Low-level C programming  
- Real-time loops using `millis()`  
- Hardware–software integration  
- Sensor interfacing (AHT10 + LDR)  
- OLED text rendering  
- DevOps-style structured logs  
- Thinking in small, focused system components

---

## 🧩 Features

- Reads **temperature** and **humidity** from AHT10  
- Reads **ambient light** from LDR  
- Displays values on a **0.96" OLED (128×64)**  
- Logs system status every **5 seconds**:

  ```
  [Log] Temp=24.3C  Hum=42.7%  Light=63%  Uptime=5032ms
  ```

- Uses **non-blocking `millis()`** pattern  
- Fully **closed** (no future extensions)

---

## 🛠 Hardware

- ESP32 DevKit V4 (WROOM-32U + CP2102)
- AHT10 temp/humidity sensor  
- OLED 0.96" I2C (128×64)  
- LDR module (HOYA, 3-pin, with 103 resistor)  
- Breadboard + jumper wires  

---

## 🔌 Wiring

### I2C (ESP32 ↔ AHT10 + OLED)

- 3V3 → VCC  
- GND → GND  
- GPIO21 (SDA) → SDA  
- GPIO22 (SCL) → SCL  

### LDR

- GPIO34 → S  
- 3V3 → middle pin  
- GND → -  

---

## 🧪 Behavior

- Sensor update every **1 sec**  
- OLED displays:

  ```
  ESP32 DevOps Monitor
  --------------------
  Temp: xx.x C
  Hum : xx.x %
  Light: xx %
  ```

- Log every **5 sec** to Serial Monitor  
- No delays → fully non-blocking

---

## 💻 Software Setup

1. Install ESP32 board support  
2. Select **ESP32 Dev Module**  
3. Install libraries:
   - Adafruit AHTX0  
   - Adafruit SSD1306  
   - Adafruit GFX  

---

## 📄 Code Structure

```
loop():
    if 1s passed → read sensors → update OLED
    if 5s passed → log status
```

Uses structured tasks inside loop for clean embedded design.

---

## 🎓 Learning Notes

Practiced:  

- millis()-based scheduling  
- Shared I2C bus  
- Mapping raw ADC values  
- Simple system-style monitoring  
- Embedded-friendly clean code structure  

---

## 🚪 Scope & Closure

This project is intentionally **closed**:  
no WiFi, no cloud, no GUI, no OTA.  
It’s a focused building block inside the larger embedded lab.

---
