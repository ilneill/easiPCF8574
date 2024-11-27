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
 * *  easiPCF8574 Header File  *
 * *****************************
 */

#ifndef __easiPCF8574_h
  #define __easiPCF8574_h
  
  #define INCLUDE_PCF_INT_FUNCS

  #define DEFAULT_PCF_ADDRESS 0x20  // Default base I2C address: PCF8574 = 0x20, PCF8574A = 0x38.
  #define DEFAULT_PCF_IO_MASK 0xFF  // Default pin IO direction mask. All pins are inputs.

  #define PCF_GPIO0     0
  #define PCF_GPIO1     1
  #define PCF_GPIO2     2
  #define PCF_GPIO3     3
  #define PCF_GPIO4     4
  #define PCF_GPIO5     5
  #define PCF_GPIO6     6
  #define PCF_GPIO7     7
  
  #define PCF_ALL_HIGH  0b11111111

  class PCF8574 {
    public:
      // PCF8574 Class instantiation.
      PCF8574(uint8_t i2cAd dress = DEFAULT_PCF_ADDRESS);
      // Set up the PCF register I/O directions.
      bool begin(uint8_t ioMask = DEFAULT_PCF_IO_MASK);
      #ifdef INCLUDE_PCF_INT_FUNCS
        // Set up the PCF register I/O directions and attach an interrupt handler for the PCF8574 INT pin.
        bool begin(uint8_t, void (*interruptFunction)(), uint8_t ioMask = DEFAULT_PCF_IO_MASK);
        void attachInt(uint8_t, void (*interruptFunction)()); // Manually attach an interrupt handler for the PCF8574 INT pin.
        void detachInt();                                     // Manually detach an interrupt handler for the PCF8574 INT pin.
      #endif
      uint8_t read();                                         // Read 8 bits from the PCF register.
      uint8_t write(uint8_t);                                 // Write 8 bits to the PCF register - Return: 0 = success, 1 = transmission error, 2 = address error.
      bool digitalRead(uint8_t);                              // Read the digital value of a specific pin.
      uint8_t digitalWrite(uint8_t, bool);                    // Write a digital value to a specific pin.
      uint8_t digitalToggle(uint8_t);                         // Toggle a digital value of a specific pin.
    private:
      uint8_t _pcfAddress;                                    // The PCF8574 I2C address.
      uint8_t _pcfRegister;                                   // The current value of the PCF8574 I/O register.
      #ifdef INCLUDE_PCF_INT_FUNCS
        uint8_t _intPin = 255;                                // The Arduino pin that the interrupt handler is attached to.
        bool _intEnabled = false;                             // The interrupt handler enabled flag.
      #endif
  };

#endif

// EOF
