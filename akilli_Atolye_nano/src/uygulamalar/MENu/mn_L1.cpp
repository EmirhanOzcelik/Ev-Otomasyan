#include "main.h"

void L1_s1();
void L1_s2();
void L1_s3();
void L1_s4();
void L1_s5();

void L1_s1() // sistem eşitle
{
    uygulama.sistem_reset();
    sistem.sifirla();
}
void L1_s2() // tarih ayarla
{
    uygulama.tarih_ayar();
}
void L1_s3() // saat ayarla
{
    uygulama.saat_ayar();
}
void L1_s4() // ana menu
{
    keypad.mod = false;
    uygulama.no = __ID_anaekran;
    sayac.azalan.keypad_aktiflik = 0;
}
void L1_s5() // bilgi ekran
{
    uygulama.bilgi_ekran();
}