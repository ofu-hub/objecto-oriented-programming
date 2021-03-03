#include <iostream>
#include <sstream>
#include <string>
#include <climits>

// #pragma pack(push,1)
class Bill {
private:
    // ����
    std::string family;     // �������
    std::string number;
    double rate;
    int startTime;
    int endTime;
    double price;
    double discount;        // ���������� � ���������
    // Input
    std::string inputString() const noexcept;
    int inputInt() const noexcept;
    double inputDouble() const noexcept;

public:
    Bill();
    Bill(std::string family, std::string number, double rate, int startTime, int endTime, double discount);
    Bill(const Bill &bill);

    // ���� � �����
    void Display() const noexcept;
    void Read();

    // ������
    void setFamily(std::string family) noexcept;
    void setNumber(std::string number) noexcept;
    void setRate(double rate);
    void setStartTime(int startTime);
    void setEndTime(int endTime);
    void setDiscount(double discount);
    
    // ������
    std::string getFamily() const noexcept { return family; };
    std::string getNumber() const noexcept { return number; };
    int getRate() const noexcept { return rate; };
    int getStartTime() const noexcept { return startTime; };
    int getEndTime() const noexcept { return endTime; };
    int getDiscount() const noexcept { return discount; };

    // ������� ������� ����� ���������
    long getPartyPrice() const noexcept;
    double getDiscountFromPrice() const noexcept;
    double getDiscountedPrice() const noexcept;

    // �������� ������
    int compareRates(const Bill &bill) const noexcept;

    // to_String
    std::string toString() const noexcept {
        std::stringstream str;
        str << "family: " << family << ", number: " << number << ", rate: " << rate
            << ", startTime: " << startTime << ", endTime: " << endTime
            << ", price: " << price << ", discount: " << discount << ". \n";
        return str.str();
    }
};
// #pragma pack(pop)