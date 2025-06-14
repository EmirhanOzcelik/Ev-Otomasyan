#include "main.h"

void __uygulamalar::seri_veri_bekle(uint16_t sayac, uint16_t max, bool durum, uint8_t hata_kod)
{
    ekran.yaz(F("Nodemcuya"), 9, 15, 0);
    ekran.yaz(F("baglaniyor..."), 13, 2, 10);
    if (!durum)
    {
        ekran.yaz(F("veri bekliyor"), 13, 3, 20);
        ekran.yaz(F("baglanti:null"), 13, 0, 40);
    }
    else
        ekran.yaz(F("veri okunuyor"), 13, 0, 20);
    ekran.yaz(F("kalan sn:"), 9, 14, 30);
    uint16_t u = (max - sayac) / 1000;
    ekran.yaz(u, 68, 30);
    switch (hata_kod)
    {
    case 1:
        ekran.yaz(F("basarili !"), 10, 0, 40);
        break;
    case 2:
        ekran.yaz(F("hata:kod"), 8, 0, 40);
        break;
    case 3:
        ekran.yaz(F("hata:baslik"), 11, 0, 40);
        break;
    default:
        break;
    }
}
