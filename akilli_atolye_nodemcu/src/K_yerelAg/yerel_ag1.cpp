#include "main.h"

#define MAX_KAYIT 10

String mesaj_kutu2 = "";
String mesaj_kutu3 = "";
String mesaj_kutu1 = "";

int k = 0;

struct Zaman
{
    int sn, dk, saat, haftagun, ay, gun, yil;
};

const char *ssid = "ESP-CaptivePortal";
const char *password = "sifre123";

AsyncWebServer server(80);
DNSServer dnsServer;
IPAddress apIP(192, 168, 4, 1);

void __wifi::yerel_kur()
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

    WiFi.softAP(ssid, password);
    dnsServer.start(53, "*", apIP);

    Serial.print("AP IP: ");
    arkaplan_log += WiFi.softAPIP().toString() + "\n";

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->redirect("/site_genel.html"); });

    server.serveStatic("/site_genel.html", LittleFS, "/site_genel.html");
    server.serveStatic("/server_kullanim1.txt", LittleFS, "/server_kullanim1.txt");
    server.serveStatic("/server_kullanim2.txt", LittleFS, "/server_kullanim2.txt");
    server.serveStatic("/server_kullanim3.txt", LittleFS, "/server_kullanim3.txt");
    server.serveStatic("/server_kullanim4.txt", LittleFS, "/server_kullanim4.txt");
    server.serveStatic("/server_kullanim5.txt", LittleFS, "/server_kullanim5.txt");
    /////////////////////////////////////////////////////////////////////////////////////////////////////// tarih bölümü tamamlandı

    server.on("/zaman", HTTP_POST, [](AsyncWebServerRequest *request)
              {
                wifi.yerel_aktiflik_sayac = 0;
        tarih.sn = request->getParam("sn", true)->value().toInt();
        tarih.dk = request->getParam("dk", true)->value().toInt();
        tarih.saat = request->getParam("saat", true)->value().toInt();
        tarih.hafta_gunu = request->getParam("haftagun", true)->value().toInt();
        tarih.ay = request->getParam("ay", true)->value().toInt();
        tarih.gun = request->getParam("gun", true)->value().toInt();
        tarih.yil = request->getParam("yil", true)->value().toInt();
        tarih.epr_kaydet_izin = true;
        arkaplan_log += "Guncel tarih: "+String(tarih.yil)+"/"+String(tarih.ay)+"/"+String(tarih.gun)+
            " "+String(tarih.saat)+":"+String(tarih.dk)+":"+String(tarih.sn)+"\n";
        request->send(200, "text/plain", "Zaman bilgisi alindi."); });
    /////////////////////////////////////////////////////////////////////////////////////////////////////// kapı bölümü tamamlandi

    server.on("/kapi-secim", HTTP_POST, [](AsyncWebServerRequest *request)
              {
            if (!request->hasParam("saat", true) || !request->hasParam("dk", true)) {
                request->send(400, "text/plain", "Eksik parametre!");
                return;
            }
            wifi.yerel_aktiflik_sayac=0;
            
            String saat = request->getParam("saat", true)->value();
            String dk = request->getParam("dk", true)->value();
            arkaplan_log += "#kapi#sure#"+String(60 * saat.toInt() + dk.toInt()) +"#\n";
            
            arkaplan_log += "Secilen kapak acik kalma suresi: " + saat + " saat " + dk + " dk\n";
            request->send(200, "text/plain", "Sure alindi: " + saat + " saat " + dk + " dk"); });
    /////////////////////////////////////////////////////////////////////////////////////////////////////// //kapı bölümü tamamlandi

    server.on("/kapi", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        String islem = request->getParam("islem", true)->value();
                wifi.yerel_aktiflik_sayac=0;
        if (islem == "aktif") {
            arkaplan_log += "Kapi aktif edildi.\n";
            arkaplan_log += "#kapi#durum#aktif#\n";
            request->send(200, "text/plain", "Kapi aktif edildi.");
        } else if (islem == "pasif") {
            arkaplan_log += "Kapi pasif edildi.\n";
            arkaplan_log += "#kapi#durum#pasif#\n";
            request->send(200, "text/plain", "Kapi pasif edildi.");
        } else {
            request->send(400, "text/plain", "Gecersiz islem.");
        } });
    /////////////////////////////////////////////////////////////////////////////////////////////////////// uygulamalar yarım
    // rifid kayit ekranı tamamlandı
    server.on("/rfid_kart_kaydet", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                wifi.yerel_aktiflik_sayac=0; 
                nfc.kayit_izin = !nfc.kayit_izin;
                arkaplan_log+="\n";
        request->send(200, "text/plain", "rfid kaydedici"); });

    server.on("/keypad_sifre_olustur", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                wifi.yerel_aktiflik_sayac=0;
                arkaplan_log += "Keypad sifre olusturucu ";
        request->send(200, "text/plain", "Keypad sifre olusturucu acildi."); });

    server.on("/sensor_kalibrasyon", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                wifi.yerel_aktiflik_sayac=0;
                arkaplan_log += "Sensor kalibrasyon özelligi henuz eklenmedi\n";
        request->send(200, "text/plain", "Sensor kalibrasyon ekranina girildi."); });

    server.on("/motor_kalibrasyon", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                wifi.yerel_aktiflik_sayac=0;
                arkaplan_log += "Motor kalibrasyon özelligi henuz eklenmedi\n";
        request->send(200, "text/plain", "Motor kalibrasyon ekranina girildi."); });

    server.on("/ana_menu", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Ana menuye donuldu."); 
                wifi.yerel_aktiflik_sayac=0; });
    /////////////////////////////////////////////////////////////////////////////////////////////////////// bilgi kutuları tamamlandı

    server.on("/mesaj1", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", mesaj_kutu1); });
    server.on("/mesaj2", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", mesaj_kutu2); });
    server.on("/mesaj3", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", mesaj_kutu3); });
    /////////////////////////////////////////////////////////////////////////////////////////////////////// wifi kısmı tamamlandı
    server.on("/tara-ssid", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                wifi.yerel_aktiflik_sayac=0;
                String k = "";
                if(wifi.ssid_liste == "" && !wifi.ssid_tara){
                    wifi.ssid_tara = true;}
                else if(wifi.ssid_liste != "" && !wifi.ssid_tara){
                    k = wifi.ssid_liste;
                }
                else if(wifi.ssid_liste != "" && wifi.ssid_tara)
                {
                    wifi.ssid_liste = "";
                    wifi.ssid_tara = false;
                }
        request->send(200, "application/json", k); });

    server.on("/baglan", HTTP_POST, [](AsyncWebServerRequest *request)
              {
                wifi.yerel_aktiflik_sayac=0;
        if (!request->hasParam("ssid", true) || !request->hasParam("password", true)) {
            request->send(400, "text/plain", "Eksik bilgi!");
            return;
        }
        String ssid = request->getParam("ssid", true)->value();
        String password = request->getParam("password", true)->value();
    
        arkaplan_log += "baglanmak istenen SSID: " + ssid+"\n";
        wifi.son_ssid = ssid;
        wifi.son_sifre = password;
        wifi.arkaplan_baglan = true;
        request->send(200, "text/plain", "Baglaniliyor: " + ssid); });

    /////////////////////////////////////////////////////////////////////////////////////////////////////// server kontrolü tamamlandı

    server.onNotFound([](AsyncWebServerRequest *request)
                      {
        String path = request->url();
        if (path != "/" && path != "/site_genel.html" && path != "/zaman" &&
            path != "/rfid_kart_kaydet" && path != "/keypad_sifre_olustur" &&
            path != "/sensor_kalibrasyon" && path != "/motor_kalibrasyon") 
        {
            request->redirect("/");
        } else {
            request->send(404, "text/plain", "Sayfa bulunamadi.");
        } });

    server.begin();
}

void __wifi::yerel_ag_aktifTut()
{
    if (yerel_izni)
        dnsServer.processNextRequest();
    else
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            k++;
            if (k * g_ms >= 10000)
            {
                yerel_izni = true;
                k = 0;
            }
        }
        else
            k = 0;
    }
}