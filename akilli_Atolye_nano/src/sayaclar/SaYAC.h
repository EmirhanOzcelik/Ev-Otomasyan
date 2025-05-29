#pragma once
#include "Arduino.h"

#define __sayac_keyp_aktf 10
#define __sayac_keyp_aktf2 60
#define __sayac_keyp_tus_cerc 3
#define __sayac_keypd_spam 3
#define __sayac_hatali_girs 3
#define __sayac_animasyon_Degistrci 5
#define __sayac_ms_3degisim 3
#define __sayac_ms_5degisim 5
#define __sayac_ms_10degisim 10
#define __sayac_ms_15degisim 15
#define __sayac_ms_20degisim 20
#define __sayac_ms_25degisim 25
#define __sayac_ms_85_degisim 84


struct __azalanlar
{
    uint8_t keypad_aktiflik = __sayac_keyp_aktf;                 // belirli sn keypadla işlem yapılmazsa
    uint8_t keypad_tus_cerceve = __sayac_keyp_tus_cerc;          // 300*3 900ms sürecek çerçeve animasyonu
    uint8_t keypad_spam = __sayac_keypd_spam;                    // 3 adet spamdan sonra belirli süre kitlenir
    uint8_t keypad_hatali_giris = __sayac_hatali_girs;           // 3 hatalı giriş sonrası bekletme
    uint8_t animasyon_degistirici = __sayac_animasyon_Degistrci; // her 5 snde azalır
    uint8_t ms_3degisim = __sayac_ms_3degisim;                   // her 700 ms
    uint8_t ms_5degisim = __sayac_ms_5degisim;                   // her 700 ms
    uint8_t ms_10degisim = __sayac_ms_10degisim;                 // her 700 ms
    uint8_t ms_15degisim = __sayac_ms_15degisim;                 // her 500 ms
    uint8_t ms_20degisim = __sayac_ms_20degisim;                 // her 300 ms
    uint8_t ms_25degisim = __sayac_ms_25degisim;                 // her 200 ms
    uint8_t ms_85_degisim = __sayac_ms_85_degisim;                 // her 25 ms

};
struct __degisenler
{
    bool imlec = false;  // 500ms de yanıp sönen imleç
    bool imlec2 = false; // 200 ms de yanıp sönen imleç
};

struct __sayac
{
    struct __degisenler degisen;
    struct __azalanlar azalan;
    void azalt(int16_t &syc, int16_t min = 0);
    void arttir(int16_t &syc, int16_t max);
    void azalt(uint16_t &syc, uint16_t min = 0);
    void arttir(uint16_t &syc, uint16_t max);
    void azalt(uint8_t &syc, uint8_t min = 0);
    void arttir(uint8_t &syc, uint8_t max);
};
extern struct __sayac sayac;