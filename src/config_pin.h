#ifndef _CONFIG_PIN_H
#define _CONFIG_PIN_H

/********************ads8688********************/
#if defined(ARDUINO_TEENSY40)
  #define ads8688_mosi  3
  #define ads8688_miso  4
  #define ads8688_sck   2
  #define ads8688_cs    9
  #define ads8688_rst   16

  #define mcp23s17_spi  SPI
  #define mcp23s17_cs   10
  #define mcp23s17_rst  25

  #define serial485Port1    Serial2
  #define usrPort           Serial3

#else
  #error "Unsupported chip!"
#endif



#endif