#include "main.h"
#include "millis_sistem.h"

unsigned long gecen_zaman = 0;

class __calisma_zaman millis_timer;

void __calisma_zaman::calistir()
{
    ms_sayac++;
    if (ms_sayac * g_ms >= 100)
    {
        /// her 100 ms
        sayac.azalt(sayac.azalan.ms_85_degisim);
        if (sayac.azalan.ms_85_degisim <= 0)
            sayac.azalan.ms_85_degisim = __sayac_ms_85_degisim;
        /// her 100 ms
        ms_sayac = 0;
        sn_ms_sayac++;
        if (sn_ms_sayac >= 10)
        {
            /// her 1 sn
            sayac.azalt(sayac.azalan.keypad_aktiflik);
            /// her 1 sn
            sn_ms_sayac = 0;
            calistir2();
        }
        else if (sn_ms_sayac % 7 == 0)
        {
            /// her 700 ms
            /// her 700 ms
        }
        else if (sn_ms_sayac % 5 == 0)
        {
            /// her 500 ms
            sayac.degisen.imlec = !sayac.degisen.imlec;
            /// her 500 ms
        }
        else if (sn_ms_sayac % 3 == 0)
        {
            /// her 300 ms
            sayac.azalt(sayac.azalan.keypad_tus_cerceve);
            sayac.azalt(sayac.azalan.ms_20degisim);
            /// her 300 ms
        }
        else if (sn_ms_sayac % 2 == 0)
        {
            /// her 200 ms
            sayac.degisen.imlec2 = !sayac.degisen.imlec2;
            /// her 200 ms
        }
    }
}

void __calisma_zaman::delay(const uint16_t k)
{
    uint16_t i = 0;
    while (i * g_ms < k)
    {
        if (millis() - gecen_zaman >= g_ms)
        {
            i++;
            gecen_zaman = millis();
            millis_timer.calistir();
        }
    }
}