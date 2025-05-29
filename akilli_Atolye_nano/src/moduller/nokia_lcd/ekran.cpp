#include "main.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "ekran.h"

#define Ekran true           // ekran kompenenti kullanılacaksa true
#define Ekran_test_mod false // ekran için test modu

#if Ekran == true
Adafruit_PCD8544 ekran_(2, 4, 5);

class __displaYY ekran;

void __displaYY::kur()
{
    ekran_.begin();
    ekran_.setContrast(Ekran_Contrast_);
    ekran_.clearDisplay();
    Serial.println(F("Ekran kuruldu"));
    yaz(F("kuruldu"), 7);
    ekran_.display();
    ekran_.setTextWrap(false);
    sil();
#if Ekran_test_mod == true
    while (Ekran_test_mod)
    {
        uint16_t k = analogRead(Ekran_test_pot);
        uint16_t c = map(k, 0, 1023, 0, 255);
        ekran_.setContrast(c);
        ekran_.clearDisplay();
        yaz(F("pot: "), 5, 0, 0);
        yaz(F("kontrast: "), 10, 0, 10);
        yaz(k, 30, 0);
        yaz(c, 55, 10);
        ekran_.display();
        delay(50);
        sil();
    }
#endif
}

void __displaYY::yaz(uint8_t sayi, int x, uint8_t y)
{
    ekran_.setCursor(x, y);
    ekran_.print(sayi);
}

void __displaYY::yaz(uint16_t sayi, int x, uint8_t y)
{
    ekran_.setCursor(x, y);
    ekran_.print(sayi);
}

void __displaYY::yaz(int sayi, int x, uint8_t y)
{
    ekran_.setCursor(x, y);
    ekran_.print(sayi);
}
void __displaYY::yaz(float sayi, int x, uint8_t y, uint8_t hassasiyet)
{
    ekran_.setCursor(x, y);
    ekran_.print(sayi, hassasiyet); // hassasiyet: ondalık basamak sayısı
}

void __displaYY::yaz(const char *metin, int x, uint8_t y)
{
    uint8_t uzunluk = strlen(metin);
    uint8_t xpos = hizala(uzunluk, x);
    ekran_.setCursor(xpos, y);
    ekran_.print(metin);
}
void __displaYY::yaz(char *metin, int x, uint8_t y)
{
    uint8_t uzunluk = strlen(metin);
    uint8_t xpos = hizala(uzunluk, x);
    ekran_.setCursor(xpos, y);
    ekran_.print(metin);
}
void __displaYY::yaz(String metin, int x, uint8_t y)
{
    uint8_t uzunluk = metin.length();
    uint8_t xpos = hizala(uzunluk, x);
    ekran_.setCursor(xpos, y);
    ekran_.print(metin);
}
void __displaYY::yaz(const __FlashStringHelper *metin, uint8_t uzunluk, int x, uint8_t y)
{
    uint8_t xpos = hizala(uzunluk, x);
    ekran_.setCursor(xpos, y);
    ekran_.print(metin);
}
void __displaYY::kayan_yaz(const __FlashStringHelper *metin, uint8_t uzunluk, uint8_t y)
{
    ekran_.setCursor(sayac.azalan.ms_85_degisim - (uzunluk + 1) * font1_Xpix, y);
    ekran_.print(metin);
}

uint8_t __displaYY::hizala(uint8_t metin_uzunlugu, int x)
{
    uint8_t genislik = metin_uzunlugu * font1_Xpix;

    if (x == 2525) // ORTALA
    {
        if (genislik >= Ekran_Xpix)
            return 0;
        return (Ekran_Xpix - genislik) / 2 - Ekran_ortalama_tolerans;
    }
    else if (x == 2323) // SAĞA YASLA
    {
        if (genislik >= Ekran_Xpix)
            return 0;
        return Ekran_Xpix - genislik;
    }
    else // DÜZ X VERİLDİ
    {
        if (x + genislik > Ekran_Xpix)
            return 0; // Taşmayı engelle
        return x;
    }
}

void __displaYY::sil()
{
    ekran_.clearDisplay();
}
void __displaYY::guncelle()
{
    ekran_.display();
}

void __displaYY::kare_ciz(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool k)
{
    if (k)
        ekran_.drawRect(x, y, w, h, BLACK);
    else
        ekran_.drawRect(x, y, w, h, BLACK);
}

void __displaYY::cizgi_ciz(uint8_t x, uint8_t y, uint8_t x2, uint8_t y2, bool k)
{
    if (k)
        ekran_.drawLine(x, y, x2, y2, BLACK);
    else
        ekran_.drawLine(x, y, x2, y2, WHITE);
}

void __displaYY::yuvarlak_ciz(int x, int y, int R, bool k)
{
    if (k)
        ekran_.drawCircle(x, y, R, BLACK);
    else
        ekran_.drawCircle(x, y, R, WHITE);
}

void __displaYY::pixel_ciz(int x, int y, bool k)
{
    if (k)
        ekran_.drawPixel(x, y, BLACK);
    else
        ekran_.drawPixel(x, y, WHITE);
}

void __displaYY::bitmap_ciz(byte x, byte y, byte bx, byte by, const unsigned char a[], bool k)
{
    if (k)
        ekran_.drawBitmap(x, y, a, bx, by, BLACK);
    else
        ekran_.drawBitmap(x, y, a, bx, by, WHITE);
}
void __displaYY::kayan_bitmap_ciz(byte y, byte bx, byte by, const unsigned char a[], bool k)
{
    if (k)
        ekran_.drawBitmap(sayac.azalan.ms_85_degisim - bx, y, a, bx, by, BLACK);
    else
        ekran_.drawBitmap(sayac.azalan.ms_85_degisim - bx * 3 / 2, y, a, bx, by, WHITE);
}

#endif