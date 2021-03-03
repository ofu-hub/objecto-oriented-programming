#include "Body.h"

class Parallelepiped : public Body {
    double h;   // Высота
    double w;   // Ширина
    double l;   // Длина

public:
    // Конструкторы
    Parallelepiped() = default;
    Parallelepiped(double h, double w, double l) {
        this->h = h;
        this->w = w;
        this->l = l;
    }

    // Переопределение базовой функции класса Body
    void Area() {
        double S = 2 * (h * w + w * l + h * l);
        this->setArea(S);
    }
    void Volume() {
        double V = h * w * l;
        this->setVolume(V);
    }
};