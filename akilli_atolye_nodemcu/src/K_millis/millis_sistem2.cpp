#include "main.h"

extern String mesaj_kutu1;
extern String mesaj_kutu2;
extern String mesaj_kutu3;

#define sistem_aktif true

void __calisma_zaman::calistir2()
{
    tarih.hesapla();
#if sistem_aktif == true
    sn_sayac++;
    if (sn_sayac == 6 || sn_sayac == 10 || sn_sayac == 14 || sn_sayac == 15)
        return;
    else if (sn_sayac % 2 == 0)
    {
        /// her 2sn
        if (mesaj_kutu2.length() < 250)
            mesaj_kutu2 = depo.oku("/kp_sifre.txt");
        else
        {
            if (depo.satir_hesap("kp_sifre.txt") > 5)
                mesaj_kutu2 = depo.oku("/kp_sifre.txt", depo.satir_hesap("kp_sifre.txt") - 5, depo.satir_hesap("kp_sifre.txt"));
            else
                mesaj_kutu2 = "Dosya sistemi hata verdi";
        }
        /// her 2sn
    }
    else if (sn_sayac % 3 == 0)
    {
        /// her 3sn
        if (mesaj_kutu3.length() < 250)
            mesaj_kutu3 = depo.oku("/rf_sifre.txt");
        else
        {
            if (depo.satir_hesap("rf_sifre.txt") > 5)
                mesaj_kutu3 = depo.oku("/rf_sifre.txt", depo.satir_hesap("rf_sifre.txt") - 5, depo.satir_hesap("rf_sifre.txt"));
            else
                mesaj_kutu3 = "Dosya sistemi hata verdi";
        } /// her 3sn
    }
    else if (sn_sayac % 5 == 0)
    {
        /// her 5sn
        /// her 5sn
    }
    else if (sn_sayac % 7 == 0)
    {
        /// her 7sn
        /// her 7sn
    }
    else if (sn_sayac % 11 == 0)
    {
        /// her 11sn
        /// her 11sn
    }
    else if (sn_sayac % 13 == 0)
    {
        /// her 13sn
        /// her 13sn
    }
    else if (sn_sayac % 17 == 0)
    {
        sn_sayac = 0;
        /// her 13sn
        /// her 13sn
    }
#endif
}

void __calisma_zaman::delay(const uint16_t k)
{
    uint16_t i = 0;
    while (i * g_ms < k)
    {
        if (millis() - gecen_zaman >= g_ms)
        {
            i++;
            gecen_zaman = millis();
            millis_timer.calistir();
        }
    }
}