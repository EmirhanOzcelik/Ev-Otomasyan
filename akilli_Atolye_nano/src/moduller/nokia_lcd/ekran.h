#pragma once
#include "Arduino.h"
#include "logolar.h"

#define ekran_ORTA 2525           // ortadan sıgdırır
#define ekran_SAG 2323            // en sagdan sıgdırır
#define Ekran_ortalama_tolerans 4 // ortalarken sola kaydırma içindir
#define Ekran_test_pot A7         // test modu için potansiyometre
#define Ekran_Contrast_ 60        // önerilen kontrast
#define Ekran_Xpix 84             // ekran yatay pixel
#define Ekran_Ypix 48             // ekran dikey pixel
#define font1_Xpix 6              // ekran kullanılan font x pixel
#define font1_Ypix 8              // ekran kullanılan font y pixel
#define Ekran_satir_max 16        // satirlarda max karakter

class __displaYY
{
private:
public:
    void kur();
    void yaz(uint8_t sayi, int x, uint8_t y);
    void yaz(uint16_t sayi, int x, uint8_t y);
    void yaz(int sayi, int x, uint8_t y);
    void yaz(float sayi, int x, uint8_t y, uint8_t hassasiyet);
    void yaz(const char *metin, int x = 0, uint8_t y = 0);
    void yaz(char *metin, int x = 0, uint8_t y = 0);
    void yaz(String metin, int x, uint8_t y);
    void yaz(const __FlashStringHelper *metin, uint8_t uzunluk, int x = 0, uint8_t y = 0);
    void kayan_yaz(const __FlashStringHelper *metin, uint8_t uzunluk, uint8_t y);
    void guncelle();
    uint8_t hizala(uint8_t metin_uzunlugu, int x);
    void sil();
    void kare_ciz(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool k = true);
    void cizgi_ciz(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool k = true);
    void yuvarlak_ciz(int x, int y, int R, bool k = true);
    void pixel_ciz(int x, int y, bool k = true);
    void bitmap_ciz(byte x, byte y, byte bx, byte by, const unsigned char a[], bool k = true);
    void kayan_bitmap_ciz(byte y, byte bx, byte by, const unsigned char a[], bool k = true);
};
extern class __displaYY ekran;
