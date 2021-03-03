#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <utility>
#include <vector>

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

    class Money {
        enum {
            CoinMod = 100
        };
        
        unsigned long long rub{0};   // �����
        unsigned char coin{0};   // �������

        unsigned long long Money::toCoin() const noexcept {
            return coin + rub * CoinMod;
        }
        void Money::fieldValidation() noexcept {
            // �������� ��� � ����� � ����� �������� �� ����������
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

    public:
        Money() = default;
        Money(const Money &var2) {
            *this = var2;
        }
        Money(const std::string &number)
        {
            size_t search = number.find(',');
            if (search == std::string::npos)
            {
                *this = Money(stoll(number) * 100);
            }
            else
            {
                if (number.front() == ',' || number.back() == ',') {
                    throw std::invalid_argument("Invalid money argument");
                }

                std::vector<std::string> summa = split(number, ',');
                *this = Money(stol(summa[0]) * 100 + stol(summa[1]));
            }
        }
        explicit Money(const unsigned long long &coin) {
            convertFromCoin(coin);
        }
        explicit Money(unsigned long long rub, unsigned char coin) {
            this->rub = rub;
            this->coin = coin;
            fieldValidation();
        }
        void debug() const noexcept {
            std::cout << rub << "," << +coin << "\n";
            std::cout << "����� -> " << rub << "\n";
            std::cout << "������� -> " << +coin << "\n";
        }
        Money operator+=(const Money &var2) {
            *this = *this + var2;
            return *this;
        }
        Money operator-=(const Money &var2) {
            *this = *this - var2;
            return *this;
        }
        friend bool operator<(const Money &var1, const Money &var2) {
            return var1.toCoin() < var2.toCoin();
        }
        friend bool operator>(const Money &var1, const Money &var2) {
            return !(var1 <= var2);
        }
        friend bool operator<=(const Money &var1, const Money &var2) {
            return (var1 < var2) || (var1 == var2);
        }
        friend bool operator>=(const Money &var1, const Money &var2) {
            return (var1 > var2) || (var1 == var2);
        }
        friend bool operator==(const Money &var1, const Money &var2) {
            return var1.toCoin() == var2.toCoin();
        }
        friend bool operator!=(const Money &var1, const Money &var2) {
            return !(var1 == var2);
        }
        friend Money operator+(const Money &var1, const Money &var2) {
            return Money(var1.toCoin() + var2.toCoin());
        }
        friend Money operator-(const Money &var1, const Money &var2) {
            // ����� ���� ������� ������, �������� � ������...
            // ��������, ������ ����� �� ������������ ��� � ���
            return Money(var1.toCoin() - var2.toCoin());
        }
        friend double operator/(const Money &var1, const Money &var2) {
            if (var2.toCoin() == 0) {
                throw std::invalid_argument("������� �� 0");
            }
            return static_cast<double>(var1.toCoin() / var2.toCoin());
        }
        friend Money operator/(const Money &var1, double coef) {
            if (coef == 0) {
                throw std::invalid_argument("������� �� 0");
            }
            return Money(var1.toCoin() / coef);
        }
        friend Money operator*(const Money &var1, double coef) {
            return Money(var1.toCoin() * coef);
        }
        friend std::ostream &operator<<(std::ostream &strm, const Money &var) {
            return strm << var.rub << "," << +var.coin << " ������";
        }
        friend std::istream &operator>>(std::istream &strm, Money &var) {
            std::string in;
            strm >> in;
            var = Money(in);
            return strm;
        }
    };
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