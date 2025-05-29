#include "main.h"
#if Tus_Takimi == true

void __uygulamalar::spam(uint8_t bekleme_sn)
{
    if (bekleme_sn <= 0)
        return;
    sayac.azalan.keypad_aktiflik = 0;
    uint8_t k = 0;
    uint8_t ms_k = 0;
    while (k < bekleme_sn)
    {
        if (millis() -  gecen_zaman>= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            ms_k++;
            if (ms_k * g_ms >= 1000)
            {
                ms_k = 0;
                k++;
            }
            ekran.sil();
            ekran.yaz(bekleme_sn - k, 0, 0);
            ekran.yaz(F("sn sonra"), 8, 15, 0);
            ekran.yaz(F("tekrar deneyin"), 14, 0, 10);
            ekran.yaz(F("kalan hak:"), 11, 0, 20);
            ekran.yaz(sayac.azalan.keypad_spam, 60, 20);
            ekran.guncelle();
        }
    }
}

void __uygulamalar::hatali_giris(uint8_t bekleme_sn)
{
    if (bekleme_sn <= 0)
        return;
    sayac.azalan.keypad_aktiflik = 0;
    uint8_t k = 0;
    uint8_t ms_k = 0;
    while (k < bekleme_sn)
    {
        if (millis() -  gecen_zaman>= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            ms_k++;
            if (ms_k * g_ms >= 1000)
            {
                ms_k = 0;
                k++;
            }
            ekran.sil();
            ekran.yaz(F("sifre yanlis!"), 13, 0, 0);
            ekran.yaz(bekleme_sn - k, 0, 10);
            ekran.yaz(F("sn sonra"), 8, 15, 10);
            ekran.yaz(F("tekrar deneyin"), 14, 0, 20);
            ekran.yaz(F("kalan hak:"), 11, 0, 30);
            if (sayac.degisen.imlec)
                ekran.yaz(F(">"), 1, 0, 40);
            ekran.yaz(keypad.girilen, 5, 40);
            ekran.yaz(sayac.azalan.keypad_hatali_giris, 60, 30);
            ekran.guncelle();
        }
    }
}

void __uygulamalar::basarili_giris(uint8_t bekleme_sn, bool k)
{
    if (bekleme_sn <= 0)
        return;
    sayac.azalan.keypad_aktiflik = 0;
    uint8_t i = 0;
    uint8_t ms_k = 0;
    while (i < bekleme_sn)
    {
        if (millis() -  gecen_zaman>= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            ms_k++;
            if (ms_k * g_ms >= 1000)
            {
                ms_k = 0;
                i++;
            }
            ekran.sil();
            ekran.yaz(bekleme_sn - i, 0, 0);
            ekran.yaz(F("sn bekleyin"), 11, 15, 0);
            ekran.yaz(F("basarili"), 8, 0, 10);
            ekran.yaz(F("giris yetkisi"), 13, 0, 30);
            if (k)
                ekran.yaz(F("yonetici"), 8, 20, 40);
            else
                ekran.yaz(F("ogrenci"), 7, 24, 40);
            ekran.guncelle();
        }
    }
}

#endif