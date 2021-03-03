#include <iostream>
#include <string>
#include <sstream>
#include <ostream>

struct Time {
    uint8_t ss;
    uint8_t mm;
    uint8_t hh;

    Time() = default;
    Time(const Time &time) {
        *this = time;
    }
    Time(uint8_t hh, uint8_t mm, uint8_t ss) {
        this->hh = hh;
        this->mm = mm;
        this->ss = ss;
    }

    friend std::ostream& operator<<(std::ostream&, const Time&);
};

class Bill {
    std::string family = ""; // �������
    std::string number; // ����� ���.
    double rate;        // �����
    double discount;    // ������
    Time time1;         // ����� ���.
    Time time2;         // ����� ���.
    double result;      // ����� � ������

    Time countingTime() { //---------------------------- ������� ������� �������
        Time time;
        if (time1.hh > time2.hh) time.hh = (time2.hh + 24) - time1.hh;  // ���� � ��� ���. ����� (������: 01:00:00) ������
        else time.hh = time2.hh - time1.hh;                             // ���. ������� (������: 23:00:00), �� ����� �
                                                                        // ���. ������� ��������� 24 (1+24=25) � �������
                                                                        // (25-23=2). ������ ������� ������� �� �������.
                                                                        // ����� � ��� ���. ����� (������: 23:00:00), �
                                                                        // ���. ������� (������: 01:00:00), �� ������
                                                                        // �������� (23-1=22).

        if (time1.mm > time2.mm) time.mm = (time2.mm + 60) - time1.mm;  // ����������� ����� � �����. ������ ������ ������.
        else time.mm = time2.mm - time1.mm;                             // ���. ����� (������: 00:30:00) ���. �����
                                                                        // (������: 23:50:00), ������ (30+60=90 -> 90-50=40)

        if (time1.ss > time2.ss) time.ss = (time2.ss + 60) - time1.ss;  // ���. ����� (������: 00:00:10) ���. �����
        else time.ss = time2.ss - time1.ss;                             // (������: 23:00:40), ������ (10+60=70 -> 70-40=30)

        return time;
    }
    double countingPartyPrice() { //-------------------- ������� �����
        // std::cout << "countingPartyPrice()\n";
        return trasformTimeToMin() * rate;
    }
    double countingDiscountFromPrice() { //------------- ������� ������
        // std::cout << "countingDiscountFromPrice()\n";
        return discount / 100.0 * countingPartyPrice();
    }
    double countingDiscountedPrice() { //--------------- ������� ����� � ������ ������
        // std::cout << "countingDiscountedPrice()\n";
        return countingPartyPrice() - countingDiscountFromPrice();
    }
    double trasformTimeToMin() { //--------------------- ��������� ���. ����� � ������
        // std::cout << "trasformTimeToMin()\n";
        Time time;
        time = countingTime();
        time.hh *= 60;
        time.ss /= 60;
        return time.hh + time.mm + time.ss;
    }
    std::string toStrTime(Time time) const noexcept { // ����������� ����� � HH:MM:SS
        std::stringstream ss;
        if (time.hh < 10) ss << "0" << +time.hh << ":";
        else ss << +time.hh << ":";

        if (time.mm < 10) ss << "0" << +time.mm << ":";
        else ss << +time.hh << ":";

        if (time.ss < 10) ss << "0" << +time.ss;
        else ss << +time.hh;
        
        return ss.str();
    }
public:
    // ������������
    Bill() = default;
    Bill(const Bill &bill) {
        *this = bill;
    }
    Bill(std::string, std::string, double, double, Time, Time);

    // Input's
    std::string inputString() const noexcept;   // ������ ������
    Time inputTime();                           // ������ ��������� Time (time1 or time2)
    double inputDouble() noexcept;              // ������ float
    uint8_t inputInt8() noexcept;               // ������ ���������� ����� (0 ... 255)
    uint16_t inputInt16() noexcept;             // ������ ���������� ����� (0 ... 65535)

    // ���������
    void Read();    // ���� ������ ��� ������ ���������
    void Display(); // ����� ����������� ���������� �� ������ ������� ������

    // ������
    void setFamily(std::string) noexcept;   // ������ ������� �������
    void setNumber(std::string) noexcept;   // ������ ������� ����� 
    void setRate(double);                   // ������ ������� �����
    void setDiscount(double);               // ������ ������� ������
    void setTime1(Time);                    // ������ ���. �����
    void setTime2(Time);                    // ������ ���. �����

    // ������
    std::string getFamily() {return family;}            // ���������� ������� �������
    std::string getNumber() {return number;}            // ���������� ������� �����
    double getRate() {return rate;}                     // ���������� ������� �����
    double getDiscount() {return discount;}             // ���������� ������� ������
    std::string getTime1() {return toStrTime(time1);}   // ���������� ������� ���. �����
    std::string getTime2() {return toStrTime(time2);}   // ���������� ������� ���. �����
    double getResult() {                                // ���������� ������� ����� (+������� �)
        //result = countingPartyPrice();
        //result = countingDiscountFromPrice();
        result = countingDiscountedPrice();
        return result;
   }
};