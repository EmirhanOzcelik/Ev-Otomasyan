#include "main.h"

void __uygulamalar::sistem_reset()
{
    uint8_t k = 0;
    while (k * g_ms < 2000)
    {
        if (millis() - gecen_zaman >= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            k++;
            ekran.sil();
            ekran.yaz(F("Yeniden"), 7, ekran_ORTA, 0);
            ekran.yaz(F("baslatiliyor"), 12, ekran_ORTA, 10);
            if (sayac.degisen.imlec2)
                ekran.yaz(F("bekleyin..."), 11, 0, 20);
            ekran.guncelle();
        }
    }
}

void __uygulamalar::epr_reset()
{
    uint8_t k = 0;
    while (k * g_ms < 2000)
    {
        if (millis() - gecen_zaman >= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            k++;
            ekran.sil();
            ekran.yaz(F("EEPROM"), 6, ekran_ORTA, 0);
            ekran.yaz(F("resetleniyor"), 12, ekran_ORTA, 10);
            if (sayac.degisen.imlec2)
                ekran.yaz(F("bekleyin..."), 11, ekran_ORTA, 20);
            ekran.guncelle();
        }
    }
}

void __uygulamalar::saat_ayar()
{
    uint16_t k = 0;
    uint8_t imlec = 0; // YUKARDAN ASAGIYA 0SAAT,1DK,2SN,3KAYDET,4İPTAL
    bool sayac_imlec = true;
    uint8_t secim = 0; // 1 ise kayit edildi 2 ise iptal edildi 0 ise zaman aşımı
    int8_t a = 0;      // saat
    int8_t b = 0;      // dk
    int16_t c = 0;     // sn
    while (k * g_ms < 15000)
    {
        int8_t saatd = a + tarih.saat;
        int8_t dakikad = b + tarih.dk;
        int8_t saniyed = c + tarih.sn;
        char p = keypad.oku_();
        switch (p)
        {
        case 'D': ////////////////////////// imlec yukarı
            k = 0;
            if (imlec < 4)
                imlec++;
            else
                imlec = 0;
            if (imlec > 2)
                sayac_imlec = false;
            else
                sayac_imlec = true;
            break; /////////////////////////
        case 'U':  ///////////////////////// imlec aşagı
            k = 0;
            if (imlec > 0)
                imlec--;
            else
                imlec = 4;
            if (imlec > 2)
                sayac_imlec = false;
            else
                sayac_imlec = true;
            break; //////////////////////////
        case 'R':  ////////////////////////// paket artış
            k = 0;
            if (imlec == 2) // saniye arttır
            {
                sayac_imlec = true;
                if (saniyed < 60)
                    c++;
                else
                    c = -tarih.sn;
            }
            else if (imlec == 1) // dk arttır
            {
                sayac_imlec = true;
                if (dakikad < 60)
                    b++;
                else
                    b = -tarih.dk;
            }
            else if (imlec == 0) // saat arttır
            {
                sayac_imlec = true;
                if (saatd < 24)
                    a++;
                else
                    a = -tarih.saat;
            }
            else
                sayac_imlec = false;
            break; //////////////////////////
        case 'L':  ////////////////////////// paket azalış
            k = 0;
            if (imlec == 2)
            {
                sayac_imlec = true;
                if (saniyed > 0) // saniye azalt
                    c--;
                else
                    c = 60 - tarih.sn;
            }
            else if (imlec == 1)
            {
                sayac_imlec = true;
                if (dakikad > 0) // dakika azalt
                    b--;
                else
                    b = 60 - tarih.dk;
            }
            else if (imlec == 0)
            {
                sayac_imlec = true;
                if (saatd > 0) // saat azalt
                    a--;
                else
                    a = 24 - tarih.saat;
            }
            else
                sayac_imlec = false;
            break;
        case 'O':
            k = 0;
            if (imlec == 4) // iptal
            {
                k = 13000 / g_ms;
                secim = 2;
            }
            else if (imlec == 3) // kaydet
            {
                k = 13000 / g_ms;
                tarih.saat = saatd;
                tarih.dk = dakikad;
                tarih.sn = saniyed;
                secim = 1;
            }
            else if (imlec == 2)
                c = 0;
            else if (imlec == 1)
                b = 0;
            else if (imlec == 0)
                a = 0;
            break;
        default:
            break;
        }
        if (millis() - gecen_zaman >= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            k++;

            ekran.sil();
            if (k * g_ms > 11000)
            {
                if (secim == 0)
                {
                    ekran.yaz(F("geri donus yok"), 14, 0, 0);
                    ekran.yaz((15000 - k * g_ms) / 1000, 0, 10);
                    ekran.yaz(F("sn sonra"), 8, 15, 10);
                    ekran.yaz(F("cikilacak"), 8, 19, 20);
                }
                else if (secim == 1)
                {
                    ekran.yaz(F("kayit ediliyor"), 14, 0, 0);
                    uint32_t kalan = 15000 - (k * g_ms);
                    uint8_t ik = 100 - ((kalan * 100) / 4000);
                    if (ik > 100)
                        ik = 100;
                    ekran.yaz(ik, 15, 20);
                    ekran.yaz(F("%"), 1, 0, 20);
                    ekran.yaz(F("..."), 3, 65, 20);
                }
                else if (secim == 2)
                {
                    ekran.yaz(F("iptal edildi"), 12, 5, 0);
                    ekran.yaz((15000 - k * g_ms) / 1000, 0, 10);
                    ekran.yaz(F("sn sonra"), 8, 15, 10);
                    ekran.yaz(F("cikilacak"), 8, 19, 20);
                }
            }
            else
            {
                ekran.yaz(F("Saat ayar"), 9, ekran_ORTA, 0);
                ekran.yaz(F("saat:"), 5, 21, 8);
                ekran.yaz(F("dakika:"), 7, 12, 16);
                ekran.yaz(F("saniye:"), 7, 12, 24);
                ekran.yaz(saatd, 52, 8);
                ekran.yaz(dakikad, 58, 16);
                ekran.yaz(saniyed, 58, 24);
                ekran.yaz(F("kaydet"), 6, 24, 32);
                ekran.yaz(F("iptal"), 5, 27, 40);
                if (sayac_imlec && sayac.degisen.imlec2)
                {
                    ekran.yaz(F("<-"), 2, 0, (imlec + 1) * 8);
                    ekran.yaz(F("+>"), 2, 72, (imlec + 1) * 8);
                }
                else if (sayac.degisen.imlec2)
                {
                    ekran.yaz(F(" *"), 2, 0, (imlec + 1) * 8);
                    ekran.yaz(F("* "), 2, 72, (imlec + 1) * 8);
                }
            }
            ekran.guncelle();
        }
    }

    if (secim == 1)
    {
        tarih.epr_yaz_saat();
        tarih.epr_oku();
    }
    millis_timer.delay(100);
}

