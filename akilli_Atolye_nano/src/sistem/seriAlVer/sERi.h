#pragma once

#include "Arduino.h"

/// @brief Maksimum veri parçası (paket) sayısı.
/// @details Gelen veri `ayirac_karakter` ile bölünür. Bu tanım, en fazla kaç parça veri saklanacağını belirtir.
#define SP_MAX_paket 5

/// @brief Her bir parçadaki maksimum karakter sayısı.
/// @details Her veri parçası (paket) bu karakter sayısını aşmamalıdır.
#define SP_MAX_veri 20

/// @brief Başlık karakteri sayısı (opsiyonel kullanım için).
#define port_baslik 1

/**
 * @class __port
 * @brief Seri port üzerinden gelen verileri ayrıştırmak ve düzenli biçimde erişmek için kullanılan sınıf.
 *
 * Bu sınıf, Arduino'nun `Serial` arabiriminden okunan ham veriyi,
 * belirli bir ayıraç karakterine göre parçalara böler ve her parçayı ayrı ayrı erişilebilir hale getirir.
 *
 * Tipik kullanım:
 * @code
 * __port port;
 * port.oku();
 * if (port.islem) {
 *     port.ayikla();
 *     String komut = port.veri(0);
 *     String deger = port.veri(1);
 *     port.temizle();
 * }
 * @endcode
 */
class __port
{
private:
    /// @brief Veriyi bölecek olan karakter (örnek: '#').
    const unsigned char ayirac_karakter = '#';

    /// @brief Serial'den okunan ham veri (buffer).
    char gelen[SP_MAX_paket * SP_MAX_veri];

    /// @brief Ayıraç karakterlerinin veri içindeki konumları.
    /// @details Bu konumlar parçalama işlemi için kullanılır.
    uint8_t ayirac_konumlar[SP_MAX_paket + 1];

    /// @brief Okunan verinin toplam byte sayısı.
    int16_t boyut = 0;

    /// @brief Ayıklanmış veri parçalarının saklandığı dizi.
    char paket_[SP_MAX_paket][SP_MAX_veri];

    /// @brief Son ayıklama işleminden sonra elde edilen geçerli veri parçası sayısı.
    uint8_t parcacik_sayisi_ = 0;

public:
    /// @brief Veri işlenmeye hazır mı?
    /// @details `oku()` çağrısından sonra ayıraç karakteri bulunmuşsa bu değer `true` olur.
    bool islem = false;

    /**
     * @brief Seri port üzerinden gelen veriyi okur.
     *
     * @details `Serial.readBytes()` ile veriyi `gelen` tamponuna okur.
     * Verinin içinde ayıraç karakteri varsa `islem` bayrağı `true` olur.
     *
     * Tipik olarak loop() içinde sürekli çağrılır.
     */
    void oku();

    /**
     * @brief Okunan ham veriyi ayırır ve `paket_` dizisine yerleştirir.
     *
     * @details Her ayıraç karakteri, yeni bir parçanın başladığını ifade eder.
     * Sonuçta her bir parça, `paket_` dizisinde indekslenmiş olarak saklanır.
     * Bu işlem tamamlandığında `paket_boyut()` çağrısı doğru sayıyı döner.
     */
    void ayikla();

    /**
     * @brief `paket_` dizisindeki tüm verileri temizler.
     *
     * @details Her hücreye `'\0'` yazar ve `parcacik_sayisi_` değerini sıfırlar.
     * Yeni bir okuma-ayıklama döngüsüne başlamadan önce çağrılması önerilir.
     */
    void temizle();

    /**
     * @brief Belirli bir veri parçasını (paket) döndürür.
     *
     * @param i Erişmek istenen parça indeksi (0'dan başlar).
     * @return String Veri parçası. Eğer indeks geçersizse boş string döner.
     *
     * @note `ayikla()` fonksiyonu çalıştırılmadan önce çağrılırsa anlamlı sonuç vermez.
     */
    String veri(uint8_t i);

    /**
     * @brief Mevcut geçerli parça (paket) sayısını döndürür.
     *
     * @return int8_t Ayıklanan veri parçası (paket) sayısı.
     *
     * @note Bu değer her `ayikla()` çağrısından sonra güncellenir.
     */
    int8_t paket_boyut();
};

/// @brief Global port nesnesi.
/// @details Kodun diğer bölümlerinde bu nesne doğrudan kullanılabilir.
extern class __port port;
