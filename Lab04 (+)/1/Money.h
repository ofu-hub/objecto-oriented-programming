#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "Bill.h"

class Money {
    enum {
        CoinMod = 100
    };
    
    unsigned long long rub{0};   // Рубли
    unsigned char coin{0};   // Копейки

    unsigned long long toCoin() const noexcept;
    void fieldValidation() noexcept;
    void convertFromCoin(const unsigned long long &fCoin) noexcept;
    static std::vector<std::string> split(const std::string &s, char delim);

public:
    Money() = default;
    Money(const Money &var2);
    Money(const std::string &number);
    explicit Money(const unsigned long long &coin);
    explicit Money(unsigned long long rub, unsigned char coin);

    class MoneyException {};

    void debug() const noexcept;

    Money operator+=(const Money &var2);
    Money operator-=(const Money &var2);

    friend bool operator<(const Money &var1, const Money &var2);
    friend bool operator>(const Money &var1, const Money &var2);
    friend bool operator<=(const Money &var1, const Money &var2);
    friend bool operator>=(const Money &var1, const Money &var2);
    friend bool operator==(const Money &var1, const Money &var2);
    friend bool operator!=(const Money &var1, const Money &var2);

    friend Money operator+(const Money &var1, const Money &var2);
    friend Money operator-(const Money &var1, const Money &var2);
    friend double operator/(const Money &var1, const Money &var2);
    friend Money operator/(const Money &var1, double coef);
    friend Money operator*(const Money &var1, double coef);
    friend std::ostream& operator<<(std::ostream &strm, const Money &var);
    friend std::istream& operator>>(std::istream &strm, Money &var);
};