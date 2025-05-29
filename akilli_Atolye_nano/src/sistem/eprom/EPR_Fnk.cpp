#include <EEPROM.h>
#include "main.h"
#include "EPR_Fnk.h"

class __depo depo;

void __depo::yaz(uint16_t adres, uint8_t veri)
{
    EEPROM.update(adres, veri);
}

void __depo::yaz16(uint16_t adres, uint16_t veri)
{
    EEPROM.update(adres, veri & 0xFF);
    EEPROM.update(adres + 1, veri >> 8);
}

uint8_t __depo::oku8(const uint16_t adres)
{
    return EEPROM.read(adres);
}

uint16_t __depo::oku16(const uint16_t adres)
{
    uint16_t alt = EEPROM.read(adres);
    uint16_t ust = EEPROM.read(adres + 1);
    return (ust << 8) | alt;
}

void __depo::reset(uint16_t k1, uint16_t k2, uint8_t veri)
{
    if (k2 > 1023)
        k2 = 1023;
    if (k1 >= k2)
        return;
    while (k1 < k2)
    {
        yaz(k1, veri);
        k1++;
    }
}

bool __depo::ekle8(const uint16_t adres, const int8_t artis)
{
    int16_t yeni = (int16_t)oku8(adres) + artis;
    if (yeni > 255 || yeni < 0)
        return false;
    yaz(adres, (uint8_t)yeni);
    return true;
}

bool __depo::ekle16(const uint16_t adres, const int16_t artis)
{
    int32_t mevcut = oku16(adres);
    int32_t yeni = mevcut + artis;
    if (yeni < 0 || yeni > 65535)
        return false;
    yaz(adres, (uint16_t)yeni);
    return true;
}
