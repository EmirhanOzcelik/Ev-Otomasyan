#pragma once
#include "Arduino.h"

#define Tus_Takimi true

#define __KEYPAD_maxgirdi 10 // max depo edilecek girdi
#define __KEYPAD_sifresure 2 // şifre geçerlilik süresi yazdığınız değer 7saniye ile çarpılır.
#define __KEYPAD_sifresure2 10 // şifre geçerlilik süresi yazdığınız değer 7saniye ile çarpılır.

const uint8_t QSatir = 4;
const uint8_t QSutun = 3;
extern const char tuslar[QSatir][QSutun];

class __tustakiM
{
private:
    const char (*dizi)[QSutun];
    void kontrol();
    void kontrol2();
    void sil();
    void ekleme_kontrol();
    void ekleme_kontrol2();
    void moddegis();
    void tus_azalt(bool satir);
    void tus_arttir(bool satir);
    int8_t Usatir = 0;
    int8_t Usutun = 0;
public:
    uint16_t sifre = 0;
    String girilen = "";
    char okunan = '\0';
    char son_okunan;
    bool mod = false;
    char oku_();
    void kur();
    void oku();
    uint16_t menu_sistem_satir();
    uint16_t menu_sistem_sutun();
};
extern class __tustakiM keypad;