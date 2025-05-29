#include "main.h"
#include "ZAMAN.h"
#include "avr/pgmspace.h"

// Her ay ismini tek tek PROGMEM ile tanımlıyoruz
const char ay_adi_1[] PROGMEM = "Ocak";    // 1. Ay Ocak
const char ay_adi_2[] PROGMEM = "Subat";   // 2. Ay Subat
const char ay_adi_3[] PROGMEM = "Mart";    // 3. Ay Mart
const char ay_adi_4[] PROGMEM = "Nisan";   // 4. Ay Nisan
const char ay_adi_5[] PROGMEM = "Mayis";   // 5. Ay Mayıs
const char ay_adi_6[] PROGMEM = "Haziran"; // 6. Ay Haziran
const char ay_adi_7[] PROGMEM = "Temmuz";  // 7. Ay Temmuz
const char ay_adi_8[] PROGMEM = "Agustos"; // 8. Ay Ağustos
const char ay_adi_9[] PROGMEM = "Eylul";   // 9. Ay Eylül
const char ay_adi_10[] PROGMEM = "Ekim";   // 10. Ay Ekim
const char ay_adi_11[] PROGMEM = "Kasim";  // 11. Ay Kasım
const char ay_adi_12[] PROGMEM = "Aralik"; // 12. Ay Aralık

// Ay isimlerinin referanslarını içeren dizi
const char *const ay_isimleri[] PROGMEM = {
    ay_adi_1, ay_adi_2, ay_adi_3, ay_adi_4,
    ay_adi_5, ay_adi_6, ay_adi_7, ay_adi_8,
    ay_adi_9, ay_adi_10, ay_adi_11, ay_adi_12};

const char gun_adi_0[] PROGMEM = "Pazar";
const char gun_adi_1[] PROGMEM = "Pzartesi";
const char gun_adi_2[] PROGMEM = "Sali";
const char gun_adi_3[] PROGMEM = "Carsamba";
const char gun_adi_4[] PROGMEM = "Persembe";
const char gun_adi_5[] PROGMEM = "Cuma";
const char gun_adi_6[] PROGMEM = "Cumrtesi";

const char *const gun_isimleri[] PROGMEM = {
    gun_adi_0, gun_adi_1, gun_adi_2, gun_adi_3,
    gun_adi_4, gun_adi_5, gun_adi_6};

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
    sn = depo.oku8(_EprAdr_sn);
    dk = depo.oku8(_EprAdr_dk);
    saat = depo.oku8(_EprAdr_saat);
    gun = depo.oku8(_EprAdr_gun);
    ay = depo.oku8(_EprAdr_ay); 
    yil = depo.oku16(_EprAdr_yil);
    hafta_gunu = depo.oku8(_EprAdr_hafta);
}

void __tarih::epr_yaz_saat()
{
    depo.yaz(_EprAdr_sn, sn);
    depo.yaz(_EprAdr_dk, dk);
    depo.yaz(_EprAdr_saat, saat);
}
void __tarih::epr_yaz_tarih()
{
    depo.yaz(_EprAdr_gun, gun);
    depo.yaz(_EprAdr_ay, ay); // Ay 1’den başlayacak
    depo.yaz16(_EprAdr_yil, yil);
    depo.yaz(_EprAdr_hafta, hafta_gunu);
}
void __tarih::epr_sifirla()
{
    depo.yaz(_EprAdr_sn, 0);
    depo.yaz(_EprAdr_dk, 0);
    depo.yaz(_EprAdr_saat, 0);
    depo.yaz(_EprAdr_gun, 0);
    depo.yaz(_EprAdr_ay, 1); // Ay 1’den başlayacak
    depo.yaz16(_EprAdr_yil, 2000);
    depo.yaz(_EprAdr_hafta, 0);
}

char *__tarih::ay_adi_(uint8_t ay_index)
{
    static char buffer[15];
    // Burada ay_index'i 1'den başlatıyoruz
    strcpy_P(buffer, (PGM_P)pgm_read_word(&(ay_isimleri[ay_index - 1]))); // ay_index 1'den başlıyor
    return buffer;
}

char *__tarih::gun_adi_(uint8_t gun_index)
{
    static char buffer[15];
    if (gun_index > 6)
    {
        strcpy(buffer, "?");
        return buffer;
    }
    strcpy_P(buffer, (PGM_P)pgm_read_word(&(gun_isimleri[gun_index])));
    return buffer;
}
