#include "main.h"

#define satir_aralik 10
#define satir_1 0
#define satir_2 (satir_1 + satir_aralik)
#define satir_3 (satir_2 + satir_aralik)
#define satir_4 (satir_3 + satir_aralik)
#define satir_5 (satir_4 + satir_aralik)
uint8_t _satirlar[] = {satir_1, satir_2, satir_3, satir_4, satir_5};

#define imlec_sutun 0
#define sutun_baslangic 8

uint8_t islem_kod = 0;

void liste1();
void liste2();

void __uygulamalar::menu()
{
    if (sayac.azalan.keypad_aktiflik <= 0)
        no = __ID_anaekran;
    if (sayac.degisen.imlec2)
        ekran.yaz(F(">"), 1, imlec_sutun, _satirlar[keypad.menu_sistem_satir()]);
    switch (keypad.menu_sistem_sutun())
    {
    case 0:
        liste1();
        break;
    default:
        no = __ID_anaekran;
        sayac.azalan.keypad_aktiflik = 0;
        break;
    }
}
void liste1()
{
    ekran.yaz(F("makine esitle"), 13, sutun_baslangic-4, satir_1);
    ekran.yaz(F("tarih ayarla"), 12, sutun_baslangic, satir_2);
    ekran.yaz(F("saat ayarla"), 11, sutun_baslangic, satir_3);
    ekran.yaz(F("ana menu don"), 12, sutun_baslangic, satir_4);
    ekran.yaz(F("bilgi ekran"), 11, sutun_baslangic, satir_5);
}