#include "main.h"
#if Tus_Takimi == true

#define tus_takim_x ((Ekran_Xpix - 3 * (font1_Xpix + aralikX)) / 2)
#define tus_takim_y 12
#define aralikX 13
#define aralikY 1

uint8_t kutuX1 = Ekran_Xpix;
uint8_t kutuX2 = kutuX1 - 5;
uint8_t kutuY = Ekran_Ypix;

void __uygulamalar::tustakim()
{
    if (sayac.azalan.keypad_aktiflik <= 0)
    {
        uygulama.no = __ID_anaekran;
        keypad.girilen = "";
    }
    else
    {
        for (uint8_t c = 0; c < QSutun; c++)
        {
            for (uint8_t k = 0; k < QSatir; k++)
            {
                uint8_t x = tus_takim_x + c * (font1_Xpix + aralikX);
                uint8_t y = tus_takim_y + k * (font1_Ypix + aralikY);
                char v[2];
                v[0] = pgm_read_byte(&(tuslar[k][c]));
                v[1] = '\0';
                ekran.yaz(v, x, y);
                if (v[0] == keypad.son_okunan && sayac.azalan.keypad_tus_cerceve != 0)
                {
                    kutuX1 = x - 8;
                    kutuX2 = x + 6;
                    kutuY = y;
                    ekran.yaz(F("["), 1, kutuX1, kutuY);
                    ekran.yaz(F("]"), 1, kutuX2, kutuY);
                }
            }
        }
        if (sayac.degisen.imlec)
        {
            ekran.yaz(F(">"), 1, 0, 0);
            ekran.yaz(F("<"), 1, 78, 0);
        }
        ekran.yaz(keypad.girilen, ekran_ORTA, 0);
    }
}
#endif