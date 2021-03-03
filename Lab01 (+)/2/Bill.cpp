#include "Bill.h"
#include <limits>

Bill::Bill() {
    family = "";
    number = "";
    rate = 0;
    startTime = 0;
    endTime = 0;
    discount = 0;
    price = getPartyPrice();
}

Bill::Bill(std::string family, std::string number, double rate, int startTime, int endTime, double discount) {
    this->family = family;
    this->number = number;
    this->rate = rate;
    this->startTime = startTime;
    this->endTime = endTime;
    this->discount = discount;
    this->price = getPartyPrice();
}

Bill::Bill(const Bill &bill)
{
    *this = bill;
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
    std::cout << "������� �����������: " << family << "\n";
    std::cout << "����� ��������: " << number << "\n";
    std::cout << "����� �� ������ ���������: " << rate << "\n";
    std::cout << "������ (� ���������): " << discount << "\n";
    std::cout << "����� ������ ���������: " << startTime << "\n";
    std::cout << "����� ��������� ���������: " << endTime << "\n";
    std::cout << "����� � ������: " << price << " ������ \n";
}

void Bill::Read() {
    std::cout << "������� �������: \n";
    setFamily(inputString());

    std::cout << "\n������� ����� ��������: \n";
    setNumber(inputString());

    std::cout << "\n������� ����� �� ������ ���������: \n";
    setRate(inputDouble());

    std::cout << "\n������� ����� ������ ���������: \n";
    setStartTime(inputInt());

    std::cout << "\n������� ����� ��������� ���������: \n";
    setEndTime(inputInt());

    std::cout << "\n������� ������: \n";
    setDiscount(inputDouble());
}

// ������
void Bill::setFamily(std::string family) noexcept {
    this->family = family;
}

void Bill::setNumber(std::string number) noexcept {
    this->number = number;
}

void Bill::setStartTime(int startTime) {
    if (startTime < 1) {
        throw std::invalid_argument("������ ������� ��������� �� ����� ���� ������������� ��� ������ ����!");
    }
    this->startTime = startTime;
}

void Bill::setEndTime(int endTime) {
    if (endTime < startTime) {
        throw std::invalid_argument("����� ������� ��������� �� ����� ���� ������ ������ ������� ���������!");
    }
    this->endTime = endTime;
}

void Bill::setRate(double discount) {
    if (discount < 0 || discount > 100) {
        throw std::invalid_argument("����� ������ ���� � ��������� �� 0 �� 100 ������������!");
    }
    this->rate = rate;
}

void Bill::setDiscount(double discount) {
    if (discount < 0 || discount > 100) {
        throw std::invalid_argument("������ ������ ���� � ��������� �� 0 �� 100 ������������!");
    }
    this->discount = discount;
}

// ������� ������� ����� ���������
long Bill::getPartyPrice() const noexcept {
    return (endTime - startTime) * rate;
}

double Bill::getDiscountFromPrice() const noexcept {
    return discount / 100 * getPartyPrice();
}

double Bill::getDiscountedPrice() const noexcept {
    return getPartyPrice() - getDiscountFromPrice();
}

// ���������� ������
int Bill::compareRates(const Bill &bill) const noexcept {
    int sign = 0;
    if (this->rate < bill.rate) sign = -1;
    else if (this->rate > bill.rate) sign = 1;
    return sign;
}