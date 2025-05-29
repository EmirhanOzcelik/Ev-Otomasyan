#pragma once

#define g_ms 50 // makine güncelleme ms (100 e tamkat)

extern unsigned long gecen_zaman;

class __calisma_zaman
{
private:
    void calistir2();
    uint16_t ms_sayac = 0;   // 100ms sayacı
    uint8_t sn_ms_sayac = 0; // sn-ms sayacı
    uint8_t sn_sayac = 0;    // sn sayacı
public:
    void calistir();
    void delay(const uint16_t k);
};

extern class __calisma_zaman millis_timer;