/*!
 * Easy PCF8574/PCF8574A Arduino Library Example Sketch - Read buttons (interrupt) and toggle an LED.
 *
 * (c) 2024 Ian Neill, arduino@binaria.co.uk
 * Licence: MIT

 * Toggles an LED, connected to VCC via 1K resistor, then to PCF8574 module pin 0, 
 *  when buttons, connected to any of the PCF8574 module pins 1, 2, 3, 4, 5, 6 and 7 are pressed.
 *
 * The PCF8574 module INT pin is connected to interrupt supporting pin D2 of the Arduino (a Nano, Uno or Pro Mini). 
 * When any PCF8574 module pin changes status, the INT changing from HIGH -> LOW (falling edge) fires an interrupt. 
 * 
 * A notification of the interrupt and each button press will sent to the serial monitor and the LED will be toggled OFF->ON or ON->OFF.
 *
 * Arduino and PCF8574 module connections:
 *  |Device |PCF8574|Description            |
 *  |-------|-------|-----------------------|
 *  |Arduino|       |                       |
 *  |   A5  |  SCL  |I2C Clock              |
 *  |   A4  |  SDA  |I2C Data               |
 *  |   D2  |  INT  |Arduino Interrupt pin  |
 *  |-------|       |                       |
 *  |Buttons|       |                       |
 *  |   B1  | PIN 1 |} Buttons connected to |
 *  |   B2  | PIN 2 |}                      |
 *  |   B3  | PIN 3 |}   any PCF8574 pin    |
 *  |   B4  | PIN 4 |}                      |
 *  |   B5  | PIN 5 |}  and then connected  |
 *  |   B6  | PIN 6 |}                      |
 *  |   B7  | PIN 7 |}        to GND        |
 *  |-------|       |                       |
 *  |  LEDs |       |                       |
 *  |  LED1 | PIN 0 |LED-> 1K Resistor-> VCC|
 *  |-------|-------|-----------------------|
*/

#include <easiPCF8574.h>

#define pcfLED1 PCF_GPIO0
#define ARDUINO_INT_PIN 2

volatile bool pcfEvent = false;
volatile unsigned int intCount = 0;

PCF8574 myPCFModule(0x20);                // The PCF8574 module is configured with I2C address 0x20.

void setup() {
  Serial.begin(9600);                     // The baudrate of Serial monitor is set to 9600 baud.
  while(!Serial);                         // Wait for Serial port to be ready.

  // Set all the PCF8574 module pins to HIGH, and setup an interrupt service routine for the PCF8574 INT pin.
  if(!myPCFModule.begin(ARDUINO_INT_PIN, checkInt, PCF_ALL_HIGH)) {
    Serial.print("Error: PCF8574 module problem!");
    while(true);                          // Stop here - no point continuing...
  }

  Serial.println("\nPress buttons 1 - 7 to toggle the LED..."); 
}

void loop() {
  byte binCounter, pcfPinStatus;
  
  // Expect a pcfEvent when a button is pressed and released.
  if(pcfEvent) {
    Serial.print("Interrupt: ");
    Serial.println(intCount);
    // Check all button pins to find which one(s) is/are LOW (pressed) and triggered the interrupt.
    for(binCounter = 1; binCounter < 8; binCounter++) {
      // Reading from the PCF8574 will clear the PCF8574 interrupt and reset the INT pin from LOW -> HIGH.
      if(myPCFModule.digitalRead(binCounter) == LOW) {
        Serial.print("Pin #");
        Serial.print(binCounter);
        Serial.println(" is LOW!");
        myPCFModule.digitalToggle(pcfLED1);
      }
    }
    // Show the status of all the PCF8574 pins.
    pcfPinStatus = myPCFModule.read();
    Serial.print("PCF8574: ");
    for(binCounter = 7; binCounter > 0; binCounter--) {
      Serial.print((pcfPinStatus >> binCounter) & 0x01 ? "1" : "0");
    }
    Serial.println((pcfPinStatus) & 0x01 ? "1" : "0
    
    // Clear our interrupt status flag.
    pcfEvent = false;
  }
}

// Process a PCF8574 module interrupt event.
// This function is called when the PCF8574 module INT pin transitions from HIGH -> LOW for any I/O pin changes status.
void checkInt() {
  pcfEvent = true;  // Set our interrupt status flag.
  intCount++;
}

// EOF