# FPVGate

![FPVGate Logo](./logo.png)

FPVGate is a project that aims to create a gate system for detecting the passage of objects, such as drones or RC
helicopters, using ultrasonic sensors. The gate system is designed for FPV (First Person View) racing and can be used as
a starting and finishing line for races.

## Features

- Gate detection: Ultrasonic sensors are used to detect the passage of objects through the gates.
- Configurable threshold distance: The threshold distance can be adjusted to fine-tune the detection sensitivity.
- Starter functionality: One gate is designated as the starter gate, which initiates the race and records the lap times.
- Web-based user interface: Provides a user-friendly interface for configuring and monitoring the gate system (not
  implemented yet).
- Supporting OTA

# TODO 
 - 

## Requirements

To use FPVGate, the following components are required:

- Arduino-compatible board (ESP32 or ESP8266)
- HC-SR04 ultrasonic sensors
- RGB LED (optional)
- Buttons
- Batteries (18650)
- Buzzer
- Lcd Display (SSD1306)

## Installation

1. Clone FPVGate repository
2. Install the required libraries and dependencies as specified in the documentation.
3. ???
4. Profit !

## Wiring

Common:

- Ultrasonic sensor: 33 (Trigger), 25 (Echo)
- Potentiometer (for ultrasonic range calibration): 36
- State led: 2
- Buzzer : 27
- Led Strip : 23 (Data), 22 (Clock)

Starter :

- reset button : 12
- Lcd display : 21 (SDA), 22 (SCL)

## Project

One gate must be the **Starter** gate, it will :

- create a wifi access point
- receive information when a gate detects a passage
- orchestrate others gates

Others **Gates** can :

- access to the Starter's wifi access point
- register when joining network
- notify **Starter** when detecting object's passage

## Configuration

**Starter Gate** has 3 modes : NONE, TRACK and RACE.

- IDLE : default mode when starting devices (does nothing)
- CALIBRATION : all registered gates are listening and continue to listen when passage is detected. Allow user to calibrate ultrasonic sensor's range using potentiometer 
- TRACK MODE : all registered gates are listening. When the drone pass a gate, **Starter** is notified and gates order is kept in memory.
- RACE MODE : once **Starter** is passed, RACE mode is activated.

*NONE* -> Long press on reset -> *TRACK* -> define track by passing gates -> pass Starter -> *RACE*

## License

FPVGate is licensed under the MIT License.

## Acknowledgements
