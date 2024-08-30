FPVGate Documentation
Table of Contents

    Introduction
    Project Objective
    Main Features
    Hardware Components
    Operating Modes
    Communication between Gates
    User Interface
    Programming Language and Development Environment
    Libraries and Dependencies
    Code Structure
    Event Management
    Data Management
    Testing and Validation
    Deployment
    Error Handling
    Performance and Optimization
    Documentation and Support
    Conclusion

Introduction

FPVGate is a project for a gate system designed to detect the passage of drones (mainly tinywhoops) using ultrasonic sensors. This system is intended for FPV (First Person View) racing and can be used as a starting and finishing line for races. The project is aimed at personal and recreational use, allowing users to create race tracks in their homes or apartments.
Project Objective

The primary objective of FPVGate is to provide a solution for creating FPV drone race tracks at home. By placing gates at various locations, users can define a race track layout and time their laps, adding a goal and challenge to their flying sessions.
Main Features

    Passage Detection: Each gate is equipped with an upward-facing ultrasonic sensor to detect the passage of a drone.
    Race Time Management: The system records passage times and lap times for each lap.
    Flexible Configuration: Gates can be placed anywhere and configured to define a race track layout.
    Operating Modes: The system has multiple operating modes for calibration, track creation, and racing.
    WiFi Communication: Gates communicate with each other via WiFi, using a REST web service to manage instructions and notifications.

Hardware Components

    Ultrasonic Sensor: HC-SR04
    Microcontroller: ESP32
    LED Strip: To indicate the status and the next gate to pass through
    Buttons: For configuration and control
    Batteries: 18650 with charging and regulation circuit, or 5V power supply via micro USB
    Buzzer: For sound notifications
    OLED Display: For the user interface on the Starter gate

Operating Modes
IDLE

Default mode where the gate waits for instructions.
CALIBRATION

Mode for adjusting the detection distance of the ultrasonic sensors using a potentiometer. All connected gates enter calibration mode.
TRACK

Mode for creating the race track layout. Gates record the order of passage of the drone.
RACE

Race mode where gates indicate the next gate to pass through in sequence and record lap times.
Communication between Gates

Gates communicate via WiFi. The Starter gate creates a WiFi access point with a predefined SSID and password. Other gates automatically connect to this network and notify the Starter of their presence. The Starter stores the IP addresses of the gates to send instructions. The gates know the IP address of the Starter via the network gateway.
User Interface

The user interface is planned on an OLED display on the Starter gate. This display will allow for configuration and parameterization of the track. No web interface or mobile application is planned for now.
Programming Language and Development Environment

The project is developed in C++ for the ESP32 using PlatformIO.
Libraries and Dependencies

    Web Server: AsyncTCP and ESPAsyncWebServer
    Ultrasonic Sensor: NewPin
    Indication LED: meirarc/Led or manually managed
    LED Strip: NeoPixel (not yet implemented)

Code Structure

The code is structured in modules with a dedicated class for each component (ultrasonic sensor, LED, buzzer, etc.). A server part manages the Starter gate to send instructions to other gates.
Event Management

Events for detecting the passage of drones are managed via HTTP (POST) requests. When a gate is in "listening" mode, it sends pulses until it detects a passage and lights up the LED strip in a predefined pattern or color. Once a passage is detected, the gate notifies the Starter via a web service call. The Starter then instructs the next gate to listen.
Data Management

Currently, no data is stored persistently. Race times are lost when the Starter is turned off. Given the recreational nature of the project and the flexibility of gate placement, storing times is not a priority.
Testing and Validation

Unit tests and integration tests are not yet implemented. The testing method with PlatformIO is still to be defined.
Deployment

Deployment is currently done by connecting the ESP32 via serial and flashing the firmware. OTA (Over-The-Air) updates are considered to simplify updates but are not a priority yet.
Error Handling

No error handling or logging mechanisms are planned for now.
Performance and Optimization

The latency of communication via WiFi and REST web services must be relatively low to allow for quick detection and efficient notification between gates. The frequency of ultrasonic sensor pulses must be high enough to detect small, fast-moving drones.
Documentation and Support

The project will be documented on GitHub. The documentation will be updated as the project progresses. The current analysis and these questions/answers will serve as the basis for the documentation.
Conclusion

FPVGate is an innovative project that allows users to create FPV drone race tracks at home. Using ultrasonic sensors and WiFi communication, the system offers a flexible and recreational solution for drone enthusiasts. This documentation provides a comprehensive and detailed overview of the project, covering all technical and functional aspects.