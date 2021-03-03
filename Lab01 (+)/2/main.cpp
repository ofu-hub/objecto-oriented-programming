#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "Bill.h"

using namespace std;

int main() {

    Bill Pers_1("Matiz", "+7-927-241-24-12", 12, 120, 240, 20); //* -> TRUE
    Bill Pers_2(Pers_1); //* TRUE
    cout << "Pers_1 => " << Pers_1.toString(); //* TRUE
    cout << "Pers_2 => " << Pers_2.toString(); //* TRUE
    cout << "Pers_1.compareRates(Pers_2) -> " << Pers_1.compareRates(Pers_2) << "\n";  //* TRUE -> 6
    cout << "Pers_1.getDiscountFromPrice() -> " << Pers_1.getDiscountFromPrice() << "\n";  //* TRUE -> 
    cout << "Pers_1.getDiscountedPrice() -> " << Pers_1.getDiscountedPrice() << "\n\n\n";  //* TRUE -> 

    Pers_1.setFamily("Sweet");              //* TRUE
    Pers_1.setNumber("35-42-12");           //* TRUE
    Pers_1.setRate(21);                     //* TRUE
    Pers_1.setStartTime(64);                //* TRUE
    Pers_1.setEndTime(90);                  //* TRUE
    Pers_1.setDiscount(5);                  //* TRUE

    Pers_2.setRate(-5);                  //! FALSE -> Тариф должен быть в диапазоне от 0 до 100 включительно!
    Pers_2.setStartTime(-16);            //! FALSE -> Начало времени разговора не может быть отрицательным или равным нулю!
    Pers_2.setStartTime(16);             //* TRUE
    Pers_2.setEndTime(14);               //! FALSE -> Конец времени разговора не может быть меньше начала времени разговора!
    Pers_2.setDiscount(-7);              //! FALSE -> Скидка должна быть в диапазоне от 0 до 100 включительно!

    cout << "\n\nРабота программы завершена! Спасибо за использовние! \n";
    return 0;
}