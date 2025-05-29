#include "main.h"

__port port;

void __port::oku()
{
    boyut = Serial.readBytes(gelen, SP_MAX_paket * SP_MAX_veri);
    islem = false;
    if (boyut > 0)
    {
        for (uint8_t i = 0; i < boyut; i++)
        {
            if (gelen[i] == ayirac_karakter)
            {
                islem = true;
                return;
            }
        }
    }
}

void __port::ayikla()
{
    if (boyut <= 0 || gelen == nullptr || !islem)
        return;

    for (uint8_t i = 0; i < SP_MAX_paket; i++)
        paket_[i][0] = '\0';

    ayirac_konumlar[0] = 0;
    parcacik_sayisi_ = 1;

    for (int16_t i = 0; i < boyut && parcacik_sayisi_ < SP_MAX_paket + 1; i++)
    {
        if (gelen[i] == ayirac_karakter)
        {
            ayirac_konumlar[parcacik_sayisi_++] = i + 1;
        }
    }
    ayirac_konumlar[parcacik_sayisi_] = boyut;

    for (uint8_t i = 0; i < parcacik_sayisi_ - 1; i++)
    {
        uint8_t basla = ayirac_konumlar[i];
        uint8_t bitis = ayirac_konumlar[i + 1] - 1;
        uint8_t j = 0;
        for (uint8_t k = basla; k < bitis && j < SP_MAX_veri - 1; k++)
        {
            if (gelen[k] == '\0')
                break;
            paket_[i][j++] = gelen[k];
        }
        paket_[i][j] = '\0';
    }

    parcacik_sayisi_ -= 1; // Gerçek parça sayısı
    islem = false;
}

void __port::temizle()
{
    for (uint8_t i = 0; i < SP_MAX_paket; i++)
    {
        for (uint8_t j = 0; j < SP_MAX_veri; j++)
        {
            paket_[i][j] = '\0';
        }
    }
    parcacik_sayisi_ = 0;
    islem = false;
    boyut = 0;
    gelen[0] = '\0';
}

String __port::veri(uint8_t i)
{
    if (i < SP_MAX_paket)
        return String(paket_[i]);
    else
        return String("");
}

int8_t __port::paket_boyut()
{
    return parcacik_sayisi_;
}
