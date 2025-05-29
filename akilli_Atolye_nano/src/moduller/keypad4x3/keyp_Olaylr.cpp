#include "main.h"

void __tustakiM::moddegis()
{
    uint16_t k = 0;
    mod = !mod;
    if (mod)
    {
        Usatir = 0;
        Usutun = 0;
        uygulama.no = __ID_menuekran;
        sayac.azalan.keypad_aktiflik = __sayac_keyp_aktf2;
    }
    else
    {
        uygulama.no = __ID_anaekran;
        sayac.azalan.keypad_aktiflik = 0;
    }
    while (k * g_ms < 3000)
    {
        if (millis() - gecen_zaman >= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            k++;
            ekran.sil();
            ekran.yaz(F("mod degisti"), 11, ekran_ORTA, 0);
            ekran.yaz(F("Keypad Modu"), 11, ekran_ORTA, 10);
            if (mod)
                ekran.yaz(F("MENU"), 4, ekran_ORTA, 20);
            else
                ekran.yaz(F("TUSTAKIM"), 8, ekran_ORTA, 20);
            ekran.guncelle();
        }
    }
}