#pragma once
#include "Arduino.h"
#include <SPI.h>
#include <MFRC522.h>
// MFRC522 RFID modulu NodeMCU (ESP8266) baglantilari:
// SDA  -> D2   (GPIO4)   // SS (Slave Select)
// SCK  -> D5   (GPIO14)  // SPI Clock
// MOSI -> D7   (GPIO13)  // SPI veri gonderme
// MISO -> D6   (GPIO12)  // SPI veri alma
// IRQ  -> Baglanmiyor    // Gerekli degil
// GND  -> GND            // Toprak
// RST  -> D1   (GPIO5)   // Reset pini
// 3.3V -> 3.3V           // 5V baglama! Modul yanar

class __nfc
{
private:
public:
    bool kayit_izin = false;
    void kur();
    void oku();
    void kart_kaydet();
    void kart_dogrula();
};
extern class __nfc nfc;