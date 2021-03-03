#include "Body.h"
#include "Parallelepiped.h"
#include "Ball.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");

    Parallelepiped P(4.5, 3.7, 2.8);
    P.Area();
    P.Volume();
    std::cout << "\nПараллелепипед\t";
    P.Display();

    Ball B(7.4);
    B.Area();
    B.Volume();
    std::cout << "\nШар          \t";
    B.Display();

    system("pause");
    return 0;
}