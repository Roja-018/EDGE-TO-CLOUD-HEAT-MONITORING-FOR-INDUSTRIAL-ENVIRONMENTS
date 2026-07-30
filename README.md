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

## ⚙️ Project Implementation & Workflow

### 1. Modular Testing Phase
Before integrating the entire system, each peripheral module is individually validated:
* **Display System (`lcd.c` / `lcd.h`):** Verified display rendering for character constants, string constants, and integer values.
* **Temperature Acquisition (`adc.c` / `adc.h`):** Tested the LM35 analog input reading via the LPC2148's inbuilt ADC pin.
* **Gas/Smoke Detection:** Verified the MQ-2 sensor functionality using LED/GPIO indication based on smoke threshold presence.
* **Serial Communications:** Verified UART interrupt execution and configured the ESP-01 module via AT commands using the Flash Magic terminal.

### 2. System Integration & Driver Development
* Connected ESP-01 hardware lines to LPC2148 UART pins.
* Developed custom ESP-01 communication drivers for ARM7.
* Tested static payload transmission to a target ThingSpeak IoT Channel.

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
