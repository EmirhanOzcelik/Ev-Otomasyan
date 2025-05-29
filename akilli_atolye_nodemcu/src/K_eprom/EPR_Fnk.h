#pragma once
#include "EPR_ADR.h"
#include "EEPROM.h"
#include <Arduino.h>
#define nodemcu_epr_boyut 64

class __depo_epr
{
public:
    void yaz(uint16_t adres, uint8_t veri); ///< 1 byte veri kaydeder
    void yaz16(uint16_t adres, uint16_t veri);
    uint8_t oku8(const uint16_t adres);   ///< 1 byte veri okur
    uint16_t oku16(const uint16_t adres); ///< 2 byte veri okur
    void reset(uint16_t k1 = 0, uint16_t k2 = 1023, uint8_t veri = 0);
    bool ekle8(const uint16_t adres, const int8_t artis);
    bool ekle16(const uint16_t adres, const int16_t artis);
    bool varsayilana_sifirla();
};

extern __depo_epr epr;