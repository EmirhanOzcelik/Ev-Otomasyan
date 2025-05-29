#include "main.h"
#include <avr/pgmspace.h>

// Allah'ın 99 ismi (Türkçe karakterler olmadan, 14 karakteri aşmayan)
const char esma_0[] PROGMEM = "Er-Rahman";      // 1
const char esma_1[] PROGMEM = "Er-Rahim";       // 2
const char esma_2[] PROGMEM = "El-Melik";       // 3
const char esma_3[] PROGMEM = "El-Kuddus";      // 4
const char esma_4[] PROGMEM = "Es-Salam";       // 5
const char esma_5[] PROGMEM = "El-Mumin";       // 6
const char esma_6[] PROGMEM = "El-Muhaymin";    // 7
const char esma_7[] PROGMEM = "El-Aziz";        // 8
const char esma_8[] PROGMEM = "El-Cebbar";      // 9
const char esma_9[] PROGMEM = "El-Mutekebbir";  // 10
const char esma_10[] PROGMEM = "El-Halik";      // 11
const char esma_11[] PROGMEM = "El-Bari";       // 12
const char esma_12[] PROGMEM = "El-Musawwir";   // 13
const char esma_13[] PROGMEM = "El-Ghaffar";    // 14
const char esma_14[] PROGMEM = "El-Kahhar";     // 15
const char esma_15[] PROGMEM = "El-Wahhab";     // 16
const char esma_16[] PROGMEM = "Er-Razzaq";     // 17
const char esma_17[] PROGMEM = "El-Fattah";     // 18
const char esma_18[] PROGMEM = "El-Alim";       // 19
const char esma_19[] PROGMEM = "El-Qabid";      // 20
const char esma_20[] PROGMEM = "El-Basit";      // 21
const char esma_21[] PROGMEM = "El-Hafiz";      // 22
const char esma_22[] PROGMEM = "El-Muqit";      // 23
const char esma_23[] PROGMEM = "El-Hasib";      // 24
const char esma_24[] PROGMEM = "El-Jalil";      // 25
const char esma_25[] PROGMEM = "El-Karim";      // 26
const char esma_26[] PROGMEM = "Er-Raqib";      // 27
const char esma_27[] PROGMEM = "El-Mujib";      // 28
const char esma_28[] PROGMEM = "El-Wasi";       // 29
const char esma_29[] PROGMEM = "El-Hakim";      // 30
const char esma_30[] PROGMEM = "El-Wadud";      // 31
const char esma_31[] PROGMEM = "El-Majid";      // 32
const char esma_32[] PROGMEM = "El-Ba'ith";     // 33
const char esma_33[] PROGMEM = "Ash-Shahid";    // 34
const char esma_34[] PROGMEM = "Al-Haqq";       // 35
const char esma_35[] PROGMEM = "Al-Wakil";      // 36
const char esma_36[] PROGMEM = "Al-Qawi";       // 37
const char esma_37[] PROGMEM = "Al-Matin";      // 38
const char esma_38[] PROGMEM = "Al-Wali";       // 39
const char esma_39[] PROGMEM = "Al-Hamid";      // 40
const char esma_40[] PROGMEM = "Al-Muhsi";      // 41
const char esma_41[] PROGMEM = "Al-Mubdi";      // 42
const char esma_42[] PROGMEM = "Al-Mu'id";      // 43
const char esma_43[] PROGMEM = "Al-Muhyi";      // 44
const char esma_44[] PROGMEM = "Al-Mumit";      // 45
const char esma_45[] PROGMEM = "Al-Hayy";       // 46
const char esma_46[] PROGMEM = "Al-Qayyum";     // 47
const char esma_47[] PROGMEM = "Al-Wajid";      // 48
const char esma_48[] PROGMEM = "Al-Majid";      // 49
const char esma_49[] PROGMEM = "Al-Wahid";      // 50
const char esma_50[] PROGMEM = "Al-Ahad";       // 51
const char esma_51[] PROGMEM = "As-Samad";      // 52
const char esma_52[] PROGMEM = "Al-Qadir";      // 53
const char esma_53[] PROGMEM = "Al-Muqtadir";   // 54
const char esma_54[] PROGMEM = "Al-Muqaddim";   // 55
const char esma_55[] PROGMEM = "Al-Mu'akhkhir"; // 56
const char esma_56[] PROGMEM = "Al-Awwal";      // 57
const char esma_57[] PROGMEM = "Al-Akhir";      // 58
const char esma_58[] PROGMEM = "Az-Zahir";      // 59
const char esma_59[] PROGMEM = "Al-Batin";      // 60
const char esma_60[] PROGMEM = "Al-Waliyy";     // 61
const char esma_61[] PROGMEM = "Al-Muta'ali";   // 62
const char esma_62[] PROGMEM = "Al-Barr";       // 63
const char esma_63[] PROGMEM = "At-Tawwab";     // 64
const char esma_64[] PROGMEM = "Al-Muntaqim";   // 65
const char esma_65[] PROGMEM = "Al-'Afuww";     // 66
const char esma_66[] PROGMEM = "Ar-Ra'uf";      // 67
const char esma_67[] PROGMEM = "Malik al-Mulk"; // 68
const char esma_68[] PROGMEM = "Dhul-Jalali";   // 69
const char esma_69[] PROGMEM = "Al-Muqsit";     // 70
const char esma_70[] PROGMEM = "Al-Jami'";      // 71
const char esma_71[] PROGMEM = "Al-Ghani";      // 72
const char esma_72[] PROGMEM = "Al-Mughni";     // 73
const char esma_73[] PROGMEM = "Al-Mani'";      // 74
const char esma_74[] PROGMEM = "Ad-Darr";       // 75
const char esma_75[] PROGMEM = "An-Nafi'";      // 76
const char esma_76[] PROGMEM = "An-Nur";        // 77
const char esma_77[] PROGMEM = "Al-Hadi";       // 78
const char esma_78[] PROGMEM = "Al-Badi'";      // 79
const char esma_79[] PROGMEM = "Al-Baqi";       // 80
const char esma_80[] PROGMEM = "Al-Warith";     // 81
const char esma_81[] PROGMEM = "Ar-Rashid";     // 82
const char esma_82[] PROGMEM = "As-Sabur";      // 83
const char esma_83[] PROGMEM = "Al-Muhsi";      // 84
const char esma_84[] PROGMEM = "Al-Latif";      // 85
const char esma_85[] PROGMEM = "Al-Khabir";     // 86
const char esma_86[] PROGMEM = "Al-Ghafur";     // 87
const char esma_87[] PROGMEM = "Ar-Rauf";       // 88
const char esma_88[] PROGMEM = "Al-Muntaqim";   // 89
const char esma_89[] PROGMEM = "Al-Wahid";      // 90
const char esma_90[] PROGMEM = "Al-Ahad";       // 91
const char esma_91[] PROGMEM = "Al-Khabir";     // 92
const char esma_92[] PROGMEM = "Al-Jabbar";     // 93
const char esma_93[] PROGMEM = "Al-Muntaqim";   // 94
const char esma_94[] PROGMEM = "Al-Wahhab";     // 95
const char esma_95[] PROGMEM = "Al-Malik";      // 96
const char esma_96[] PROGMEM = "Al-Aziz";       // 97
const char esma_97[] PROGMEM = "Al-Jabbar";     // 98
const char esma_98[] PROGMEM = "Al-Mutakabbir"; // 99

