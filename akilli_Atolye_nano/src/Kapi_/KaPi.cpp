#include "main.h"
#include "Servo.h"
Servo motor;

byte sureklilik_engel = 0;  // motorun sürekli yazma fonksiyonu çagırmasını engeller
byte sureklilik_engel2 = 0; // motorun sürekli yazma fonksiyonu çagırmasını engeller
uint16_t icr = 0;
class __sistem sistem;

void __sistem::kur()
{
    pinMode(kapi_sens2_pin, INPUT_PULLUP);
    pinMode(kapi_buton_pin, INPUT_PULLUP);
    motor.attach(motor_pin);
    motor.write(motor_kapali_konum);
}

void __sistem::sensor_oku()
{
    potansiyometre = analogRead(A5);       // kalibre_analogOku(kapi_sens1_pin, vcc_olc());
    sensor = !digitalRead(kapi_sens2_pin); // kapı manyetık sensor
    buton = !digitalRead(kapi_buton_pin);  // kapıyı içerden açmak için buton

    if (((keypad.sifre > 0 || buton) && !kapi_acik)) // kapı kapalı ve giriş hakkı var
    {
        if (sureklilik_engel2 < 1)
        {
            Serial.println("kapi acildi");
            sureklilik_engel2++;
            kapi_acik = true;
            motor.write(motor_acik_konum);
            millis_timer.delay(motor_hareket_bekleme_ms);
            sureklilik_engel = 0;
        }
    }
    else if (potansiyometre >= kapi_kapali_konum - pot_okuma_tolerans && !buton) // kapı açık ve açı 0-10 derece
    {
        if (sensor) // sensor yuvada
        {
            millis_timer.delay(motor_kapanis_bekleme_ms);
            sensor = !digitalRead(kapi_sens2_pin); // kapı manyetık sensor
            if (sensor)                            // sensor belirli ms sonra da yuvada mı?
            {
                if (sureklilik_engel < 1)
                {
                    sureklilik_engel2 = 0;
                    Serial.println("kapi kapandi");
                    keypad.sifre = 0;
                    kapi_acik = false;
                    sureklilik_engel++;
                    motor.write(kapi_kapali_konum);
                    millis_timer.delay(motor_hareket_bekleme_ms);
                }
                return;
            }
        }
        else if (sureklilik_engel2 < 1)
        {
            Serial.println("kapi acildi");
            sureklilik_engel2++;
            kapi_acik = true;
            motor.write(motor_acik_konum);
            millis_timer.delay(motor_hareket_bekleme_ms);
            sureklilik_engel = 0;
        }
    }
}
