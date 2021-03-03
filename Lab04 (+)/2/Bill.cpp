#include "Bill.h"

Bill::Bill(std::string family, std::string number, double rate, double discount, Time time1, Time time2) {
    this->family = family;
    this->number = number;
    this->rate = rate;
    this->discount = discount;
    this->time1 = time1;
    this->time2 = time2;
}

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

Time Bill::inputTime() {
    Time time;

    std::cout << "Укажите кол-во часов: ";
    time.hh = inputInt8();
    if (time.hh < 0 || time.hh > 23) throw ("Кол-во часов не может меньше 0 и больше 23!");
    std::cout << "Укажите кол-во минут: ";
    time.mm  = inputInt8();
    if (time.mm < 0 || time.mm > 59) throw std::invalid_argument("Кол-во минут не может меньше 0 и больше 59!");
    std::cout << "Укажите кол-во секунд: ";
    time.ss = inputInt8();
    if (time.ss < 0 || time.ss > 59) throw std::invalid_argument("Кол-во секунд не может меньше 0 и больше 59!");

    return time;
}

double Bill::inputDouble() noexcept {
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

uint16_t Bill::inputInt16() noexcept {
    uint16_t number = 0;
    do {
        if (std::cin.fail()) { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<uint16_t>::max() - 1, '\n'); 
        }
        std::cin >> number;
    } while (std::cin.fail());
    return number;
}

uint8_t Bill::inputInt8() noexcept{
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

void Bill::Read() {
    std::cout << "Введите фамилию: \n";
    setFamily(inputString());

    std::cout << "\nВведите номер телефона: \n";
    setNumber(inputString());

    std::cout << "\nВведите тариф за минуту разговора: \n";
    setRate(inputDouble());

    std::cout << "\nВведите время начала разговора: \n";
    setTime1(inputTime());

    std::cout << "\nВведите время окончания разговора: \n";
    setTime2(inputTime());

    std::cout << "\nВведите скидку: \n";
    setDiscount(inputDouble());
}

void Bill::Display() {
    std::cout << "Фамилия плательщика: " << family << "\n";
    std::cout << "Номер телефона: " << number << "\n";
    std::cout << "Тариф за минуту разговора: " << rate << "\n";
    std::cout << "Скидка (в процентах): " << discount << "%\n";
    std::cout << "Время начала разговора: " << getTime1() << "\n";
    std::cout << "Время окончания разговора: " << getTime2() << "\n";
    std::cout << "Сумма к оплате с учётом скидки: " << getResult() << " рублей \n";
}

void Bill::setFamily(std::string family) noexcept {
    this->family = family;
}

void Bill::setNumber(std::string number) noexcept {
    this->number = number;
}

void Bill::setRate(double rate) {
    if (rate < 0 || rate > 10) throw std::invalid_argument("Тариф за минуту не может быть меньше 0 и превышать 10!");
    this->rate = rate;
}

void Bill::setDiscount(double discount) {
    if (discount < 1 || discount > 100) throw std::invalid_argument("Скидка не может быть меньше 1% и превышать 100%");
    this->discount = discount;
}

void Bill::setTime1(Time time) {
    this->time1 = time;
}   

void Bill::setTime2(Time time) {
    this->time2 = time;
}

std::ostream &operator<<(std::ostream &out, const Time &time) {
    out << +time.hh << ":" << +time.mm << ":" << +time.ss;
    return out;
}