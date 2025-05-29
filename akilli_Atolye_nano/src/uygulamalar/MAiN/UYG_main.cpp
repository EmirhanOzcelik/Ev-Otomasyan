#include "main.h"
#include "UYG_main.h"
class __uygulamalar uygulama;

uint8_t kl1 = 0;
uint8_t kl2 = 0;
uint8_t kl3 = 0;
uint8_t kl4 = 0;

uint8_t _saat_konumY = 2;
uint8_t _saat_konumX = 0;

#define sn_yaz true
#define _saatX (_saat_konumX)
#define _zamanayiracX (_saatX + 2 * font1_Xpix)
#define _dakikaX (_zamanayiracX + font1_Xpix) // x = 30 de biter
#define _zamanayirac2X (_dakikaX + 2 * font1_Xpix)
#define saniyeX (_zamanayirac2X + font1_Xpix) // x = 40 de biter

#if sn_yaz == false
#define logo_sn_basla 2
#else
#define logo_sn_basla 14
#endif

#define logoY 0
#define logo_pildeger (saniyeX + logo_sn_basla)
#define logo_kilit (logo_pildeger + 12)
#define logo_girishak (logo_kilit + 12)
#define logo_baglanti (logo_girishak + 12)

#define animasyonY (_saat_konumY + 15)

void __uygulamalar::ustpanel()
{
#if logolar == true
    if (sayac.azalan.keypad_spam >= 3)
        ekran.bitmap_ciz(logo_girishak, logoY, 10, 10, _lgirishak3_10x10);
    else if (sayac.azalan.keypad_spam == 2)
        ekran.bitmap_ciz(logo_girishak, logoY, 10, 10, _lgirishak2_10x10);
    else if (sayac.azalan.keypad_spam <= 0)
        ekran.bitmap_ciz(logo_girishak, logoY, 10, 10, _lgirishak1_10x10);

    if (sistem.pil_deger <= 1)
        ekran.bitmap_ciz(logo_pildeger, logoY, 10, 10, _lbatarya25_10x10);
    else if (sistem.pil_deger == 2)
        ekran.bitmap_ciz(logo_pildeger, logoY, 10, 10, _lbatarya50_10x10);
    else if (sistem.pil_deger == 3)
        ekran.bitmap_ciz(logo_pildeger, logoY, 10, 10, _lbatarya75_10x10);
    else if (sistem.pil_deger >= 4)
        ekran.bitmap_ciz(logo_pildeger, logoY, 10, 10, _lbatarya100_10x10);

    if (keypad.sifre <= 0)
        ekran.bitmap_ciz(logo_kilit, logoY, 10, 10, _lkilitli1_10x10);
    else
        ekran.bitmap_ciz(logo_kilit, logoY, 10, 10, _lkilitli0_10x10);

#endif
    ekran.yaz(tarih.saat, _saatX, _saat_konumY);
    ekran.yaz(tarih.dk, _dakikaX, _saat_konumY);
#if sn_yaz == true
    ekran.yaz(tarih.sn, saniyeX, _saat_konumY);
#endif
    if (sayac.degisen.imlec)
    {
        ekran.yaz(F(":"), 1, _zamanayiracX, _saat_konumY);
#if sn_yaz == true
        ekran.yaz(F(":"), 1, _zamanayirac2X, _saat_konumY);
#endif
    }
}

void __uygulamalar::anaekran()
{
    animasyon_sistem();
    ustpanel();
}

void __uygulamalar::_secim()
{
    switch (no)
    {
    case __ID_anaekran:
        uygulama.anaekran();
        break;
    case __ID_tuslarekran:
        uygulama.tustakim();
        break;
    case __ID_menuekran:
        uygulama.menu();
        break;
        no = __ID_anaekran;
        break;
    }
}

