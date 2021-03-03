#pragma once

#include <iostream>
#include <string>	// std::string
#include <utility>	// std::pair
#include <string>
#include <sstream>
#include <stdexcept>

class Complex {

private:
    double r = 0; // Радиус
    double a = 0; // Угол
    
public:
	Complex() = default;
    Complex(const Complex &var2) {
        *this = var2;
    }
    Complex(double a, double r) {
        this->a = a;
        this->r = r;
    }

    class ComplexError{};
    Complex(std::string t);

    void Init(double a, double b) {
		setRadius(a);
		setAngle(b);
	}

    // toString
    std::string toString() const noexcept;

    // Сетеры
    void setRadius(double n) {
		r = n;
	}
	void setAngle(double n) {
		a = n;
	}
    
    // Гетеры
    double getRadius() {
        return r;
    }
    double getAngle() {
        return a;
    }

    // Операции
	bool operator == (Complex const& a) const;
	bool operator != (Complex const& a) const;
	bool operator > (Complex const& a) const;
	bool operator < (Complex const& a) const;
	bool operator <= (Complex const& a) const;
	bool operator >= (Complex const& a) const;
	Complex operator + (Complex const& a) const;
	Complex operator - (Complex const& a) const;
	Complex operator / (Complex const& a) const;
	Complex operator * (Complex const& a) const;
	Complex operator - () const;

	friend std::pair<double, double> transform(Complex const& a);
	friend Complex transform(std::pair<double, double> a);
	friend std::ostream& operator <<(std::ostream& os, const Complex& a);
	friend std::ostream& operator >>(std::istream& is, const Complex& a);
};