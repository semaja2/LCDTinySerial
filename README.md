# LCDTinySerial
Low cost 1 wire LCD controller using an ATtiny85 and a 74HC595 for Arduino platform

# Purpose
This project is designed to be a 1 wire controller for a LCD screen, useful for small chips such as the ATtiny where pins are limited in number

The aim of the project is to produce a controller that can be low cost using components that most will already have if they are dealing with ATtiny chips etc

As this controller is using standard serial for communication, it can also reduce the overall firmware sizes for projects that connect to it (eg. Serial library may be smaller then LCD libaries)

# Usage
Simply build the circuit as per the wiring diagram, adjust the configuration details in the code then upload to an ATtiny85

Once built and the firmware is uploaded, one can simply open a serial connection to the controller and text that is typed will appear on the screen

# Modes
Currently two modes exist
## Print by character
In this mode text that is typed will appear as it is typed, if the text goes past the width of the LCD a new line will start

However new lines can still be created by simply sending the new line ASCII code

New lines will scroll text upwards, erasing the oldest line to make room
## Print by line
In this mode text will appear only after the new line ASCII code has been sent, this mode does not currently scroll text and will move the cursor to the oldest line as it needs

# Clear Screen
An ASCII code can be defined that will reset the LCD screen and clear the buffers, this is useful if you are using the LCD to display statistics

# Wiring Diagram
This git includes a fritzing diagram, but see below for a JPG export of the wiring diagram on a breadboard
![Wiring Diagram Image](https://raw.githubusercontent.com/semaja2/LCDTinySerial/master/LCDTinySerial.jpg)
