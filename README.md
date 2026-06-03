# inactivity-monitor
## About  This is a self-initiated Arduino project developed to monitor activity and generate alerts based on user-defined conditions.
# 🚨 Inactivity Monitor

## Overview

Inactivity Monitor is a personal Arduino-based project developed to detect prolonged inactivity and generate alerts in real time.

The system continuously monitors movement/activity status. If no activity is detected for a predefined duration, the system triggers visual and audio alerts and displays warning messages through the serial terminal.

This project was created to explore embedded systems, monitoring systems, event detection, and alert generation using Arduino.

---

## Features

* Real-time activity monitoring
* Inactivity detection
* Configurable inactivity threshold
* Audio alerts using buzzer/speaker
* Visual alerts using LEDs
* Serial terminal notifications
* Low-cost implementation

---

## Hardware Components

* Arduino Uno
* Buzzer / Speaker
* Red LED
* Green LED
* Logic State Input
* Virtual Terminal (Proteus)

---

## Software Tools

* Arduino IDE
* Embedded C
* Proteus Professional

---

## Working Principle

1. The system continuously monitors activity input.
2. Normal activity keeps the system in monitoring mode.
3. If no activity is detected for a specified duration, an alert condition is triggered.
4. Red LED and buzzer indicate the alert state.
5. Warning messages are displayed through the serial terminal.
6. When activity resumes, the alert condition is cleared automatically.

---

## Applications

* Pet activity monitoring
* Home monitoring systems
* Elderly care monitoring
* Security systems
* Industrial monitoring
* IoT alert systems

---

## Advantages

* Simple design
* Real-time response
* Easy implementation
* Low hardware cost
* Expandable for IoT integration

---

## Future Improvements

* GSM/SMS alerts
* Mobile application integration
* Wi-Fi based monitoring
* Cloud dashboard
* GPS tracking support
* Sensor-based activity detection

---

## Project Screenshot

Add your Proteus simulation screenshot here.

---

## Repository Structure

```text
inactivity-monitor/
│
├── README.md
├── inactivity_monitor.ino
├── Proteus_Design.pdsprj
├── Screenshot.png
└── Documentation/
```

---

## About

This is a self-initiated personal project developed to strengthen practical knowledge in Arduino programming, embedded systems, monitoring logic, and alert generation mechanisms.

## License

MIT License
