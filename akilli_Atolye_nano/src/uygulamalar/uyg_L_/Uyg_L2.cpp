#include "main.h"

void __uygulamalar::internet_ayar1()
{
    uint16_t k = 0;
    while (k * g_ms > 20000)
    {
        if (millis() - gecen_zaman >= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            ekran.sil();
            ekran.yaz(F("internet :"), 11, 0, 0);
        }
    }
}