void __uygulamalar::tarih_ayar()
{
    uint16_t k = 0;
    uint8_t imlec = 0; // 0: gun, 1: ay, 2: yil, 3:hafta günü, 4: kaydet, 5: iptal
    bool sayac_imlec = true;
    uint8_t secim = 0; // 0: zaman aşımı, 1: kaydedildi, 2: iptal edildi
    int8_t a = 0;      // gün
    int8_t b = 0;      // ay
    int16_t c = 0;     // yıl
    int16_t d = 0;     // hafta günü

    while (k * g_ms < 15000)
    {
        int8_t gund = a + tarih.gun;
        int8_t ayd = b + tarih.ay;
        int16_t yild = c + tarih.yil;
        int16_t haftd = d + tarih.hafta_gunu;

        char p = keypad.oku_();
        switch (p)
        {
        case 'D':
            k = 0;
            if (imlec < 5)
                imlec = imlec + 1;
            else
                imlec = 0;
            if (imlec > 3)
                sayac_imlec = false;
            else
                sayac_imlec = true;
            break;
        case 'U':
            k = 0;
            if (imlec > 0)
                imlec = imlec - 1;
            else
                imlec = 5;
            if (imlec > 3)
                sayac_imlec = false;
            else
                sayac_imlec = true;
            break;
        case 'R':
            k = 0;
            sayac_imlec = true;
            if (imlec == 0)
                if (gund < 31)
                    a = a + 1;
                else
                    a = -1 * tarih.gun;
            else if (imlec == 1)
                if (ayd < 12)
                    b = b + 1;
                else
                    b = -tarih.ay + 1;
            else if (imlec == 2)
                c++;
            else if (imlec == 3)
                if (haftd < 6)
                    d = d + 1;
                else
                    d = -1 * tarih.hafta_gunu;
            else
                sayac_imlec = false;
            break;
        case 'L':
            k = 0;
            sayac_imlec = true;
            if (imlec == 0)
                if (gund > 1)
                    a = a - 1;
                else
                    a = 31 - tarih.gun;
            else if (imlec == 1)
                if (ayd > 1)
                    b = b - 1;
                else
                    b = 12 - tarih.ay;
            else if (imlec == 2)
                if (yild > 2000)
                    c = c - 1;
                else
                    c = 2000;
            else if (imlec == 3)
                if (haftd > 0)
                    d = d - 1;
                else
                    d = 6 - tarih.hafta_gunu;
            else
                sayac_imlec = false;
            break;

        case 'O':
            k = 0;
            if (imlec == 4) // KAYDET
            {
                k = 13000 / g_ms;
                tarih.gun = gund;
                tarih.ay = ayd;
                tarih.yil = yild;
                tarih.hafta_gunu = haftd;
                secim = 1;
            }
            else if (imlec == 5) // İPTAL
            {
                k = 13000 / g_ms;
                secim = 2;
            }
            else if (imlec == 0)
                a = 0;
            else if (imlec == 1)
                b = 0;
            else if (imlec == 2)
                c = 0;
            else if (imlec == 3)
                d = 0;
            break;
        default:
            break;
        }

        if (millis() - gecen_zaman >= g_ms)
        {
            gecen_zaman = millis();
            millis_timer.calistir();
            k++;
            ekran.sil();
            if (k * g_ms > 11000)
            {
                if (secim == 0)
                {
                    ekran.yaz(F("geri donus yok"), 14, 0, 0);
                    ekran.yaz((15000 - k * g_ms) / 1000, 0, 10);
                    ekran.yaz(F("sn sonra"), 8, 15, 10);
                    ekran.yaz(F("cikilacak"), 8, 19, 20);
                }
                else if (secim == 1)
                {
                    ekran.yaz(F("kayit ediliyor"), 14, 0, 0);
                    uint32_t kalan = 15000 - (k * g_ms);
                    uint8_t ik = 100 - ((kalan * 100) / 4000);
                    if (ik > 100)
                        ik = 100;
                    ekran.yaz(ik, 15, 20);
                    ekran.yaz(F("%"), 1, 0, 20);
                    ekran.yaz(F("..."), 3, 65, 20);
                }
                else if (secim == 2)
                {
                    ekran.yaz(F("iptal edildi"), 12, 5, 0);
                    ekran.yaz((15000 - k * g_ms) / 1000, 0, 10);
                    ekran.yaz(F("sn sonra"), 8, 15, 10);
                    ekran.yaz(F("cikilacak"), 8, 19, 20);
                }
            }
            else
            {
                ekran.yaz(F("gun:"), 4, 21, 0);
                ekran.yaz(gund, 52, 0);
                ekran.yaz(tarih.ay_adi_(ayd), 25, 8);
                ekran.yaz(F("yil:"), 4, 18, 16);
                ekran.yaz(yild, 46, 16);
                ekran.yaz(tarih.gun_adi_(haftd), 18, 24);
                ekran.yaz(F("kaydet"), 6, 24, 32);
                ekran.yaz(F("iptal"), 5, 27, 40);

                if (sayac_imlec && sayac.degisen.imlec2)
                {
                    ekran.yaz(F("<-"), 2, 0, imlec * 8);
                    ekran.yaz(F("+>"), 2, 72, imlec * 8);
                }
                else if (sayac.degisen.imlec2)
                {
                    ekran.yaz(F(" *"), 2, 0, imlec * 8);
                    ekran.yaz(F("* "), 2, 72, imlec * 8);
                }
            }
            ekran.guncelle();
        }
    }
    if (secim == 1)
    {
        tarih.epr_yaz_tarih();
        tarih.epr_oku();
    }
    millis_timer.delay(100);
}
