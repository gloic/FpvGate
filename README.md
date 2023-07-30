# FPVGate

![FPVGate Logo](./images/fpv_gate_logo.png)

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

## Installation

1. Clone or download the FPVGate repository from GitHub: [Link to Repository](https://github.com/gloic/FPVGate)
2. Install the required libraries and dependencies as specified in the documentation.
3. Connect the HC-SR04 sensors and RGB LED to the Arduino board according to the provided circuit diagram.
4. Upload the FPVGate sketch to the Arduino board using the Arduino IDE or your preferred method.

## Wiring

**(Hard coded)**

Common:

- Ultrasonic sensor TRIGGER : 33
- Ultrasonic sensor ECHO : 25
- State led : 2 (built-in pin)
- LED DATA : 23
- LED CLOCK : 22

Starter :

- reset button : 12

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

- NONE : default mode when starting devices (does nothing)
- TRACK MODE : all registered gates are listening. When the drone pass a gate, **Starter** is notified and gates order
  is kept in memory.
- RACE MODE : once **Starter** is passed, RACE mode is activated.

*NONE* -> Long press on reset -> *TRACK* -> define track by passing gates -> pass Starter -> *RACE*

## License

FPVGate is licensed under the MIT License.

## Acknowledgements

External resources, libraries, or individuals that contributed to the development of this library.

- EspBase : https://github.com/gloic/EspBase
- OneButton : https://github.com/mathertel/OneButton
- FastLED : https://github.com/FastLED/FastLED
- Led : https://github.com/meirarc/Led
