#include "Money.h"

Money::Money(const Money &var2) {
    *this = var2;
}

Money::Money(const std::string &number)
{
    size_t search = number.find(',');
    if (search == std::string::npos) {
        *this = Money(stoll(number) * 100);
    }
    else {
        if (number.front() == ',' || number.back() == ',') {
            throw std::invalid_argument("Invalid money argument");
        }

        std::vector<std::string> summa = split(number, ',');
        *this = Money(stol(summa[0]) * 100 + stol(summa[1]));
    }
}

explicit Money::Money(const unsigned long long &coin) {
    convertFromCoin(coin);
}

explicit Money::Money(unsigned long long rub, unsigned char coin) {
    this->rub = rub;
    this->coin = coin;
    fieldValidation();
}

unsigned long long Money::toCoin() const noexcept {
    return coin + rub * CoinMod;
}

void Money::fieldValidation() noexcept {
    // Перевожу все в пенсы и потом разбиваю по категориям
    convertFromCoin(toCoin());
}

void Money::convertFromCoin(const unsigned long long &fCoin) noexcept {
    coin = fCoin % CoinMod;
    rub = fCoin / CoinMod;
}

std::vector<std::string> Money::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

void Money::debug() const noexcept {
    std::cout << rub << "," << +coin << "\n";
    std::cout << "Рубли -> " << rub << "\n";
    std::cout << "Копейки -> " << +coin << "\n";
}

Money Money::operator+=(const Money &var2) {
    *this = *this + var2;
    return *this;
}

Money Money::operator-=(const Money &var2) {
    *this = *this - var2;
    return *this;
}

bool operator<(const Money &var1, const Money &var2) {
    return var1.toCoin() < var2.toCoin();
}

bool operator>(const Money &var1, const Money &var2) {
    return !(var1 <= var2);
}

bool operator<=(const Money &var1, const Money &var2) {
    return (var1 < var2) || (var1 == var2);
}

bool operator>=(const Money &var1, const Money &var2) {
    return (var1 > var2) || (var1 == var2);
}

bool operator==(const Money &var1, const Money &var2) {
    return var1.toCoin() == var2.toCoin();
}

bool operator!=(const Money &var1, const Money &var2) {
    return !(var1 == var2);
}

Money operator+(const Money &var1, const Money &var2) {
    return Money(var1.toCoin() + var2.toCoin());
}

Money operator-(const Money &var1, const Money &var2) {
    // Порой банк снимает деньги, оставляя в минусе...
    // Например, оплата карты за обслуживание раз в год
    return Money(var1.toCoin() - var2.toCoin());
}

double operator/(const Money &var1, const Money &var2) {
    if (var2.toCoin() == 0) {
        throw std::invalid_argument("Деление на 0");
    }
    return static_cast<double>(var1.toCoin() / var2.toCoin());
}

Money operator/(const Money &var1, double coef) {
    if (coef == 0) {
        throw std::invalid_argument("Деление на 0");
    }
    return Money(var1.toCoin() / coef);
}

Money operator*(const Money &var1, double coef) {
    return Money(var1.toCoin() * coef);
}

std::ostream &operator<<(std::ostream &strm, const Money &var) {
    return strm << var.rub << "," << +var.coin << " рублей";
}

std::istream &operator>>(std::istream &strm, Money &var) {
    std::string in;
    strm >> in;
    var = Money(in);
    return strm;
}