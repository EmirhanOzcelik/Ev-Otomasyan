#include "main.h"
#include "depolama.h"
__depo depo;
const char *kp_sifreler = "/kp_sifre.txt";
const char *rf_sifreler = "/rf_sifre.txt";
const char *wf_sifreler = "/wf_sifre.txt";
const char *wf_ssidler = "/wf_ssid.txt";

bool __depo::kur()
{
    if (!LittleFS.begin())
    {
        yaz(F("LittleFS baslatilamadi!"));
        return false;
    }
    yaz(F("littleFs baslatildi"));
    return true;
}

void __depo::boyut()
{
    FSInfo fs_info;
    LittleFS.info(fs_info);
    float usedPercentage = (float(fs_info.usedBytes) / float(fs_info.totalBytes)) * 100;
    arkaplan_log += "Kullanılan depolama: %" + String(usedPercentage) + "\n";
}


void __depo::listele(const char *dizinYolu)
{
    File root = LittleFS.open(dizinYolu, "r"); // Belirtilen dizini aç
    if (!root || !root.isDirectory())          // Dizin geçerli mi kontrol et
    {
        yaz(F("Dizin acilamadi veya gecersiz: "));
        yaz(dizinYolu); // Geçersiz dizin yolunu yazdır
        return;
    }

    File dosya = root.openNextFile(); // Kök dizindeki ilk dosyayı aç
    while (dosya)                     // Dosyalar bitene kadar dön
    {
        String yol = String(dosya.name());   // Dosyanın/klasörün ismini al
        String boyut = String(dosya.size()); // Dosyanın boyutunu al

        if (dosya.isDirectory()) // Eğer dizinse, alt klasörleri listele
        {
            yaz("Klasor: " + yol);
            listele(yol.c_str()); // Alt dizin içeriğini de listele
        }
        else // Eğer dosya ise, boyutuyla birlikte yazdır
        {
            yaz(yol + " - " + boyut + " bayt");
        }

        dosya.close();               // Dosyayı kapat
        dosya = root.openNextFile(); // Bir sonraki dosyayı aç
    }

    root.close(); // Kök dizini kapat
}

int16_t __depo::satir_hesap(const char *isim)
{
    File dosya = LittleFS.open(isim, "r");
    if (!dosya || dosya.isDirectory())
    {
        yaz(F("Dosya veya klasor acilamadi"));
        return -1; // Hata durumu
    }

    int16_t satirSayisi = 0;
    while (dosya.available())
    {
        char karakter = dosya.read();
        if (karakter == '\n')
        {
            satirSayisi++;
        }
    }

    dosya.close();
    return satirSayisi;
}

void __depo::seri_kontrol()
{
    char k = Serial.read();
    switch (k)
    {
    case 'S':
        full_sil("/");
        break;
    case 'L':
        listele("/");
        break;
    case 'O':
        yaz(oku(kp_sifreler));
        break;
    default:
        break;
    }
}