# PCF8574 Library Example Sketches

All examples were tested using an Arduino Mini Pro (ATmega168P) development board with an FT232 USB Serial adapter, and compiled using Arduino IDE v2.3.3.

## Example - Blink some LEDs attached to a PCF8574 module.
__Sketch: /pcfBlinkLEDs/pcfBlinkLEDs.ino__

A simple sketch that blinks LEDs attached to PCF8574 pins 0 and 1.


## Example - Read (polling) some buttons attached to a PCF8574 module.
__Sketch: /pcfReadButtons/pcfReadButtons.ino__

A small sketch that continuously polls a PCF8574 and reads the values of buttons connected to the PCF8574 pins. A message is sent to the serial console if a button is pressed (a PCF8574 pin is found to be LOW).


## Example - Read (polling) some buttons attached to a PCF8574 module with button debouncing.
__Sketch: /pcfReadButtonsDebounced/pcfReadButtonsDebounced.ino__

A sketch that continuously polls a PCF8574 and reads and debounces the values of buttons connected to the PCF8574 pins. A message is sent to the serial console if a button is pressed (a PCF8574 pin is found to be LOW). Debouncing is via multiple reads over a short time, until the buttons input stabilises.


## Example - Read (interrupt) some buttons attached to a PCF8574 module and toggle an LED.
__Sketch: /pcfInterrupt/pcfInterrupt.ino__

A quick sketch that uses the PCF8574 INT pin and an ISR to detect when buttons connected to PCF8574 pins change status. Each time a button is pressed the LED is toggled.


## Example - Read (interrupt) some buttons attached to a PCF8574 module and toggle an LED with button debouncing.
__Sketch: /pcfInterruptDebounced/pcfInterruptDebounced.ino__

A sketch that uses the PCF8574 INT pin and an ISR to detect when buttons connected to PCF8574 pins change status. Each time a button is pressed, and has been debounced, the LED is toggled. Debouncing is achieved by ignoring interrupts for a short time after a button change is detected.


// EOF