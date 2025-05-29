#include "main.h"
#include "depolama.h"

String __depo::oku(const char *isim)
{
    String dosyaIcerigi = "";
    File dosya = LittleFS.open(isim, "r");

    if (!dosya || dosya.isDirectory())
    {
        yaz(F("Dosya açılamadı"));
        return "";
    }

    // Dosyadaki tüm satırları oku ve birleştir
    while (dosya.available())
    {
        String satir = dosya.readStringUntil('\n');
        dosyaIcerigi += satir + "\n"; // Satırları String'e ekle
    }

    dosya.close();
    return dosyaIcerigi; // Dosya içeriğini döndür
}
String __depo::oku(const char *isim, uint16_t ilkSatir, uint16_t sonSatir)
{
    if (sonSatir == 0xFFFF)
        sonSatir = ilkSatir;
    String dosyaIcerigi = "";
    int16_t toplamSatir = satir_hesap(isim);

    if (toplamSatir < 0)
    {
        yaz(F("Dosya okunamadı, satır sayısı alınamadı"));
        return "";
    }

    if (ilkSatir >= toplamSatir)
    {
        yaz(F("İlk satır toplam satır sayısından büyük veya eşit"));
        return "";
    }

    if (sonSatir >= toplamSatir)
    {
        sonSatir = toplamSatir - 1;
    }

    File dosya = LittleFS.open(isim, "r");

    if (!dosya || dosya.isDirectory())
    {
        yaz(F("Dosya açılamadı"));
        return "";
    }

    uint16_t mevcutSatir = 0;
    while (dosya.available())
    {
        String satir = dosya.readStringUntil('\n');

        if (mevcutSatir >= ilkSatir && mevcutSatir <= sonSatir)
        {
            dosyaIcerigi += satir + "\n"; // İlgili satırları String'e ekle
        }
        mevcutSatir++;

        if (mevcutSatir > sonSatir)
        {
            break;
        }
    }

    dosya.close();
    return dosyaIcerigi; // İlgili satırlar döndürülür
}
int16_t __depo::ara(const char *isim, const String &aranan)
{
    File dosya = LittleFS.open(isim, "r");
    if (!dosya || dosya.isDirectory())
    {
        arkaplan_log += "Dosya acilamadi\n";
        return -1;
    }
    uint16_t mevcutSatir = 0;
    while (dosya.available())
    {
        String satir = dosya.readStringUntil('\n');
        if (satir == aranan)
        {
            dosya.close();
            return mevcutSatir;
        }
        mevcutSatir++;
    }
    dosya.close();
    return -1;
}