const char *const esma_listesi[] PROGMEM = {
    esma_0, esma_1, esma_2, esma_3, esma_4,
    esma_5, esma_6, esma_7, esma_8, esma_9,
    esma_10, esma_11, esma_12, esma_13, esma_14,
    esma_15, esma_16, esma_17, esma_18, esma_19,
    esma_20, esma_21, esma_22, esma_23, esma_24,
    esma_25, esma_26, esma_27, esma_28, esma_29,
    esma_30, esma_31, esma_32, esma_33, esma_34,
    esma_35, esma_36, esma_37, esma_38, esma_39,
    esma_40, esma_41, esma_42, esma_43, esma_44,
    esma_45, esma_46, esma_47, esma_48, esma_49,
    esma_50, esma_51, esma_52, esma_53, esma_54,
    esma_55, esma_56, esma_57, esma_58, esma_59,
    esma_60, esma_61, esma_62, esma_63, esma_64,
    esma_65, esma_66, esma_67, esma_68, esma_69,
    esma_70, esma_71, esma_72, esma_73, esma_74,
    esma_75, esma_76, esma_77, esma_78, esma_79,
    esma_80, esma_81, esma_82, esma_83, esma_84,
    esma_85, esma_86, esma_87, esma_88, esma_89,
    esma_90, esma_91, esma_92, esma_93, esma_94,
    esma_95, esma_96, esma_97, esma_98};

void random_esmaulHusna()
{
    uint8_t random_index = random(0, 99);                        
    strcpy_P(uygulama.esmaulHusnA, (char*)pgm_read_word(&(esma_listesi[random_index]))); 
}