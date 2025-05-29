#include "main.h"

unsigned long gecen_zaman = 0;
extern String mesaj_kutu1;

class __calisma_zaman millis_timer;

void __calisma_zaman::calistir()
{
    ms_sayac++;
    if (ms_sayac * g_ms >= 100)
    {
        /// her 100 ms
        /// her 100 ms
        ms_sayac = 0;
        sn_ms_sayac++;
        if (sn_ms_sayac >= 10)
        {
            /// her 1 sn
            if (wifi.yerel_aktiflik_sayac < 30)
                wifi.yerel_aktiflik_sayac++;
            if (tarih.epr_kaydet_izin)
                tarih.epr_yaz_full();
            /// her 1 sn
            sn_ms_sayac = 0;
            calistir2();
        }
        else if (sn_ms_sayac % 7 == 0)
        {
            /// her 700 ms
            if (wifi.arkaplan_baglan)
                wifi.yerel_izni = wifi.baglan(wifi.son_ssid, wifi.son_sifre);
            /// her 700 ms
        }
        else if (sn_ms_sayac % 5 == 0)
        {
            /// her 500 ms
            if (wifi.kayit && WiFi.status() == WL_CONNECTED)
                wifi.kaydet(wifi.son_ssid, wifi.son_sifre);
            else if (wifi.ssid_tara)
                wifi.ssid_liste_olustur();
            /// her 500 ms
        }
        else if (sn_ms_sayac % 3 == 0)
        {
            /// her 300 ms
            if (arkaplan_log != "")
            {
                yaz(arkaplan_log);
                arkaplan_log = "";
            }
            /// her 300 ms
        }
        else if (sn_ms_sayac % 2 == 0)
        {
            /// her 200 ms
            if (depo.satir_hesap("seri_log.txt") > 8)
                mesaj_kutu1 = depo.oku("/seri_log.txt", depo.satir_hesap("seri_log.txt") - 8, depo.satir_hesap("seri_log.txt"));
            else
                mesaj_kutu1 = depo.oku("/seri_log.txt");
            /// her 200 ms
        }
    }
}
