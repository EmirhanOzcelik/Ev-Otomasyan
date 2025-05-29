#include "main.h"

void setup()
{
    sistem.kur();
    Serial.begin(9600);
    ekran.kur();
    keypad.kur();
    depo.kur();
    random_esmaulHusna();
}

void loop()
{

    if (millis() - gecen_zaman >= g_ms)
    {
        gecen_zaman = millis();
        millis_timer.calistir();
        sistem.sensor_oku();
        ekran.sil();
        uygulama._secim();
        ekran.guncelle();
    }

    if (Serial.available() && !port.islem)
        port.oku();
    else if (port.islem)
    {
        port.ayikla();
        nodemcu.seri_istekler();
        port.temizle();
    }
    else
        keypad.oku();
}
