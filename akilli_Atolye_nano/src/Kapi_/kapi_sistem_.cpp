#include "main.h"

void __sistem::sifirla()
{
    if (tarih.sn < 58)
        tarih.sn = tarih.sn + 2;
    else
    {
        tarih.sn = 0;
        tarih.dk++;
    }
    tarih.epr_yaz_tarih();
    delay(100);
}
void __sistem::vcc_olc()
{
    int adcValue = analogRead(vcc_olcum_pin);
    float vout = (adcValue / 1023.0) * 4.60; // ADC'nin okuduğu değeri voltaja dönüştür (0-5V)
    vcc = vout * (220 + 220) / 220;          // iki adet kırmızı kırmızı kahverengi(220 ohm)
    if (vcc > 3.9)
        pil_deger = 4;
    else if (vcc > 3.6)
        pil_deger = 3;
    else if (vcc > 3.3)
        pil_deger = 2;
    else if (vcc > 3.0)
        pil_deger = 1;
    else
        pil_deger = 1;
}

int __sistem::kalibre_analogOku(int pin, float vcc)
{
    int hamDeger = analogRead(pin);
    float maxADC = (vcc / 5.0) * 1023.0;
    float oran = (float)hamDeger / maxADC;
    int normalizeDeger = oran * 1023.0;
    if (normalizeDeger > 1023)
        normalizeDeger = 1023;
    if (normalizeDeger < 0)
        normalizeDeger = 0;
    return normalizeDeger;
}
