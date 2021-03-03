#include <iostream>

#include "Complex.h"              // -- рабочий класс --
#include "ComplexTest.h"          // -- тестовый класс --

using namespace std;

int main() {
    ComplexTest test;               // -- объект тестового класса --
    test.run();                     // -- запуск тестовых методов --
    test.report();                  // -- вывод отчета --
    
    std::cout << "\n\nРабота программы завершена! \n";
    return 0;
}