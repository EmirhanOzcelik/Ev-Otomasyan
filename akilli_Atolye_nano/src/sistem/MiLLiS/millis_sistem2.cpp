#include "main.h"

#define sistem_aktif true

void __calisma_zaman::calistir2()
{
    tarih.hesapla();
#if sistem_aktif == true
    sn_sayac++;
    if (sn_sayac % 2 == 0)
    {
        /// her 2sn
        /// her 2sn
    }
    else if (sn_sayac % 3 == 0)
    {
        /// her 3sn
        /// her 3sn
    }
    else if (sn_sayac % 5 == 0)
    {
        /// her 5sn
        /// her 5sn
    }
    else if (sn_sayac % 7 == 0)
    {
        /// her 7sn
        sayac.azalt(keypad.sifre);
        sayac.azalt(sayac.azalan.animasyon_degistirici, 0);
        if (sayac.azalan.animasyon_degistirici <= 0)
            sayac.azalan.animasyon_degistirici = __sayac_animasyon_Degistrci;
        /// her 7sn
    }
    else if (sn_sayac % 11 == 0)
    {
        /// her 11sn
        if (sayac.azalan.keypad_spam < __sayac_keypd_spam)
            sayac.arttir(sayac.azalan.keypad_spam, __sayac_keypd_spam);
        /// her 11sn
    }
    else if (sn_sayac % 13 == 0)
    {
        /// her 13sn
        sistem.vcc_olc();
        random_esmaulHusna();
        /// her 13sn
    }
    else if (sn_sayac % 17 == 0)
    {
        sn_sayac = 0;
        /// her 13sn
        if (sayac.azalan.keypad_hatali_giris < __sayac_hatali_girs)
            sayac.arttir(sayac.azalan.keypad_hatali_giris, __sayac_hatali_girs);
        /// her 13sn
    }
#endif
}