#ifndef _MCP23S17_H
#define _MCP23S17_H

#if (ARDUINO >= 100) 
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

#include <SPI.h>

class MCP23S17 {
    private:
        SPIClass *_spi; 
        uint8_t _cs;    /*! Chip select pin */
        uint8_t _addr;  /*! 3-bit chip address */
		uint8_t _rst;
    
        uint8_t _reg[22];   /*! Local mirrors of the 22 internal registers of the MCP23S17 chip */

        enum {
            MCP_IODIRA,     MCP_IODIRB,
            MCP_IPOLA,      MCP_IPOLB,
            MCP_GPINTENA,   MCP_GPINTENB,
            MCP_DEFVALA,    MCP_DEFVALB,
            MCP_INTCONA,    MCP_INTCONB,
            MCP_IOCONA,     MCP_IOCONB,
            MCP_GPPUA,      MCP_GPPUB,
            MCP_INTFA,      MCP_INTFB,
            MCP_INTCAPA,    MCP_INTCAPB,
            MCP_GPIOA,      MCP_GPIOB,
            MCP_OLATA,      MCP_OLATB
        };

        void readRegister(uint8_t addr); 
        void writeRegister(uint8_t addr);
        void readAll();
        void writeAll();
    
    public:
		MCP23S17(uint8_t addr);
		
        void begin();
        bool enableHardwareAddress();
        void pinMode(uint8_t pin, uint8_t mode);
        void digitalWrite(uint8_t pin, uint8_t value);
        uint8_t digitalRead(uint8_t pin);

        uint8_t readPort(uint8_t port);
        uint16_t readPort();
        void writePort(uint8_t port, uint8_t val);
        void writePort(uint16_t val);
        void enableInterrupt(uint8_t pin, uint8_t type);
        void disableInterrupt(uint8_t pin);
        void setMirror(boolean m);
        uint16_t getInterruptPins();
        uint16_t getInterruptValue();
        void setInterruptLevel(uint8_t level);
        void setInterruptOD(boolean openDrain);
        uint8_t getInterruptAPins();
        uint8_t getInterruptAValue();
        uint8_t getInterruptBPins();
        uint8_t getInterruptBValue();
};
#endif
