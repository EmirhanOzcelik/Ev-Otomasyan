#include "main.h"
#include "EPR_Fnk.h"

class __depo_epr epr;

void __depo_epr::yaz(uint16_t adres, uint8_t veri)
{
    EEPROM.write(adres, veri);
    EEPROM.commit();
}

void __depo_epr::yaz16(uint16_t adres, uint16_t veri)
{
    EEPROM.write(adres, veri & 0xFF);
    EEPROM.write(adres + 1, veri >> 8);
    EEPROM.commit();
}

uint8_t __depo_epr::oku8(uint16_t adres)
{
    return EEPROM.read(adres);
}

uint16_t __depo_epr::oku16(uint16_t adres)
{
    uint16_t alt = EEPROM.read(adres);
    uint16_t ust = EEPROM.read(adres + 1);
    return (ust << 8) | alt;
}

void __depo_epr::reset(uint16_t k1, uint16_t k2, uint8_t veri)
{
    if (k2 > nodemcu_epr_boyut - 1)
        k2 = nodemcu_epr_boyut - 1;
    if (k1 >= k2)
        return;
    for (uint16_t i = k1; i < k2; i++)
    {
        EEPROM.write(i, veri);
    }
    EEPROM.commit();
}

bool __depo_epr::ekle8(const uint16_t adres, const int8_t artis)
{
    int16_t yeni = (int16_t)oku8(adres) + artis;
    if (yeni > 255 || yeni < 0)
        return false;
    yaz(adres, (uint8_t)yeni);
    return true;
}

bool __depo_epr::ekle16(const uint16_t adres, const int16_t artis)
{
    int32_t mevcut = oku16(adres);
    int32_t yeni = mevcut + artis;
    if (yeni < 0 || yeni > 65535)
        return false;
    yaz16(adres, (uint16_t)yeni);
    return true;
}

bool __depo_epr::varsayilana_sifirla()
{
    yaz(_EprAdr_sn, 1);
    yaz(_EprAdr_dk, 0);
    yaz(_EprAdr_saat, 0);
    yaz(_EprAdr_gun, 1);
    yaz(_EprAdr_ay, 1);
    yaz16(_EprAdr_yil, 2025);
    yaz(_EprAdr_hafta, 0);
    yaz(_EprAdr_wifiMod, 0);
    if (EEPROM.commit())
        return true;
    else
        return false;
}