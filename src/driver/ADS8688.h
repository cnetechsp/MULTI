#ifndef _ADS8688_H
#define _ADS8688_H
#include <Arduino.h>


#define R0 0x00  // Input range to -2.5/+2.5         Vref   +/- 10.24V
#define R1 0x01  // Input range to -1.25/+1.25       Vref   +/-  5.12V
#define R2 0x02  // Input range to -0.625/+0.625     Vref   +/-  2.56V
#define R3 0x03  // Input range to -0.3125/+0.3125   Vref   +/-  1.28V
#define R4 0x0B  // Input range to -0.15625/+0.15625 Vref   +/-  0.64V
#define R5 0x05  // Input range to +2.5    Vref   10.24V
#define R6 0x06  // Input range to +1.25   Vref    5.12V
#define R7 0x07  // Input range to +0.625  Vref    2.56V
#define R8 0x0F  // Input range to +0.3125 Vref    1.28V


class ADS8688 {
public:
    ADS8688(float vref = 5.12f);

    void begin(uint8_t* type);
    void autoResetMode();
    void readAll(uint16_t* buffer, uint8_t ch = 8);
    float toVoltage(uint16_t raw);

private:
    uint8_t _mosi, _miso, _sck, _cs, _rst;
    float _vref;

    void csLow();
    void csHigh();
    void clkHigh();
    void clkLow();
    void mosiHigh();
    void mosiLow();

    void writeByte(uint8_t data);
    uint8_t readByte();
    void writeCommand(uint16_t cmd);
    void writeRegister(uint8_t addr, uint8_t data);
};

#endif