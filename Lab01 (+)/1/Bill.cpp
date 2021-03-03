#include "Bill.h"

std::string Bill::inputString() const noexcept {
    std::string str = "";
    do {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
        }
        getline(std::cin, str);
    } while (std::cin.fail());
    return str;
}

int Bill::inputInt() const noexcept {
    int number = 0;
    do {
        if (std::cin.fail()) { 
            std::cin.clear(); 
            std::cin.ignore(INT32_MAX, '\n'); 
        }
        std::cin >> number;
    } while (std::cin.fail());
    return number;
}

double Bill::inputDouble() const noexcept {
    double number = 0;
    do {
        if (std::cin.fail()) { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<uint8_t>::max() - 1, '\n'); 
        }
        std::cin >> number;
    } while (std::cin.fail());
    return number;
}

void Bill::Display() const noexcept {
    std::cout << "Фамилия плательщика: " << family << "\n";
    std::cout << "Номер телефона: " << number << "\n";
    std::cout << "Тариф за минуту разговора: " << rate << "\n";
    std::cout << "Скидка (в процентах): " << discount << "\n";
    std::cout << "Время начала разговора: " << startTime << "\n";
    std::cout << "Время окончания разговора: " << endTime << "\n";
    std::cout << "Сумма к оплате: " << price << " рублей \n";
}

void Bill::Read() {
    std::cout << "Введите фамилию: \n";
    setFamily(inputString());

    std::cout << "\nВведите номер телефона: \n";
    setNumber(inputString());

    std::cout << "\nВведите тариф за минуту разговора: \n";
    setRate(inputDouble());

    std::cout << "\nВведите время начала разговора: \n";
    setStartTime(inputInt());

    std::cout << "\nВведите время окончания разговора: \n";
    setEndTime(inputInt());

    std::cout << "\nВведите скидку: \n";
    setDiscount(inputDouble());
}

// Сетеры
void Bill::setFamily(std::string family) noexcept {
    this->family = family;
}

void Bill::setNumber(std::string number) noexcept {
    this->number = number;
}

void Bill::setStartTime(int startTime) {
    if (startTime < 1) {
        throw std::invalid_argument("Начало времени разговора не может быть отрицательным или равным нулю!");
    }
    this->startTime = startTime;
}

void Bill::setEndTime(int endTime) {
    if (endTime < startTime) {
        throw std::invalid_argument("Конец времени разговора не может быть меньше начала времени разговора!");
    }
    this->endTime = endTime;
}

void Bill::setRate(double rate) {
    if (rate < 0 || rate > 100) {
        throw std::invalid_argument("Тариф должен быть в диапазоне от 0 до 100 включительно!");
    }
    this->rate = rate;
}

void Bill::setDiscount(double discount) {
    if (discount < 0 || discount > 100) {
        throw std::invalid_argument("Скидка должна быть в диапазоне от 0 до 100 включительно!");
    }
    this->discount = discount;
}

// Считаем сколько нужно заплатить
long Bill::getPartyPrice() const noexcept {
    return (endTime - startTime) * rate;
}

double Bill::getDiscountFromPrice() const noexcept {
    return discount / 100 * getPartyPrice();
}

double Bill::getDiscountedPrice() const noexcept {
    return getPartyPrice() - getDiscountFromPrice();
}

// Сравниваем тарифы
int Bill::compareRates(const Bill &bill) const noexcept {
    int sign = 0;
    if (this->rate < bill.rate) sign = -1;
    else if (this->rate > bill.rate) sign = 1;
    return sign;
}