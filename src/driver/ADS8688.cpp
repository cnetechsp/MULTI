#include "ADS8688.h"
#include "../config_pin.h"

static constexpr uint16_t AUTO_RST = 0xA000;

ADS8688::ADS8688(float vref)
: _mosi(ads8688_mosi), _miso(ads8688_miso), _sck(ads8688_sck), _cs(ads8688_cs), _rst(ads8688_rst), _vref(vref) {}

void ADS8688::begin(uint8_t* type) {
    pinMode(_mosi, OUTPUT);
    pinMode(_miso, INPUT);
    pinMode(_sck, OUTPUT);
    pinMode(_cs, OUTPUT);
    pinMode(_rst, OUTPUT);

    digitalWrite(_cs, HIGH);
    digitalWrite(_sck, LOW);
    digitalWrite(_rst, HIGH);

    writeRegister(0x02, 0x00); // Tất cả các kênh đều thoát khỏi trạng thái tiết kiệm năng lượng.
    writeRegister(0x01, 0xFF); // Bật tất cả các kênh

    for (uint8_t ch = 0x05; ch <= 0x0C; ch++) {
        writeRegister(ch, type[ch-0x05]);
    }

    autoResetMode();
}

void ADS8688::autoResetMode() {
    writeCommand(AUTO_RST);
}

void ADS8688::readAll(uint16_t* buffer, uint8_t ch) {
    for (uint8_t i = 0; i < ch; i++) {
        csLow();
        writeByte(0x00);
        writeByte(0x00);
        uint8_t h = readByte();
        uint8_t l = readByte();
        csHigh();
        buffer[i] = (h << 8) | l;
    }
}

float ADS8688::toVoltage(uint16_t raw) {
    return (raw * _vref) / 65535.0f;
}


void ADS8688::writeRegister(uint8_t addr, uint8_t data) {
    csLow();
    writeByte((addr << 1) | 0x01);
    writeByte(data);
    csHigh();
}

void ADS8688::writeCommand(uint16_t cmd) {
    csLow();
    writeByte(cmd >> 8);
    writeByte(cmd & 0xFF);
    csHigh();
}

void ADS8688::writeByte(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        (data & 0x80) ? mosiHigh() : mosiLow();
        clkHigh();
        data <<= 1;
        clkLow();
    }
}

uint8_t ADS8688::readByte() {
    uint8_t r = 0;
    for (uint8_t i = 0; i < 8; i++) {
        r <<= 1;
        clkHigh();
        if (digitalRead(_miso)) r |= 1;
        clkLow();
    }
    return r;
}


void ADS8688::csLow()  { digitalWrite(_cs, LOW); }
void ADS8688::csHigh() { digitalWrite(_cs, HIGH); }
void ADS8688::clkHigh(){ digitalWrite(_sck, HIGH); }
void ADS8688::clkLow() { digitalWrite(_sck, LOW); }
void ADS8688::mosiHigh(){ digitalWrite(_mosi, HIGH); }
void ADS8688::mosiLow(){ digitalWrite(_mosi, LOW); }