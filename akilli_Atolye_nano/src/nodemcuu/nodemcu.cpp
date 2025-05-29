#include "main.h"
#include "nodemcu.h"

class __nodemcu nodemcu;

void zaman_guncelle();
void zaman_gonder();

void __nodemcu::seri_istekler()
{
    if (port.paket_boyut() < 1)
        return;
    if (port.veri(0) == "zaman")
        zaman_guncelle();
}
void zaman_guncelle()
{
    if (port.paket_boyut() < 4)
        return;
    if (port.veri(0) != "zaman")
        return;
    String tarihStr = port.veri(1);
    int ilk = tarihStr.indexOf('/');
    int son = tarihStr.lastIndexOf('/');
    if (ilk == -1 || son == -1 || ilk == son)
        return;
    tarih.gun = tarihStr.substring(0, ilk).toInt();
    tarih.ay = tarihStr.substring(ilk + 1, son).toInt();
    tarih.yil = tarihStr.substring(son + 1).toInt();
    String saatStr = port.veri(2);
    ilk = saatStr.indexOf(':');
    son = saatStr.lastIndexOf(':');
    if (ilk == -1 || son == -1 || ilk == son)
        return;
    tarih.saat = saatStr.substring(0, ilk).toInt();
    tarih.dk = saatStr.substring(ilk + 1, son).toInt();
    tarih.sn = saatStr.substring(son + 1).toInt();
    tarih.hafta_gunu = port.veri(3).toInt();
    tarih.epr_yaz_saat();
    tarih.epr_yaz_tarih();
}
void zaman_gonder()
{
    String veri = "#zaman#";
    veri += String(tarih.gun) + "/";
    veri += String(tarih.ay) + "/";
    veri += String(tarih.yil) + " ";
    if (tarih.saat < 10)
        veri += "0";
    veri += String(tarih.saat) + ":";
    if (tarih.dk < 10)
        veri += "0";
    veri += String(tarih.dk) + ":";
    if (tarih.sn < 10)
        veri += "0";
    veri += String(tarih.sn) + " ";
    veri += String(tarih.hafta_gunu);
    veri += "#";
    Serial.println(veri);
}
