#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

class Body {
    double area;    // Площадь
    double volume;  // Объём

public:
    // Конструкторы
    Body() = default;
    Body(double area, double volume) {
        this->area = area;
        this->volume = volume;
    }

    // Сетеры
    void setArea(double area) {     // Для того, чтобы сохранить площадь
        this->area = area;
    }
    void setVolume(double volume) { // Для того, чтобы сохранить объём
        this->volume = volume;
    }

    // Гетеры
    double getArea() {              // Возвращаем площадь
        return area;
    }
    double getVolume() {            // Возвращаем объём
        return volume;
    }

    // Виртуальные функции
    virtual void Area() = 0;      // Считаем площадь каждой фигуры
    virtual void Volume() = 0;    // Считаем объём каждой фигруы
    //Интерфейс
    void Display() {              // Вывод для каждой фигуры
        std::cout << "<" << typeid(*this).name() << ">" << std::endl;
        std::cout << "Площадь пов. = " << "\t" << area << std::endl;
        std::cout << "Обьем = " << "\t" << volume << std::endl;
    }
};