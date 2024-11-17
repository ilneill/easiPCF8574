/*!
 * Easy PCF8574/PCF8574A Arduino Library Example Sketch - Read Buttons (polling).
 *
 * (c) 2024 Ian Neill, arduino@binaria.co.uk
 * Licence: MIT
 *
 * Send the status of buttons 1 - 8, connected to PCF8574 module pins 0 - 7, to the serial monitor.
 *
 * Debouncing is essentially repeatedly reading the buttons over a short period of time, until they have settled. 
 *   
 * Arduino and PCF8574 module connections:
 *  |Device |PCF8574|Description            |
 *  |-------|-------|-----------------------|
 *  |Arduino|       |                       |
 *  |   A5  |  SCL  |I2C Clock              |
 *  |   A4  |  SDA  |I2C Data               |
 *  |-------|       |                       |
 *  |Buttons|       |                       |
 *  |   B1  | PIN 0 |Button connected to GND|
 *  |   B2  | PIN 1 |Button connected to GND|
 *  |   B3  | PIN 2 |Button connected to GND|
 *  |   B4  | PIN 3 |Button connected to GND|
 *  |   B5  | PIN 4 |Button connected to GND|
 *  |   B6  | PIN 5 |Button connected to GND|
 *  |   B7  | PIN 6 |Button connected to GND|
 *  |   B8  | PIN 7 |Button connected to GND|
 *  |-------|-------|-----------------------|
*/

#include <easiPCF8574.h>

#define BUTTONDBT       10                // Button debounce time (ms).

PCF8574 myPCFModule(0x20);                // The PCF8574 module is configured with I2C address 0x20.

void setup() {
  Serial.begin(9600);                     // The baudrate of Serial monitor is set to 9600 baud.
  while(!Serial);                         // Wait for Serial port to be ready.
  
  if(!myPCFModule.begin(PCF_ALL_HIGH)) {  // Set all the PCF8574 module pins to HIGH.
    Serial.println("Error: PCF8574 module problem!");
    while(true);                          // Stop here - no point continuing...
  }
  
  Serial.println("Press buttons 1 - 8 to make the PCF8574 pins go LOW..."); 
}

void loop() {
  byte pinCounter;
  static bool buttonState[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
  static bool buttonRead[8];
  static bool buttonReadPrevious[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
  static unsigned long lastDebounceTime [8] = {0, 0, 0, 0, 0, 0, 0, 0};
  unsigned long timenow = millis();
  
  // Read the PCF8574 module pins, one at a time, and check to see if it has changed since the last reading.
  for(pinCounter = 0; pinCounter < 8; pinCounter++) {
    buttonRead[pinCounter] = myPCFModule.digitalRead(pinCounter);
    if(buttonRead[pinCounter] != buttonReadPrevious[pinCounter]) {
      lastDebounceTime [pinCounter] = timenow;
      // Save the button readings for use when we go through the loop again:
      buttonReadPrevious[pinCounter] = buttonRead[pinCounter];
    }
  }
  // Check each button to see if it has been stable for longer than the debounce delay.
  for(pinCounter = 0; pinCounter < 8; pinCounter++) {
    if((timenow - lastDebounceTime[pinCounter]) > BUTTONDBT) {
      // The reading is stable, so if it is different, it can be recorded and used.
      if(buttonRead[pinCounter] != buttonState[pinCounter]) {
        buttonState[pinCounter] = buttonRead[pinCounter];
        if(buttonState[pinCounter] == LOW) {
          Serial.print("Button #");
          Serial.print(pinCounter + 1);
          Serial.print(" pressed => Pin #");
          Serial.print(pinCounter);
          Serial.println(" is LOW!");
        }
      }
    }
  }
}

// EOF