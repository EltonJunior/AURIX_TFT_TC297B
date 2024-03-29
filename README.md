 # AURIX_TFT_TC297B
 This repository will have examples about Infineon AURIX TFT Board 

## Development
All program here is made with HighTec and AURIX IDE and compiled at the KIT_AURIX_TC297_TFT kit where can find [Here](https://www.infineon.com/cms/en/product/evaluation-boards/kit_aurix_tc297_tft/#)

## AURIX™ Application Kit TC297 TFT
Low-cost and flexible application development platform for the 32-bit AURIX™ multi-core TriCore™ family. To simplify the development of your own application, the kit is supplied with a variety of onboard components including a highly integrated software development environment that gives you everything you need to compile, debug, and flash your AURIX™ multi-core application.

MCU Derivate: TC297TA, TC29xT, TC29xTX
- 3 x 32-bit scalar TriCore™ CPU running at up to 300 MHz in the full automotive temperature range
- Up to 8MB Flash and 728KB RAM

### Including:

- AURIX™ Development Studio

- AURIX™ Application Board 

- Link to the Free TriCore Entry Tool Chain including Getting Started, first 3 steps to
     - Install the tools
     - Set up your hardware
     - Write, compiler and debug your first program

### Summary of board features: 

- LCD XGA Display 320 x240mini SD card slot
- Mini SD card slot
- Real-Time Clock with alarm, SRAM, and unique Mac ID
- Onboard MicroUSB debug/flash connector
- Accustic beeper
- USB to UART bridge
- Ethernet PHY (if Ethernet is supported by device)
- LIN Transceiver
- High speed CAN Transceiver
- 4 Low power status LEDs
- Multi-Voltage Safety Micro Processor Supply – TLF35584

### Connectors: 

- Standard power connector
- MicroUSB connector for ASC0 interface and debug
- RJ45 Ethernet connector (if Ethernet supported by device)
- 10-pin header for DAP (Debug Access Port)
- 16-pin header for JTAG
- 10-pin 2x5 header for LIN
- 10-pin 2x5 header for CAN0
- 2 x 40-pin connectors with I/O signals RM 2.54mm

For more information access [KIT_AURIX_TC297_TFT](https://www.infineon.com/cms/en/product/evaluation-boards/kit_aurix_tc297_tft/#)

### About this repository 

It will have some code made with AURIX IDE, the main idea is to better understand the Microcontroller TC297B because it will be used in my final paper for my master's degree. 

The programs find here is:

[01_Default](#) - This repo has a default code made in the HighTech IDE.
[02_Blinky_LED](#) - This repo has a simple code made in the HighTech IDE and the onboard led.
[03_AURIX_TFT_TC297B_Blinky_LED](#) - This repo has a simple code made in the AURIX IDE and the circuit LED to test the pins of the kit.