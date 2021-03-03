#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

class Body {
    double area;    // �������
    double volume;  // �����

public:
    // ������������
    Body() = default;
    Body(double area, double volume) {
        this->area = area;
        this->volume = volume;
    }

    // ������
    void setArea(double area) {     // ��� ����, ����� ��������� �������
        this->area = area;
    }
    void setVolume(double volume) { // ��� ����, ����� ��������� �����
        this->volume = volume;
    }

    // ������
    double getArea() {              // ���������� �������
        return area;
    }
    double getVolume() {            // ���������� �����
        return volume;
    }

    // ����������� �������
    virtual void Area() = 0;      // ������� ������� ������ ������
    virtual void Volume() = 0;    // ������� ����� ������ ������
    //���������
    void Display() {              // ����� ��� ������ ������
        std::cout << "<" << typeid(*this).name() << ">" << std::endl;
        std::cout << "������� ���. = " << "\t" << area << std::endl;
        std::cout << "����� = " << "\t" << volume << std::endl;
    }
};