#include "main.h"
#include "ZAMAN.h"

// -------------------------
// tarih sınıfı nesnesi (global olarak tanımlı olmalı, dışarıdan erişilmesi için extern kullanabilirsiniz)
// -------------------------
class __tarih tarih;

// -------------------------
// Artık yıl kontrolü
// -------------------------
bool __tarih::artik_yil(uint16_t y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// -------------------------
// Ayın kaç gün çektiği
// -------------------------
uint8_t __tarih::ay_gun_sayisi(uint8_t ay, uint16_t y)
{
    const uint8_t gunler[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Artık yıl kontrolü için 2. ay (Şubat) özel durumu
    if (ay == 2 && artik_yil(y))
        return 29;

    // Aylar artık 1'den başlıyor, dolayısıyla direk kullanabiliriz
    return gunler[ay - 1]; // Ay, 1'den başlar, bu yüzden -1 ile doğru indexi elde ederiz
}

// -------------------------
// Tarih ve saat ilerletme (her saniye çağrılmalı)
// -------------------------
void __tarih::hesapla()
{
    sn++; // saniyeyi artır
    if (sn >= 60)
    {
        sn = 0;
        dk++; // dakikayı artır
        if (dk >= 60)
        {
            dk = 0;
            saat++; // saati artır
            if (saat >= 24)
            {
                saat = 0;
                gun++;                             // günü artır
                hafta_gunu = (hafta_gunu + 1) % 7; // hafta günü (0-Pazar, 1-Pazartesi, ...)

                // Eğer gün sayısı ayın gün sayısını aşıyorsa, ayı artır
                if (gun > ay_gun_sayisi(ay, yil))
                {
                    gun = 1;
                    ay++;
                    if (ay > 12)
                    {
                        ay = 1;
                        yil++; // yıl artışı
                    }
                }
            }
        }
    }
}

void __tarih::hafta_hesapla(uint8_t y, uint8_t m, uint16_t d)
{
    if (m < 3)
    {
        m += 11; // Ocak ve Şubat aylarını 13 ve 14 olarak kabul et
        y--;
    }
    int h = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    hafta_gunu = (h + 6) % 7; // 0: Pazar, 1: Pazartesi, ..., 6: Cumartesi
}

// -------------------------
// Saat ayarlama fonksiyonu
// -------------------------
void __tarih::saat_(uint8_t saat_, uint8_t dk_, uint8_t sn_)
{
    saat = saat_; // saat değerini ayarla
    dk = dk_;     // dakika değerini ayarla
    sn = sn_;     // saniye değerini ayarla
}

// -------------------------
// Tarih ayarlama fonksiyonu
// -------------------------
void __tarih::tarih_(uint16_t yil_, uint8_t ay_, uint8_t gun_, uint8_t hafta_)
{
    yil = yil_;          // yıl değerini ayarla
    ay = ay_;            // ay değerini ayarla (1'den başlıyor)
    gun = gun_;          // gün değerini ayarla
    hafta_gunu = hafta_; // hafta günü (0-Pazar, 1-Pazartesi, ...)
}

void __tarih::epr_oku()
{
    sn = epr.oku8(_EprAdr_sn);
    dk = epr.oku8(_EprAdr_dk);
    saat = epr.oku8(_EprAdr_saat);
    gun = epr.oku8(_EprAdr_gun);
    ay = epr.oku8(_EprAdr_ay);
    yil = epr.oku16(_EprAdr_yil);
    hafta_gunu = epr.oku8(_EprAdr_hafta);
}

void __tarih::epr_yaz_saat()
{
    epr.yaz(_EprAdr_sn, sn);
    epr.yaz(_EprAdr_dk, dk);
    epr.yaz(_EprAdr_saat, saat);
}
void __tarih::epr_yaz_tarih()
{
    epr.yaz(_EprAdr_gun, gun);
    epr.yaz(_EprAdr_ay, ay); // Ay 1’den başlayacak
    epr.yaz16(_EprAdr_yil, yil);
    epr.yaz(_EprAdr_hafta, hafta_gunu);
}
void __tarih::epr_yaz_full()
{
    epr_yaz_saat();
    epr_yaz_tarih();
    epr_kaydet_izin = false;
}
void __tarih::epr_sifirla()
{
    epr.yaz(_EprAdr_sn, 0);
    epr.yaz(_EprAdr_dk, 0);
    epr.yaz(_EprAdr_saat, 0);
    epr.yaz(_EprAdr_gun, 0);
    epr.yaz(_EprAdr_ay, 1); // Ay 1’den başlayacak
    epr.yaz16(_EprAdr_yil, 2000);
    epr.yaz(_EprAdr_hafta, 0);
}
String __tarih::ayyil_cikti()
{
    return String(yil) + "/" + String(ay) + "/" + String(gun) + " ";
}
String __tarih::saatdk_cikti()
{
    return String(saat) + ":" + String(dk) + ":" + String(sn) + " ";
}
String __tarih::full_cikti()
{
    return ayyil_cikti() + saatdk_cikti();
}