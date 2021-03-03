#include <iostream>
#include "Bill.h"

using namespace std;

int main() {

	Bill bill;

    bill.Read();

    cout << "\n\nИнформация и чек за телефонный разговор: \n";
    bill.Display();

    cout << "\n";
    return 0;
}