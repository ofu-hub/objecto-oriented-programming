#include <iostream>
#include "Bill.h"

int main() {
    setlocale(LC_ALL, "ru");
    Bill bill = Bill("Ѕулкин", "12-12-12", 1.5, 10, Time(1,0,0), Time(3,0,0));
    Bill bill2 = Bill("Ѕулкин", "12-12-12", 1.5, 10, Time(1,0,0), Time(3,0,0));

    //bill.Read();
    
    bill.Display();
    bill2.Display();
    
    std::cout << "\n";
    return 0;
}