#ifndef TRIAD_H
#define TRIAD_H

#include <iostream>
#include <cstdint>

class Triad {
    private:
        float a{0};
        float b{0};
        float c{0};
    
    public:
        // Гетеры
        float getA();
        float getB();
        float getC();

        // Сетеры
        void setA(float n);
        void setB(float n);
        void setC(float n);

        // Сумма чисел
        double getSum();
};

#endif //TRIAD_H
