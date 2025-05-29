#pragma once
#include <Arduino.h>
#include <avr/pgmspace.h>
extern const char *const esma_listesi[];

class __tarih
{
public:
    bool epr_kaydet_izin = false;
    void hesapla();
    void hafta_hesapla(uint8_t y, uint8_t m, uint16_t d);
    void saat_(uint8_t saat_ = 12, uint8_t dk_ = 30, uint8_t sn_ = 20);
    void tarih_(uint16_t yil_ = 2025, uint8_t ay_ = 4, uint8_t gun_ = 20, uint8_t hafta_ = 1);
    void epr_oku();
    void epr_yaz_saat();
    void epr_yaz_tarih();
    void epr_yaz_full();
    void epr_sifirla();
    String ayyil_cikti();
    String saatdk_cikti();
    String full_cikti();
    char *ay_adi_(uint8_t ay_index);
    char *gun_adi_(uint8_t gun_index);
    uint16_t yil = 2025;
    uint8_t ay = 5;
    uint8_t gun = 17;
    uint8_t saat = 0;
    uint8_t dk = 0;
    uint8_t sn = 0;
    uint8_t hafta_gunu = 4; // 0: Pazar, 1: Pazartesi, ..., 6: Cumartesi

private:
    bool artik_yil(uint16_t y);
    uint8_t ay_gun_sayisi(uint8_t ay, uint16_t yil);
};
extern class __tarih tarih;
