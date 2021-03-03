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
    std::string family = ""; // Фамилия
    std::string number; // Номер тел.
    double rate;        // Тариф
    double discount;    // Скидка
    Time time1;         // Время нач.
    Time time2;         // Время кон.
    double result;      // Сумма к оплате

    Time countingTime() { //---------------------------- Считаем разницу времени
        Time time;
        if (time1.hh > time2.hh) time.hh = (time2.hh + 24) - time1.hh;  // Если у нас кон. время (пример: 01:00:00) меньше
        else time.hh = time2.hh - time1.hh;                             // нач. времени (пример: 23:00:00), то нужно к
                                                                        // кон. времени прибавить 24 (1+24=25) и вычесть
                                                                        // (25-23=2). Отсюда получим разницу во времени.
                                                                        // Иначе у нас кон. время (пример: 23:00:00), а
                                                                        // нач. времени (пример: 01:00:00), то просто
                                                                        // вычетаем (23-1=22).

        if (time1.mm > time2.mm) time.mm = (time2.mm + 60) - time1.mm;  // Аналогичная схема и здесь. Просто покажу пример.
        else time.mm = time2.mm - time1.mm;                             // кон. время (пример: 00:30:00) нач. время
                                                                        // (пример: 23:50:00), отсюда (30+60=90 -> 90-50=40)

        if (time1.ss > time2.ss) time.ss = (time2.ss + 60) - time1.ss;  // кон. время (пример: 00:00:10) нач. время
        else time.ss = time2.ss - time1.ss;                             // (пример: 23:00:40), отсюда (10+60=70 -> 70-40=30)

        return time;
    }
    double countingPartyPrice() { //-------------------- Считаем сумму
        // std::cout << "countingPartyPrice()\n";
        return trasformTimeToMin() * rate;
    }
    double countingDiscountFromPrice() { //------------- Считаем скидку
        // std::cout << "countingDiscountFromPrice()\n";
        return discount / 100.0 * countingPartyPrice();
    }
    double countingDiscountedPrice() { //--------------- Считаем сумму с учетом скидки
        // std::cout << "countingDiscountedPrice()\n";
        return countingPartyPrice() - countingDiscountFromPrice();
    }
    double trasformTimeToMin() { //--------------------- Переводим общ. время в минуты
        // std::cout << "trasformTimeToMin()\n";
        Time time;
        time = countingTime();
        time.hh *= 60;
        time.ss /= 60;
        return time.hh + time.mm + time.ss;
    }
    std::string toStrTime(Time time) const noexcept { // Форматируем время в HH:MM:SS
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
    // Конструкторы
    Bill() = default;
    Bill(const Bill &bill) {
        *this = bill;
    }
    Bill(std::string, std::string, double, double, Time, Time);

    // Input's
    std::string inputString() const noexcept;   // Вводим строку
    Time inputTime();                           // Вводим структуру Time (time1 or time2)
    double inputDouble() noexcept;              // Вводим float
    uint8_t inputInt8() noexcept;               // Вводим безнаковое число (0 ... 255)
    uint16_t inputInt16() noexcept;             // Вводим безнаковое число (0 ... 65535)

    // Интерфейс
    void Read();    // Ввод данных для работы программы
    void Display(); // Вывод полученного результата на основе входных данных

    // Сетеры
    void setFamily(std::string) noexcept;   // Меняем атрибут фамилия
    void setNumber(std::string) noexcept;   // Меняем атрибут номер 
    void setRate(double);                   // Меняем атрибут тариф
    void setDiscount(double);               // Меняем атрибут скидка
    void setTime1(Time);                    // Меняем нач. время
    void setTime2(Time);                    // Меняем кон. время

    // Гетеры
    std::string getFamily() {return family;}            // Возвращаем атрибут фамилия
    std::string getNumber() {return number;}            // Возвращаем атрибут номер
    double getRate() {return rate;}                     // Возвращаем атрибут тариф
    double getDiscount() {return discount;}             // Возвращаем атрибут скидка
    std::string getTime1() {return toStrTime(time1);}   // Возвращаем атрибут нач. время
    std::string getTime2() {return toStrTime(time2);}   // Возвращаем атрибут кон. время
    double getResult() {                                // Возвращаем атрибут сумма (+считаем её)
        //result = countingPartyPrice();
        //result = countingDiscountFromPrice();
        result = countingDiscountedPrice();
        return result;
   }
};