# PCF8574 Library Example Sketches


## Example - Blink some LEDs attached to a PCF8574 module.
File: /pcfBlinkLEDs/pcfBlinkLEDs.ino

A simple sketch that blinks LEDs attached to PCF8574 pins 0 and 1.


## Example - Read (polling) some buttons attached to a PCF8574 module.
File: /pcfReadButtons/pcfReadButtons.ino

A small sketch that continuously polls a PCF8574 and reads the values of buttons connected to the PCF8574 pins. A message is sent to the serial console if a button is pressed (the PCF8574 pin is found to be LOW).


## Example - Read (interrupt) some buttons attached to a PCF8574 module and toggle an LED.
File: /pcfInterrupt/pcfInterrupt.ino

A quick sketch that uses the PCF8574 INT pin and an ISR to detect when buttons connected to PCF8574 pins change status. When a button is pressed and LED is toggled.


// EOF