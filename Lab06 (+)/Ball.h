#include "Body.h"

class Ball : public Body {
    double r;   // Радиус

public:
    // Конструкторы
    Ball() = default;
    Ball(double r) {
        this->r = r;
    }

    // Переопределение базовой функции класса Body
    void Area() {
        double S = 4 * M_PI * pow(r, 2);
        this->setArea(S);
    }
    void Volume() {
        double V = (4.0 / 3.0) * M_PI * pow(r, 3);
        this->setVolume(V);
    }
};