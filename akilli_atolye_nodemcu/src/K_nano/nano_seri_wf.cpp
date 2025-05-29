#include "main.h"

class __nano nano;

void __nano::seri_istekler()
{
    if (port.veri(0) == "nfc" && port.veri(1) == "kayit")
        nfc.kayit_izin = !nfc.kayit_izin;
    else if (port.veri(0) == "keypad" && port.veri(1) == "kayit")
        depo.ekle(kp_sifreler, port.veri(2));
}
