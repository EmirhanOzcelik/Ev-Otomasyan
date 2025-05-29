#pragma once
#include "Arduino.h"
#include "LittleFS.h"

extern const char* kp_sifreler;
extern const char* rf_sifreler;
extern const char* wf_sifreler;
extern const char* wf_ssidler;

struct __depo
{
    bool kur();

    void boyut();

    void listele(const char *dizinYolu);
    int16_t satir_hesap(const char *isim);
    void seri_kontrol();

    String oku(const char *isim);
    String oku(const char *isim, uint16_t ilkSatir, uint16_t sonSatir = 0xFFFF);

    int16_t ara(const char *isim, const String &aranan);

    void degistir(const char *isim, const String &yeniIcerik);
    void degistir(const char *isim, const char *yeniIcerik);
    void degistir(const char *isim, int yeniIcerik);
    void degistir(const char *isim, float yeniIcerik);
    void ekle(const char *isim, const String &yeniIcerik);
    void ekle(const char *isim, const char *yeniIcerik);
    void ekle(const char *isim, int yeniIcerik);
    void ekle(const char *isim, float yeniIcerik);

    void full_sil(const char *dizinYolu);
    void sil(const char *dosyaAdi);
    void sil(const char *dosyaAdi, uint16_t ilkSatir, uint16_t sonSatir = 0xFFFF);
};
extern struct __depo depo;