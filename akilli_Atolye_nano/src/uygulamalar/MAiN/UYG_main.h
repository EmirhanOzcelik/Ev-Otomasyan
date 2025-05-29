#pragma once
#include "Arduino.h"

#define __ID_anaekran 0    // ana ekran kodu
#define __ID_tuslarekran 1 // keypad tuş ekranı kodu
#define __ID_menuekran 2   // keypad menu ekranı kodu
void random_esmaulHusna();

class __uygulamalar
{
private:
    void animasyon_sistem();

public:
    char esmaulHusnA[15];
    uint8_t no = 0;
    void _secim();
    void bilgi_ekran();
    void sensor_test(bool k);
    void ustpanel();
    void anaekran();
    void tustakim();
    void spam(uint8_t bekleme_sn);
    void hatali_giris(uint8_t bekleme_sn);
    void basarili_giris(uint8_t bekleme_sn, bool k = false);
    void menu();
    void seri_veri_bekle(uint16_t sayac, uint16_t max, bool durum, uint8_t hata_kod);
    void sistem_reset();
    void epr_reset();
    void saat_ayar();
    void tarih_ayar();
    void internet_ayar1();
};
extern class __uygulamalar uygulama;