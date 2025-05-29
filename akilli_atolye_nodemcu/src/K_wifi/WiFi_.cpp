#include "main.h"
#include "WiFi_.h"

class __wifi wifi;

void __wifi::ssid_liste_olustur()
{
    int n = WiFi.scanNetworks();
    if (n > 0)
    {
        ssid_liste = "[";
        for (int i = 0; i < n; i++)
        {
            ssid_liste += "\"" + WiFi.SSID(i) + "\"";
            if (i != n - 1)
                ssid_liste += ",";
        }
        ssid_liste += "]";
    }
    else
        ssid_liste = "";
}

int16_t __wifi::ssid_eslestir()
{
    int numNetworks = WiFi.scanNetworks();
    if (numNetworks == 0)
    {
        yaz(F("Ag bulunamadi"));
        return -1;
    }

    int16_t satirSayisi = depo.satir_hesap(wf_ssidler);
    if (satirSayisi <= 0)
    {
        yaz(F("Dosya bos veya okunamadi"));
        return -1;
    }

    for (int i = 0; i < numNetworks; i++)
    {
        String foundSSID = WiFi.SSID(i);

        for (int j = 0; j < satirSayisi; j++)
        {
            String ssidInFile = depo.oku(wf_ssidler, j);
            if (foundSSID == ssidInFile)
            {
                yaz(F("Eslesen SSID bulundu: "));
                yaz(foundSSID);
                return j;
            }
        }
    }

    yaz(F("Eslesen SSID bulunamadi"));
    return -1;
}

bool __wifi::baglan()
{
    kayit = false;
    arkaplan_baglan = false;
    WiFi.mode(WIFI_STA);
    int16_t baglanilacak_wifi = ssid_eslestir();
    if (baglanilacak_wifi >= 0)
    {
        String _ssid = depo.oku(wf_ssidler, baglanilacak_wifi);
        String _sifre = depo.oku(wf_sifreler, baglanilacak_wifi);

        if (_ssid.length() <= 0 || _sifre.length() < 3)
            return false;

        WiFi.begin(_ssid.c_str(), _sifre.c_str());
        uint16 k = 0;

        while (WiFi.status() != WL_CONNECTED && k * g_ms < 5000)
        {
            yerel_ag_aktifTut();
            if (millis() - gecen_zaman >= g_ms)
            {
                gecen_zaman = millis();
                millis_timer.calistir();
                k++;
            }
        }
        if (WiFi.status() != WL_CONNECTED)
        {
            yaz(F("Baglanti zaman asimi"));
            hata_mesajlar();
            kayit = false;
            _internet = false;
            return false;
        }
        else
        {
            yaz("Baglanti basariyla yapildi. IP Adresi : " + WiFi.localIP().toString());
            yaz("SSID : " + _ssid);
            yaz("sinyal gücü : " + dbm_string() + " dBm");
            kayit = true;
            _internet = true;
            return true;
        }
    }
    arkaplan_log += "oto baglanti icin kayitli ag bulunamadi\n";
    return false;
}

uint8_t __wifi::dbm_int()
{
    if (WiFi.status() != WL_CONNECTED)
        return 0;

    int rssi = WiFi.RSSI();
    if (rssi >= -50)
        return 3;
    else if (rssi >= -65)
        return 2;
    else if (rssi >= -75)
        return 1;
    else
        return 0;
}

String __wifi::dbm_string()
{
    if (WiFi.status() != WL_CONNECTED)
        return "-1";

    int rssi = WiFi.RSSI();
    if (rssi >= -50)
        return "3";
    else if (rssi >= -65)
        return "2";
    else if (rssi >= -75)
        return "1";
    else
        return "0";
}

bool __wifi::baglan(String ssid, String sifre)
{
    arkaplan_baglan = false;
    kayit = false;
    if (sifre.length() < 4)
        return false;
    WiFi.begin(ssid.c_str(), sifre.c_str());
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts * g_ms < 5000)
    {
        yerel_ag_aktifTut();
        if (millis() - gecen_zaman >= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            attempts++;
        }
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        yaz("\ninternete baglandi");
        yaz("IP Adresi: " + WiFi.localIP().toString());
        yaz("SSID : " + ssid);
        yaz("sinyal gücü : " + dbm_string() + " dBm");
        kayit = true;
        return true;
    }
    else
    {
        yaz("\ninternete baglanamadi");
        hata_mesajlar();
        kayit = false;
        return false;
    }
}

void __wifi::kaydet(String ssid, String sifre)
{
    if (!kayit)
        return;
    else if (WiFi.status() != WL_CONNECTED)
        return;
    int a = depo.ara(wf_ssidler, ssid);
    int b = depo.ara(wf_sifreler, sifre);
    if (a >= 0)
    {
        if (b >= 0)
        {
            if (b == a)
            {
                kayit = false;
                return;
            }
            else
            {
                depo.sil(wf_sifreler, b);
                depo.sil(wf_ssidler, a);
            }
        }
    }
    else
    {
        depo.ekle(wf_sifreler, sifre);
        depo.ekle(wf_ssidler, ssid);
        arkaplan_log += "ag kayit edildi\n";
    }
    kayit = false;
}
void __wifi::hata_mesajlar()
{
    if (WiFi.status() == WL_CONNECT_FAILED)
        yaz("SSID veya sifre hatali");
    else if (WiFi.status() == WL_NO_SSID_AVAIL)
        yaz("SSID bulunamadi");
    else if (WiFi.status() == WL_CONNECT_FAILED)
        yaz("Baglanti zaman asimi");
    else if (WiFi.status() == WL_IDLE_STATUS)
        yaz("Baglanti beklemede");
    else if (WiFi.status() == WL_DISCONNECTED)
        yaz("Baglanti kesildi");
}