#pragma once

#define kapi_sens1_pin A5
#define vcc_olcum_pin A7
#define kapi_sens2_pin 6
#define kapi_buton_pin 9

#define kapi_kapali_konum 770
#define pot_okuma_tolerans 50

#define motor_pin 3
#define motor_acik_konum 90          // acık hale gelmek için konum
#define motor_kapali_konum 110       // kapalı hale gelmek için konum
#define motor_hareket_bekleme_ms 10  // temel hareket bekleme süresi
#define motor_kapanis_bekleme_ms 200 // kapanmak için bekleme süresi(metal plaka temas gecikmesi)

class __sistem
{
private:
public:
    float vcc;
    uint8_t pil_deger = 0;
    uint16_t potansiyometre;
    bool sensor;
    bool buton;
    bool kapi_acik;
    void kur();
    void sensor_oku();
    void sifirla();
    void vcc_olc();
    int kalibre_analogOku(int pin, float vcc);
};
extern class __sistem sistem;