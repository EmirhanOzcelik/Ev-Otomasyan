#include "main.h"
#include "tustakimi.h"

#define __Keypad_sifre_bekleme_sn 3
#if Tus_Takimi == true
extern void liste_olaylar();

const char __KEYPAD_sifre_k[5][7] PROGMEM = {
    "739026",
    "185493",
};
const char __KEYPAD_sifre_y[5][7] PROGMEM = {
    "731072",
};
void __tustakiM::oku()
{
    okunan = oku_();
    if (okunan)
    {
        son_okunan = okunan;
        if (mod)
        {
            if (sayac.azalan.keypad_aktiflik <= 0)
                uygulama.no = __ID_anaekran;
            uygulama.no = __ID_menuekran;
            sayac.azalan.keypad_aktiflik = __sayac_keyp_aktf2;
            sayac.azalan.keypad_tus_cerceve = __sayac_keyp_tus_cerc;
            switch (okunan)
            {
            case 'U': // Yukarı
                tus_azalt(1);
                break;
            case 'D': // Aşağı
                tus_arttir(1);
                break;
            case 'L': // Sola
                tus_azalt(0);
                break;
            case 'R': // Sağa
                tus_arttir(0);
                break;
            case 'F': // yes
                kontrol2();
                break;
            case 'B': // no
                sil();
                break;
            case 'O': // no
                liste_olaylar();
                break;
            case '_': // 2
                ekleme_kontrol2();
                break;
            case '>': // 3
                ekleme_kontrol2();
                break;
            default:
                break;
            }
        }
        else
        {
            switch (okunan)
            {
            case 'Y':
                if (girilen.length() > 2)
                    kontrol();
                else
                    kontrol2();
                break;
            case 'N':
                sil();
                break;
            default:
                uygulama.no = __ID_tuslarekran;
                sayac.azalan.keypad_aktiflik = __sayac_keyp_aktf;
                sayac.azalan.keypad_tus_cerceve = __sayac_keyp_tus_cerc;
                ekleme_kontrol();
                break;
            }
        }
    }
}
void __tustakiM::ekleme_kontrol()
{
    if (girilen.length() > __KEYPAD_maxgirdi)
    {
        girilen = "";
        if (sayac.azalan.keypad_spam > 0)
        {
            uygulama.spam(4);
            sayac.azalan.keypad_spam--;
        }
        else
            uygulama.spam(20);
    }
    else
        girilen += okunan;
}
void __tustakiM::ekleme_kontrol2()
{
    if (girilen.length() > 3)
        girilen = "";
    else
        girilen += okunan;
}
void __tustakiM::kontrol()
{
    char buf[7];
    for (int c = 0; c < 5; c++)
    {
        strcpy_P(buf, __KEYPAD_sifre_k[c]);
        if (girilen.equals(buf))
        {
            sifre = __KEYPAD_sifresure;
            uygulama.basarili_giris(3);
            girilen = "";
            return;
        }
    }
    for (int c = 0; c < 5; c++)
    {
        strcpy_P(buf, __KEYPAD_sifre_y[c]);
        if (girilen.equals(buf))
        {
            sifre = __KEYPAD_sifresure2;
            uygulama.basarili_giris(3, true);
            girilen = "";
            return;
        }
    }
    sifre = 0;
    int16_t e = 0;
    int16_t k = __Keypad_sifre_bekleme_sn * 1000;
    uint8_t hata_kod = 0;
    gecen_zaman = millis();
    Serial.println("#keypad#" + girilen + "#");
    while (e * g_ms < k)
    {
        if (millis() - gecen_zaman >= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            e++;
            ekran.sil();
            uygulama.seri_veri_bekle(e * g_ms, k, port.islem, hata_kod);
            ekran.guncelle();
        }
        if (Serial.available() && !port.islem)
            port.oku();
        else if (port.islem)
        {
            port.ayikla();
            if (port.veri(0) == "keypad")
            {
                if (port.veri(1) == "dogru")
                {
                    sifre = __KEYPAD_sifresure;
                    e = 0;
                    hata_kod = 1;
                    port.islem = false;
                }
                if (port.veri(1) == "yanlis")
                {
                    sifre = 0;
                    e = 0;
                    hata_kod = 2;
                    port.islem = false;
                }
                else
                {
                    hata_kod = 3;
                    sifre = 0;
                    port.islem = false;
                    e = 0;
                }
            }
            else
            {
                hata_kod = 3;
                sifre = 0;
                port.temizle();
                e = 0;
            }
        } // port aayikla
    } // while
    if (sifre == 0)
        if (sayac.azalan.keypad_hatali_giris > 1)
            sayac.azalan.keypad_hatali_giris--;
        else
            uygulama.hatali_giris(20);
    else
        uygulama.basarili_giris(3);
    girilen = "";
}

void __tustakiM::kontrol2()
{
    if (girilen == "23" || girilen == "_>" || girilen == "32" || girilen == ">_") // mod değiş
    {
        moddegis();
    }
    girilen = "";
}

void __tustakiM::sil()
{
    if (keypad.girilen.length() > 0)
        keypad.girilen.remove(keypad.girilen.length() - 1);
}

#endif