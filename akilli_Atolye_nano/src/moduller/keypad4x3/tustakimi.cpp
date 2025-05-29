#include "main.h"
#include "tustakimi.h"
#if Tus_Takimi == true
#define max_Satir 4 // n-1 degeri satir(4 için 5 satir)
#define max_Sutun 0 // max sayfa sayısı (n-1)

const uint8_t satirPinleri[QSatir] = {A0, A1, A2, A3};
const uint8_t sutunPinleri[QSutun] = {7, 8, A4};

const char tuslar[QSatir][QSutun] PROGMEM = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'Y', '0', 'N'}};

const char menu[QSatir][QSutun] PROGMEM = {
    {'<', '_', '>'},
    {'{', 'U', '}'},
    {'L', 'O', 'R'},
    {'F', 'D', 'B'}};

class __tustakiM keypad;

void __tustakiM::kur()
{
    for (byte i = 0; i < QSatir; i++)
    {
        pinMode(satirPinleri[i], OUTPUT);
        digitalWrite(satirPinleri[i], HIGH);
    }
    for (byte i = 0; i < QSutun; i++)
    {
        pinMode(sutunPinleri[i], INPUT_PULLUP);
    }
}

char __tustakiM::oku_()
{
    char tus = '\0';
    for (byte r = 0; r < QSatir; r++)
    {
        digitalWrite(satirPinleri[r], LOW);
        for (byte c = 0; c < QSutun; c++)
        {
            if (digitalRead(sutunPinleri[c]) == LOW)
            {
                millis_timer.delay(50);
                while (digitalRead(sutunPinleri[c]) == LOW)
                {
                    if (millis() - gecen_zaman >= g_ms)
                    {
                        gecen_zaman = millis();
                        millis_timer.calistir();
                    }
                }
                if (mod == 0)
                    tus = pgm_read_byte_near(tuslar[r] + c);
                else
                    tus = pgm_read_byte_near(menu[r] + c);
                millis_timer.delay(50);
                return tus;
            }
        }
        digitalWrite(satirPinleri[r], HIGH);
    }
    return tus;
}
// 0,1,2,3,4,5...
uint16_t __tustakiM::menu_sistem_sutun()
{
    return Usutun;
}
// 0,1,2,3,4,5...
uint16_t __tustakiM::menu_sistem_satir()
{
    return Usatir;
}
void __tustakiM::tus_azalt(bool satir)
{
    if (satir)
    {
        if (Usatir > 0)
            Usatir--;
        else
            Usatir = max_Satir;
    }
    else
    {
        if (Usutun > 0)
            Usutun--;
        else
            Usutun = max_Sutun;
    }
}
void __tustakiM::tus_arttir(bool satir)
{
    if (satir)
    {
        if (Usatir < max_Satir)
            Usatir++;
        else
            Usatir = 0;
    }
    else
    {
        if (Usutun < max_Sutun)
            Usutun++;
        else
            Usutun = 0;
    }
}

#endif