#include <iostream>
#include <sstream>
#include <string>
#include <climits>

class Bill {
private:
    // Поля
    std::string family;
    std::string number;
    double rate;
    int startTime;
    int endTime;
    double price;
    double discount;        // Измеряется в процентах
    // Input
    std::string inputString() const noexcept;
    int inputInt() const noexcept;
    double inputDouble() const noexcept;

public:
    void Init() {
        family = "";
        number = "";
        rate = 0;
        startTime = 0;
        endTime = 0;
        discount = 0;
    };
    void Init(std::string family, std::string number, double rate, int startTime, int endTime, double discount) {
        setFamily(family);
        setNumber(number);
        setRate(rate);
        setStartTime(startTime);
        setEndTime(endTime);
        setDiscount(discount);
        price = getPartyPrice();
    }
    void Init(const Bill &bill) {
        *this = bill;
    }

    // Ввод и вывод
    void Display() const noexcept;
    void Read();

    // Сетеры
    void setFamily(std::string family) noexcept;
    void setNumber(std::string number) noexcept;
    void setRate(double rate);
    void setStartTime(int startTime);
    void setEndTime(int endTime);
    void setDiscount(double discount);
    
    // Гетеры
    std::string getFamily() const noexcept { return family; };
    std::string getNumber() const noexcept { return number; };
    int getRate() const noexcept { return rate; };
    int getStartTime() const noexcept { return startTime; };
    int getEndTime() const noexcept { return endTime; };
    int getDiscount() const noexcept { return discount; };

    // Считаем время
    int countingTime(int startTime, int endTime) const noexcept;

    // Считаем сколько нужно заплатить
    long getPartyPrice() const noexcept;
    double getDiscountFromPrice() const noexcept;
    double getDiscountedPrice() const noexcept;

    // Сравнить тарифы
    int compareRates(const Bill &bill) const noexcept;

    // to_String
    std::string toString() const noexcept {
        std::stringstream str;
        str << "family: " << family << ", number: " << number << ", rate: " << rate
            << ", startTime: " << startTime << ", endTime: " << endTime
            << ", price: " << price << ", discount:" << discount << ". \n";
        return str.str();
    }
};