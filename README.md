# Real-Time PV Battery Monitoring System using ESP32

## Overview

This project presents a real-time photovoltaic (PV) battery monitoring system built around an ESP32 microcontroller. The system monitors battery State of Charge (SoC) and charging current while the battery is being charged by a PV panel through an MPPT charge controller. Communication between the battery system and the ESP32 is achieved via CAN bus, making the setup robust and close to what is used in real industrial energy systems.

The collected data is transmitted wirelessly to the cloud using ThingSpeak, enabling real-time visualization and performance analysis. In parallel, the system behavior is simulated and validated in MATLAB to compare theoretical expectations with real measurements.

## System Architecture

The complete system is composed of:

* PV panel connected to an MPPT charge controller
* 60V / 100Ah battery
* CAN bus interface for battery data communication
* ESP32 microcontroller
* MCP2515 CAN module
* Wi-Fi connection for cloud communication
* ThingSpeak platform for data visualization

The ESP32 receives CAN messages containing battery parameters (SoC and current), processes them, and uploads the data periodically to ThingSpeak.

## Objectives

The main goals of this project are:

* To design a real-time monitoring system for PV battery charging
* To read and decode CAN messages from the battery during charging
* To monitor State of Charge (SoC) and charging current in real time
* To evaluate battery charging performance under different environmental conditions
* To validate real measurements using MATLAB simulation

## Experimental Results

Two main experimental trials were conducted:

### First Trial (Poor PV Conditions)

* Measured charging current: approximately 0.7 A
* Effective charging current: 0 A
* Observed behavior: battery SoC remained constant

This indicates that under poor irradiation conditions, the PV system is unable to provide sufficient current to effectively charge the battery.

### Second Trial (Good PV Conditions)

* Measured charging current: greater than 1 A
* Observed behavior: battery SoC increased over time

This confirms that the battery starts charging effectively only when the current exceeds approximately 1 A, validating both the hardware setup and the monitoring logic.

## Cloud Visualization

ThingSpeak is used to visualize:

* Battery State of Charge (SoC)
* Battery charging current

The platform allows real-time monitoring, historical data analysis, and easy performance comparison between different operating conditions.

## MATLAB Simulation

MATLAB was used to simulate the PV charging behavior and battery response. Simulation results were compared with real-time data to validate system accuracy and confirm the observed charging thresholds.

## Key Takeaways

* CAN bus is reliable for real-time battery data acquisition
* ESP32 provides an efficient solution for IoT-based energy monitoring
* Battery charging effectiveness strongly depends on PV conditions
* Real-time cloud monitoring is essential for performance verification

## Future Improvements

* Add voltage and temperature monitoring
* Implement data logging on local storage (SD card)
* Introduce predictive charging analytics
* Improve SoC estimation using advanced algorithms

## Technologies Used

* ESP32
* MCP2515 CAN controller
* CAN bus protocol
* PV system with MPPT controller
* ThingSpeak IoT platform
* MATLAB for simulation and validation

## Author

Maram Ghribi

This project demonstrates a practical and scalable approach to real-time PV battery monitoring using embedded systems and IoT technologies.
