#include "main.h"

String arkaplan_log = "";
bool zaman_damga = true;

void yaz(String k)
{
    if (depo.satir_hesap("/seri_log.txt") > 200)
        depo.sil("/seri_log.txt");
    else
    {
        if (zaman_damga)
        {
            String c = tarih.full_cikti() + " --> " + k;
            Serial.println(c);
            depo.ekle("/seri_log.txt", c);
        }
        else
        {
            Serial.println(k);
            depo.ekle("/seri_log.txt", k);
        }
    }
}

void yaz(const __FlashStringHelper *k)
{
    yaz(String(k));
}

void yaz(const char *k)
{
    yaz(String(k));
}

void yaz(char k)
{
    yaz(String(k));
}

void yaz(int k)
{
    yaz(String(k));
}

void yaz(unsigned int k)
{
    yaz(String(k));
}

void yaz(long k)
{
    yaz(String(k));
}

void yaz(unsigned long k)
{
    yaz(String(k));
}

void yaz(float k, int precision)
{
    yaz(String(k, precision));
}

void yaz(double k, int precision)
{
    yaz(String(k, precision));
}
