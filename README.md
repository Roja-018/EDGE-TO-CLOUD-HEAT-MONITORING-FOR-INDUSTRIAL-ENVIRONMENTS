# EDGE-TO-CLOUD-HEAT-MONITORING-FOR-INDUSTRIAL-ENVIRONMENTS

## 🎯 Abstract

In modern industrial environments, maintaining precise temperature thresholds is critical to guaranteeing machinery safety, operational reliability, and peak process efficiency. 

**Edge-to-Cloud Heat Monitoring** provides a smart, scalable IoT solution that pairs localized, real-time edge temperature sensing with cloud-based telemetry logging and predictive analytics. By processing critical thermal events at the edge while aggregating trend data in the cloud, the system minimizes response latency and reduces costly machine downtime.

---

## ✨ Key Features

- **Real-Time Edge Telemetry:** Continuous micro-second thermal sampling at the equipment layer.
- **Automated Alerting:** Immediate local boundary triggers to prevent overheating and hardware damage.
- **Scalable Cloud Analytics:** Secure transmission via MQTT/HTTP for centralized monitoring and historical data visualisations.
- **Predictive Maintenance:** Data logging structured for trend analysis, assisting in failure prediction before breakdowns occur.

## Block diagram

<img width="592" height="297" alt="block diagram" src="https://github.com/user-attachments/assets/8f6751a0-a13c-4dcc-9291-2be6c74796cd" />

## 🛠️ Hardware Requirements

| Component | Description / Function |
| :--- | :--- |
| **LPC2148** | ARM7 TDMI-S Microcontroller (Main Control Unit) |
| **LM35** | Precision Analog Temperature Sensor |
| **MQ-2** | Gas / Smoke Detection Sensor |
| **ESP8266 (ESP-01)** | Wi-Fi Transceiver Module for Cloud Telemetry |
| **16x2 LCD Display** | On-device visual output |
| **Buzzer** | Local audio alarm indicator |
| **USB-to-UART / DB9** | Serial interface for programming & debugging |

---

## 💻 Software Requirements & Tools

* **IDE / Compiler:** Keil µVision (C Compiler)
* **Programming Language:** Embedded C
* **Flashing Tool:** Flash Magic
* **Cloud Platform:** ThingSpeak IoT Platform

---

## 🔄 Project Implementation & Workflow

### Step 1: Temperature Monitoring
- LM35 continuously measures the ambient temperature.
- LPC2148 reads the analog value using its ADC.

### Step 2: Smoke Detection
- MQ-2 sensor detects smoke or combustible gases.
- LPC2148 monitors the sensor output through GPIO.

### Step 3: Data Processing
- LPC2148 processes the temperature and smoke sensor values.
- The measured values are compared with predefined threshold limits.
- If abnormal conditions are detected, the system proceeds to generate an alert.

### Step 4: Local Display
- Current temperature is displayed on the 16×2 LCD.
- Smoke detection status is also shown on the LCD.

### Step 5: Alert Generation
- If the temperature exceeds the threshold:
  - Buzzer turns ON.
  - Warning LED glows.
- If smoke is detected:
  - Buzzer turns ON.
  - Warning LED glows.

### Step 6: Cloud Communication
- LPC2148 sends sensor readings to the ESP01 Wi-Fi module through UART.
- ESP01 uploads the data to the ThingSpeak cloud platform using the HTTP protocol.

### Step 7: Remote Monitoring
Users can monitor the real-time sensor data using:
- 💻 Laptop
- 📱 Mobile Phone
- 🌐 Web Browser

---


# Project images and videos

<video src="https://private-user-images.githubusercontent.com/310009827/628961865-eea9797b-bc63-441f-8ac0-f2fbc2840ebf.mp4?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3ODUzOTY0MDgsIm5iZiI6MTc4NTM5NjEwOCwicGF0aCI6Ii8zMTAwMDk4MjcvNjI4OTYxODY1LWVlYTk3OTdiLWJjNjMtNDQxZi04YWMwLWYyZmJjMjg0MGViZi5tcDQ_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjYwNzMwJTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI2MDczMFQwNzIxNDhaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT05Y2Q1MzllOGFlZDQ0ZjVkOGUyYmRkNzMzMTIzODJjYTYxNWFhYjQ4Y2E5MGE2ZmNiBmBmNmVjM2EwNmY5NzFkJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCZyZXNwb25zZS1jb250ZW50LXR5cGU9dmlkZW8lMkZtcDQifQ.FrPJt2mbxrAvuqita2jne2_RodMOEaJcLaCA0fcrknI" width="100%" controls>
</video>
## 🔄 Operational Logic

```mermaid
flowchart TD
    A[Start / System Initialization] --> B[Read LM35 Temperature via ADC]
    B --> C{Check 3-Minute Interval via RTC?}
    C -- Yes --> D[Publish Temperature to ThingSpeak]
    C -- No --> E[Read MQ-2 Gas Sensor]
    D --> E
    
    E --> F{Gas / Smoke Detected?}
    F -- Yes --> G[Trigger Local Buzzer Alarm]
    G --> H[Publish Emergency Gas Alert to Cloud]
    
    F -- No --> I{Was Gas Previously Detected?}
    I -- Yes --> J[Deactivate Buzzer]
    J --> K[Publish 'Environment Clear' Status to Cloud]
    I -- No --> B
    H --> B
    K --> B
