#include "main.h"
#include "NFC_rdr.h"

#define SS_PIN 4  // RFID modülünün SDA pinine bağlı
#define RST_PIN 5 // RFID modülünün RST pinine bağlı
class __nfc nfc;

String uid = "";

MFRC522 rfid(SS_PIN, RST_PIN); // RFID nesnesi oluştur

void __nfc::kur()
{
    SPI.begin();
    rfid.PCD_Init();
    arkaplan_log += "nfc modulu baslatildi\n";
}

void __nfc::oku()
{
    uid = "";
    if (!rfid.PICC_IsNewCardPresent())
        return;
    if (!rfid.PICC_ReadCardSerial())
        return;
    arkaplan_log += "\nKart UID: ";
    for (byte i = 0; i < rfid.uid.size; i++)
    {
        uid += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
        uid += String(rfid.uid.uidByte[i], HEX) + " ";
    }
    arkaplan_log += uid + "\n";
    rfid.PICC_HaltA();
    if (!kayit_izin)
        kart_dogrula();
}
void __nfc::kart_kaydet()
{
    oku();
    if (uid == "")
        return;
    if (depo.ara(rf_sifreler, uid) >= 0)
    {
        arkaplan_log += "Bu kart zaten kayitli\n";
        return;
    }
    else
    {
        depo.ekle(rf_sifreler, uid);
        arkaplan_log += "Kart kaydedildi: " + uid + "\n";
    }
}

void __nfc::kart_dogrula()
{
    if (depo.ara(rf_sifreler, uid) >= 0)
    {
        arkaplan_log += "rfid kartla giris yapildi\n";
        arkaplan_log += "#nfc#giris#" + uid + "#\n";
    }
}