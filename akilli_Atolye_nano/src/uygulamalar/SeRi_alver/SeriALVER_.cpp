#include "main.h"

/**
 * @brief Seri bağlantı üzerinden veri bekleyen veya okuyan yardımcı fonksiyondur.
 *
 * Bu fonksiyon, bağlantı durumu ve bekleme süresine göre ekrana uygun bilgileri yazar.
 * Hata koduna göre kullanıcıya sonuçla ilgili mesaj gösterir.
 *
 * @param sayac     Gecen süreyi milisaniye cinsinden belirtir. Kalan süre hesaplanır.
 * @param max       Beklenecek maksimum süre (ms) olarak verilir.
 * @param durum     Eğer true ise veri okunuyor, false ise veri bekleniyor olarak kabul edilir.
 * @param hata_kod  Hata durumu:
 *                  - 1: başarılı
 *                  - 2: genel hata
 *                  - 3: başlık hatası
 *                  - diğer: bağlantı yok
 *
 * @note Bu fonksiyon `ekran` nesnesi aracılığıyla görsel çıktı verir.
 */
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