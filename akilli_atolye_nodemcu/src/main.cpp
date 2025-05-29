#include "main.h"

void setup()
{
    Serial.begin(9600);
    depo.kur();
    EEPROM.begin(nodemcu_epr_boyut);
    nfc.kur();

    tarih.epr_oku();
    depo.sil("/seri_log.txt");
    depo.boyut();
    
    if (wifi.yerel_izni)
        wifi.yerel_kur();
    else
        wifi.yerel_izni = !wifi.baglan();
}

void loop()
{
    if (millis() - gecen_zaman >= g_ms)
    {
        gecen_zaman = millis();
        millis_timer.calistir();    
        wifi.yerel_ag_aktifTut();
    }

    if (Serial.available())
    {
        port.oku();
    }
    else if (port.islem)
    {
        port.ayikla();
        nano.seri_istekler();
        port.temizle();
    }
    else if (nfc.kayit_izin)
        nfc.kart_kaydet();
    else
        nfc.oku();
}
