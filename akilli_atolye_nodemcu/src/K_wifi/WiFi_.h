#pragma once
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "Arduino.h"

class __wifi
{
private:
    int16_t ssid_eslestir();

public:
    bool yerel_izni = true;
    int8_t yerel_aktiflik_sayac = 0;
    bool arkaplan_baglan = false;
    String son_ssid = "";
    String son_sifre = "";
    bool kayit = false;
    void ssid_liste_olustur();
    bool ssid_tara = false;
    String ssid_liste = "";
    bool baglan();
    uint8_t dbm_int();
    String dbm_string();
    bool baglan(String ssid, String sifre);
    void kaydet(String ssid, String sifre);
    void hata_mesajlar();
    bool _internet;
    int16_t _dbm = 0;
    String _ip = "";
    uint8_t _bagli_kullanici = 0;
    void yerel_ag_aktifTut();
    void yerel_kur();
};
extern class __wifi wifi;