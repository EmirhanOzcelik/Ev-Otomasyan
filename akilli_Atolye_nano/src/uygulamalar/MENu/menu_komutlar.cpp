#include "main.h"
extern uint8_t _satirlar[];
extern uint8_t islem_kod;
extern void L1_s1();
extern void L1_s2();
extern void L1_s3();
extern void L1_s4();
extern void L1_s5();

void liste_olaylar();

void liste_olaylar()
{
    switch (keypad.menu_sistem_sutun())
    {
    case 0:
        switch (keypad.menu_sistem_satir())
        {
        case 0:
            L1_s1();
            break;
        case 1:
            L1_s2();
            break;
        case 2:
            L1_s3();
            break;
        case 3:
            L1_s4();
            break;
        case 4:
            L1_s5();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}