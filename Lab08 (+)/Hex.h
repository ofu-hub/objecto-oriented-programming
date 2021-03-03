#ifndef HEX_H
#define HEX_H

#include "Array.h"

class Hex : public Array
{
    Hex& toAdditionalCode(size_type _n);
public:
    static constexpr uint8_t num_sys = 16;

    void verifyHexFold(const Array &arr) const;

    Hex() = default;
    Hex(size_type n, value_type t = 0) : Array(n, t) { verifyHexFold(*this); }
    Hex(const std::initializer_list<value_type> &t) : Array(t) { verifyHexFold(*this); }
    Hex(const std::string &str) : Array(str) { verifyHexFold(*this); }

    Hex& operator+=(const Hex &var2);
    Hex& operator-=(const Hex &var2);
    Hex& operator*=(const Hex &var2);
    Hex& operator/=(const Hex &var2);

    friend Hex operator+(const Hex &var1, const Hex &var2);
    friend Hex operator-(const Hex &var1, const Hex &var2);
    friend Hex operator*(const Hex &var1, const Hex &var2);
    friend Hex operator/(const Hex &var1, const Hex &var2);

    class not_Hexfold_exception {}; // Числа не пятиричные
    class left_is_less_than_right_when_subtracted {}; // Левый операд меньше правого во время вычитания
    class zero_devided_exception {}; // Деление на ноль
};

#endif //HEX_H