void __uygulamalar::bilgi_ekran()
{
    uint16_t k = 0;
    char n = '\0';
    while (k * g_ms < 10000 && n == '\0')
    {
        n = keypad.oku_();
        if (millis() - gecen_zaman >= g_ms)
        {
            k++;
            gecen_zaman = millis();
            millis_timer.calistir();
            ekran.sil();
            ekran.yaz(F("MucithaneX"), 10, 15, 0);
            ekran.yaz(F("gelistirici;"), 12, 10, 10);
            ekran.yaz(F("emirhan ozclk"), 13, 4, 20);
            ekran.yaz(F("iletisim;"), 9, 10, 30);
            ekran.yaz(F("5442209871"), 10, 14, 40);
            ekran.guncelle();
        }
    }
    sayac.azalan.keypad_aktiflik = __sayac_keyp_aktf2;
    no = __ID_menuekran;
}

void __uygulamalar::sensor_test(bool k)
{
#ifdef testt
    while (k)
    {
        sistem.sensor_oku();
        ekran.sil();
        ekran.yaz(F("buton:"), 6, 0, 0);
        ekran.yaz(F("sensor:"), 7, 0, 10);
        ekran.yaz(F("pot:"), 4, 0, 20);
        ekran.yaz(F("voltaj:"), 7, 0, 30);
        ekran.yaz((uint8_t)sistem.buton, 40, 0);
        ekran.yaz((uint8_t)sistem.sensor, 45, 10);
        ekran.yaz(sistem.potansiyometre, 30, 20);
        ekran.guncelle();
    }
#endif
}

void __uygulamalar::animasyon_sistem()
{
    switch (sayac.azalan.animasyon_degistirici)
    {
    case 5:
        ekran.yaz(tarih.gun, 0, animasyonY);
        ekran.yaz(tarih.ay_adi_(tarih.ay), 14, animasyonY);
        ekran.yaz(tarih.yil, 60, animasyonY);
        ekran.yaz(tarih.gun_adi_(tarih.hafta_gunu), 14, animasyonY + 10);
        ekran.yaz(tarih.saat, 20, animasyonY + 20);
        ekran.yaz(tarih.dk, 35, animasyonY + 20);
        ekran.yaz(tarih.sn, 50, animasyonY + 20);
        if (sayac.degisen.imlec)
        {
            ekran.yaz(F(":"), 1, 30, animasyonY + 20);
            ekran.yaz(F(":"), 1, 45, animasyonY + 20);
        }
        break;
    case 4:
        if (sayac.degisen.imlec)
            ekran.yaz(uygulama.esmaulHusnA, ekran_ORTA, _saat_konumY + 12);
        ekran.bitmap_ciz(0, 28, 84, 20, _lbismillah_84x20);
        break;
    case 3:
        ekran.kayan_yaz(F("Mucithane"), 9, animasyonY);
        ekran.yaz(F("V3.8"), 4, 55, animasyonY + 20);
        if (sayac.degisen.imlec)
            ekran.kayan_yaz(F("   ^_^   "), 9, animasyonY + 10);
        else
            ekran.kayan_yaz(F("   *_*   "), 9, animasyonY + 10);
        break;
    case 2:
        ekran.yaz(F("kod"), 3, 9, animasyonY);
        ekran.yaz(F("islem"), 5, 50, animasyonY);
        ekran.yaz(F("Menu"), 4, 55, animasyonY + 10);
        ekran.yaz(F("Epr"), 3, 58, animasyonY + 20);
        ekran.yaz(F("2+3+OK:"), 7, 0, animasyonY + 10);
        ekran.yaz(F("1+2+OK:"), 7, 0, animasyonY + 20);
        break;
    case 1:
        ekran.yaz(F("Giris icin"), 9, 10, animasyonY);
        if (sayac.degisen.imlec)
            ekran.yaz(F("kart okutun"), 11, 9, animasyonY + 10);
        else
            ekran.yaz(F("sifre yazin"), 11, 9, animasyonY + 10);
        break;
    default:
        sayac.azalan.animasyon_degistirici = 4;
        break;
    }
}