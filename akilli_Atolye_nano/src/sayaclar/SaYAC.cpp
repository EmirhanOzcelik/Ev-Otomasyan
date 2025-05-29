#include "main.h"
#include "SaYAC.h"
#include "Arduino.h"
struct __sayac sayac;

void __sayac::azalt(int16_t &syc, int16_t min)
{
    if (syc > min)
        syc--;
}

void __sayac::arttir(int16_t &syc, int16_t max)
{
    if (syc < max)
        syc++;
}

void __sayac::azalt(uint16_t &syc, uint16_t min)
{
    if (syc > min)
        syc--;
}

void __sayac::arttir(uint16_t &syc, uint16_t max)
{
    if (syc < max)
        syc++;
}
void __sayac::azalt(uint8_t &syc, uint8_t min)
{
    if (syc > min)
        syc--;
}

void __sayac::arttir(uint8_t &syc, uint8_t max)
{
    if (syc < max)
        syc++;
}