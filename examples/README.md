# PCF8574 Library Example Sketches


## Example - Blink some LEDs attached to a PCF8574 module.
__Sketch: /pcfBlinkLEDs/pcfBlinkLEDs.ino__

A simple sketch that blinks LEDs attached to PCF8574 pins 0 and 1.


## Example - Read (polling) some buttons attached to a PCF8574 module.
__Sketch: /pcfReadButtons/pcfReadButtons.ino__

A small sketch that continuously polls a PCF8574 and reads the values of buttons connected to the PCF8574 pins. A message is sent to the serial console if a button is pressed (the PCF8574 pin is found to be LOW).


## Example - Read (interrupt) some buttons attached to a PCF8574 module and toggle an LED.
__Sketch: /pcfInterrupt/pcfInterrupt.ino__

A quick sketch that uses the PCF8574 INT pin and an ISR to detect when buttons connected to PCF8574 pins change status. Each time a button is pressed the LED is toggled.


// EOF