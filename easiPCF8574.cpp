/*!
 * An Easy PCF8574/PCF8574A Arduino Library.
 *  Simple, functional, optimal, and all in a class!
 *
 * The PCF8574 is a simple I2C bus 8-bit I/O module.
 *
 * Written for the Arduino Uno/Nano/Mega.
 * (c) 2024 Ian Neill, arduino@binaria.co.uk
 * Licence: MIT
 *
 * Inspired by:
 *  https://github.com/pu2clr/PCF8574
 *  https://github.com/MSZ98/pcf8574
 *  https://github.com/linus81/PCF8574_LH
 *  https://github.com/RobTillaart/PCF8574
 *  https://github.com/xreef/PCF8574_library
 *
 * *****************************
 * * easiPCF8574 C++ Code File *
 * *****************************
 */

#include <Arduino.h>                              // Standard Arduino library (part of the Arduino IDE installation).
#include <Wire.h>                                 // Arduino I2C library (part of the Arduino IDE installation).

#include "easiPCF8574.h"

/**************************/
/* Public Class Functions */
/**************************/

// Class constructor.
PCF8574::PCF8574(uint8_t i2cAddress) {
    Wire.begin(); // Creates a Wire object.
    this->_pcfAddress = i2cAddress;               // Record the I2C address.
    this->_pcfRegister = DEFAULT_PCF_IO_MASK;     // Default is that all pins are inputs.
}

// Set up the PCF register I/O directions.
bool PCF8574::begin(uint8_t ioMask) {
    bool result;
    result = this->write(ioMask) == 0 ? true : false;
    return result;
}

#ifdef INCLUDE_PCF_INT_FUNCS
  // Set up the PCF register I/O directions and attach an interrupt handler for the PCF8574 INT pin.
  bool PCF8574::begin(uint8_t interruptPin, void (*interruptFunction)(), uint8_t ioMask) {
      bool result;
      result = this->write(ioMask) == 0 ? true : false;
      if(result) {                                // Only attach the ISR if the PCF8574 was found.
        this->attachInt(interruptPin, (*interruptFunction));
      }
      return result;
  }

  // Manually attach an interrupt handler for the PCF8574 INT pin.
  void PCF8574::attachInt(uint8_t interruptPin, void (*interruptFunction)()) {
    if(!this->_intEnabled) {
      this->_intPin = interruptPin;
      pinMode(this->_intPin, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(this->_intPin), (*interruptFunction), FALLING );
      this->_intEnabled = true;
    }    
  }

  // Manually detach an interrupt handler for the PCF8574 INT pin.
  void PCF8574::detachInt() {
    if(this->_intEnabled){
      detachInterrupt(digitalPinToInterrupt(this->_intPin));
      this->_intPin = 255;
      this->_intEnabled = false;
    }
  }
#endif

// Read 8 bits from the PCF register.
uint8_t PCF8574::read() {
  uint8_t result;
  // Request 1 byte of data from the device.
  result = Wire.requestFrom(this->_pcfAddress, (uint8_t)1);
  if(result > 0) {
    result = Wire.read();                         // Get the byte if it was returned.
  }
  else {
    result = 0xff;                                // Else assume all 1's.
  }
  return result;
}

// Write 8 bits to the PCF register - Return: 0 = success, 1 = transmission error, 2 = address error.
uint8_t PCF8574::write(uint8_t value) {
  uint8_t result;
  Wire.beginTransmission(this->_pcfAddress);      // Start communications with the device.
  Wire.write(value);                              // Send the value to the device.
  result = Wire.endTransmission();                // End communications with the device.
  if (result == 0) {
    this->_pcfRegister = value;                   // Success! Update the stored register value.
  }
  return result;
}

// Read the digital value of a specific pin.
bool PCF8574::digitalRead(uint8_t pin) {
  bool result;
  result = (this->read() & (1 << pin)) ? HIGH : LOW;
  return result;
}

// Write a digital value to a specific pin.
uint8_t PCF8574::digitalWrite(uint8_t pin, bool value) {
  uint8_t result;
  result = value ? this->_pcfRegister & ~(1 << pin) : this->_pcfRegister | (1 << pin);
  result = this->write(result);
  return result;
}

// Toggle a digital value of a specific pin.
uint8_t PCF8574::digitalToggle(uint8_t pin) {
  uint8_t result;
  result = this->_pcfRegister ^ (1 << pin);
  result = this->write(result);
  return result;
}

// EOF