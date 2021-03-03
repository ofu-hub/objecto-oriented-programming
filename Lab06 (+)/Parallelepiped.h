#include "Body.h"

class Parallelepiped : public Body {
    double h;   // ������
    double w;   // ������
    double l;   // �����

public:
    // ������������
    Parallelepiped() = default;
    Parallelepiped(double h, double w, double l) {
        this->h = h;
        this->w = w;
        this->l = l;
    }

    // ��������������� ������� ������� ������ Body
    void Area() {
        double S = 2 * (h * w + w * l + h * l);
        this->setArea(S);
    }
    void Volume() {
        double V = h * w * l;
        this->setVolume(V);
    }
};