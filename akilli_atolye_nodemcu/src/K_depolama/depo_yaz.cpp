#include "main.h"

void __depo::degistir(const char *isim, const String &yeniIcerik)
{
    File dosya = LittleFS.open(isim, "w"); // Dosyayı yazma modunda aç, içerik sıfırlanır
    if (!dosya)
    {
        Serial.println(F("Dosya acilamadi"));
        return;
    }

    dosya.print(yeniIcerik); // Yeni içerik dosyaya Serial.printlnılır
    dosya.close();
    Serial.println(F("icerik basariyla değistirildi"));
}

void __depo::degistir(const char *isim, const char *yeniIcerik)
{
    degistir(isim, String(yeniIcerik));
}
void __depo::degistir(const char *isim, int yeniIcerik)
{
    degistir(isim, String(yeniIcerik));
}
void __depo::degistir(const char *isim, float yeniIcerik)
{
    degistir(isim, String(yeniIcerik));
}

void __depo::ekle(const char *isim, const String &yeniIcerik)
{
    File dosya = LittleFS.open(isim, "a");
    if (!dosya)
    {
        Serial.println(F("Dosya acilamadi"));
        return;
    }
    dosya.print("\n" + yeniIcerik);
    dosya.close();
    Serial.println(F("icerik basariyla eklendi"));
}

void __depo::ekle(const char *isim, const char *yeniIcerik)
{
    ekle(isim,String(yeniIcerik));
}
void __depo::ekle(const char *isim, int yeniIcerik)
{
    ekle(isim,String(yeniIcerik));
}
void __depo::ekle(const char *isim, float yeniIcerik)
{
    ekle(isim,String(yeniIcerik));
}
