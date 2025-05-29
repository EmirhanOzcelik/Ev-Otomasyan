#include "main.h"

void __depo::full_sil(const char *dizinYolu)
{
    // Dizin açılabiliyor mu kontrol et
    File root = LittleFS.open(dizinYolu, "r");
    if (!root || !root.isDirectory())
    {
        yaz(String(F("Gecersiz dizin: ")) + dizinYolu);
        return;
    }

    // Dosya ve klasorleri tek tek isleme
    File dosya = root.openNextFile();
    while (dosya)
    {
        String yol = String(dosya.name());
        if (dosya.isDirectory()) // Alt klasorse, onu da temizle
        {
            yaz(String(F("Alt klasor bulundu: ")) + yol);
            full_sil(yol.c_str()); // Rekursif olarak alt klasorleri temizle
            if (LittleFS.rmdir(yol))
            {
                yaz(String(F("Klasor silindi: ")) + yol); // Klasor silme basariliysa
            }
            else
            {
                yaz(String(F("Klasor silinemedi: ")) + yol); // Klasor silinemezse hata
            }
        }
        else // Dosya ise, direkt sil
        {
            yaz(String(F("Siliniyor: ")) + yol);
            if (LittleFS.remove(yol))
            {
                yaz(String(F("Dosya silindi: ")) + yol); // Dosya silme basariliysa
            }
            else
            {
                yaz(String(F("Dosya silinemedi: ")) + yol); // Dosya silinemezse hata
            }
        }
        dosya.close();               // Dosya kapatilmali
        dosya = root.openNextFile(); // Bir sonraki dosyayi ac
    }

    root.close(); // Kok dizini kapat
    if (String(dizinYolu) != "/")
    { // Eğer kök dizin değilse, dizini sil
        if (LittleFS.rmdir(dizinYolu))
        {
            yaz(String(F("Dizin silindi: ")) + dizinYolu); // Dizin silme basariliysa
        }
        else
        {
            yaz(String(F("Dizin silinemedi: ")) + dizinYolu); // Dizin silinemezse hata
        }
    }
    else
    {
        yaz(String(F("Kok dizin silinemedi: ")) + dizinYolu); // Kok dizin silinemez
    }
}

void __depo::sil(const char *dosyaAdi)
{
    if (LittleFS.exists(dosyaAdi))
    {
        if (LittleFS.remove(dosyaAdi))
        {
            yaz(String(F("Silindi: ")) + dosyaAdi); // Dosya silme basariliysa
        }
        else
        {
            yaz(String(F("Dosya silinemedi: ")) + dosyaAdi); // Dosya silinemezse hata
        }
    }
    else
    {
        yaz(String(F("Dosya yok: ")) + dosyaAdi);
    }
}

void __depo::sil(const char *dosyaAdi, uint16_t ilkSatir, uint16_t sonSatir)
{
    int16_t toplamSatir = satir_hesap(dosyaAdi);
    if (toplamSatir <= 0 || ilkSatir >= toplamSatir)
    {
        yaz(F("Silme islemi gecersiz."));
        return;
    }

    // Eger sonSatir varsayilan degerdeyse, sadece ilkSatir silinsin
    if (sonSatir == 0xFFFF)
        sonSatir = ilkSatir;

    if (sonSatir >= toplamSatir)
        sonSatir = toplamSatir - 1;

    File orijinal = LittleFS.open(dosyaAdi, "r");
    if (!orijinal)
    {
        yaz(F("Dosya acilamadi"));
        return;
    }

    String yeniIcerik = "";
    uint16_t mevcutSatir = 0;

    while (orijinal.available())
    {
        String satir = orijinal.readStringUntil('\n');
        if (mevcutSatir < ilkSatir || mevcutSatir > sonSatir)
        {
            yeniIcerik += satir + "\n";
        }
        mevcutSatir++;
    }
    orijinal.close();

    LittleFS.remove(dosyaAdi);
    File yeniDosya = LittleFS.open(dosyaAdi, "w");
    if (yeniDosya)
    {
        yeniDosya.print(yeniIcerik);
        yeniDosya.close();
        yaz(F("Satirlar silindi."));
    }
    else
    {
        yaz(F("Yeni dosya olusturulamadi."));
    }
}
