/*!
 * Easy PCF8574/PCF8574A Arduino Library Example Sketch - Blink LEDs.
 *
 * (c) 2024 Ian Neill, arduino@binaria.co.uk
 * Licence: MIT
 *
 * Periodically blink some LEDs, connected to VCC via 1K resistors, then to PCF8574 module pins 0 and 1.
 * When the PCF8574 module pins are HIGH, the LEDs turn OFF, and when they are LOW, the LEDs turn ON.
 *
 * Arduino and PCF8574 module connections:
 *  |Device |PCF8574|Description            |
 *  |-------|-------|-----------------------|
 *  |Arduino|       |                       |
 *  |   A5  |  SCL  |I2C Clock              |
 *  |   A4  |  SDA  |I2C Data               |
 *  |-------|       |                       |
 *  |  LEDs |       |                       |
 *  |  LED1 | PIN 0 |LED-> 1K Resistor-> VCC|
 *  |  LED2 | PIN 1 |LED-> 1K Resistor-> VCC|
 *  |-------|-------|-----------------------|
*/

#include <easiPCF8574.h>

#define pcfLED1 PCF_GPIO0
#define pcfLED2 PCF_GPIO1

PCF8574 myPCFModule(0x20);                // The PCF8574 module is configured with I2C address 0x20.

void setup() {
  Serial.begin(9600);                     // The baudrate of Serial monitor is set to 9600 baud.
  while(!Serial);                         // Wait for Serial port to be ready.
  
  if(!myPCFModule.begin(PCF_ALL_HIGH)) {  // Set all the PCF8574 module pins to HIGH.
    Serial.println("Error: PCF8574 module problem!");
    while(true);                          // Stop here - no point continuing...
  }
}

void loop() {
  // Turn the LEDs ON.
  myPCFModule.digitalWrite(pcfLED1, LOW);
  delay(250);
  myPCFModule.digitalWrite(pcfLED2, LOW);
  
  delay(500);
  
  // Turn the LEDs OFF.
  myPCFModule.digitalWrite(pcfLED1, HIGH);
  delay(250);
  myPCFModule.digitalWrite(pcfLED2, HIGH);
  
  delay(1000); 
}

// EOF