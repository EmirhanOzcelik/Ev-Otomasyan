#pragma once

#define __AKILLI_ATOLYE_EPR_IMZA 48      // yazılımsal doğrulama için kullanılacak imza (0-255)
#define __AKILLI_ATOLYE_EPR_IMZA_ADR 172 // imza adresi
#define adres_degistirici 0              // 200 - 400 - 600 ile yeni adreslere geçilebilir (her 10k okunmadan sonra değişmek için(boşiş))

// Zaman verileri
#define _EprAdr_sn (adres_degistirici + 0)
#define _EprAdr_dk (adres_degistirici + 1)
#define _EprAdr_saat (adres_degistirici + 2)
#define _EprAdr_gun (adres_degistirici + 3)
#define _EprAdr_ay (adres_degistirici + 4)
#define _EprAdr_yil (adres_degistirici + 5)
#define _EprAdr_hafta (adres_degistirici + 7)
//