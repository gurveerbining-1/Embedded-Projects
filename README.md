# Embedded-Projects

A collection of hands-on projects and experiments developed while learning embedded systems and low-level programming.

The repository currently focuses on bare-metal AVR C programming with the ATmega328P. As I progress, I plan to explore additional microcontrollers, hardware communication protocols, real-time operating systems, and other embedded systems concepts.

## Projects

### 1. LED Blink

Controls an LED using direct GPIO register manipulation.

**Concepts:** GPIO configuration, DDR and PORT registers, bit manipulation, and timing delays.

### 2. Seven-Segment Countdown

Implements a countdown from 9999 to 0000 on a four-digit seven-segment display.

**Concepts:** GPIO, seven-segment encoding, digit selection, and display multiplexing.

### 3. LCD Character Display

Initializes a character LCD and displays text through direct control of its interface signals.

**Concepts:** GPIO, LCD initialization, control signals, and sending commands and character data to a peripheral.

## Hardware and Tools

- **Microcontroller:** ATmega328P
- **Language:** C
- **Toolchain:** avr-gcc, avr-libc, Make
- **Programming utility:** avrdude
- **Development environment:** Visual Studio Code

## Learning Goals

Topics I plan to explore as I continue learning include:

- Register-level programming and microcontroller peripherals
- Hardware communication protocols, including I²C, SPI, and UART
- Timers, interrupts, and hardware event handling
- Working with different microcontroller architectures
- Real-time operating systems (RTOS)
- More complex embedded applications

## Approach

I aim to understand how software interacts with hardware by working close to the microcontroller, rather than relying on high-level frameworks and libraries for everything.

Each project focuses on specific concepts and serves as a practical exercise in applying what I learn. Source code includes comments documenting the implementation.

## Status

This is an ongoing learning repository. Projects, hardware platforms, and topics will evolve as I gain experience with embedded systems.
