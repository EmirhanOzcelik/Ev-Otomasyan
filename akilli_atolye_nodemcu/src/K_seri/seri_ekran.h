#pragma once

#include <Arduino.h>

extern String arkaplan_log;

extern void yaz(const __FlashStringHelper *k);
extern void yaz(String k);
extern void yaz(const char *k);
extern void yaz(char k);
extern void yaz(int k);
extern void yaz(unsigned int k);
extern void yaz(long k);
extern void yaz(unsigned long k);
extern void yaz(float k, int precision = 2);
extern void yaz(double k, int precision = 2);

