#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Complex.h"

std::pair<double, double> transform(Complex const& a) {
	double x, y;
	x = a.r * cos(a.a);
	y = a.r * sin(a.a);
	return { x, y };
}

Complex transform(std::pair<double, double> n) {
	Complex temp;
	temp.setRadius(n.first * n.first + n.second * n.second);
	temp.setAngle(atan(n.second / n.first) * 180 / 3.14159265358979323846);
	return temp;
}

Complex Complex::operator + (Complex const& n) const {
	auto pairOg = transform(*this), pairA = transform(n);
	pairOg.first += pairA.first;
	pairOg.second += pairA.second;
	Complex temp = transform(pairOg);
	return temp;
}

Complex Complex::operator - (Complex const& n) const {
	auto pairOg = transform(*this), pairA = transform(n);
	pairOg.first -= pairA.first;
	pairOg.second -= pairA.second;
	Complex temp = transform(pairOg);
	return temp;
}


bool Complex::operator >(Complex const& n) const {
	if (transform(*this).first > transform(n).first) return true;
	return false;
}

bool Complex::operator==(Complex const& n) const {
	if (a == n.a && r == n.r) return true;
	return false;
}

bool Complex::operator >=(Complex const& n) const {
	return (*this == n) || (*this > n);
}

bool Complex::operator <(Complex const& n) const {
	return !(*this > n);
}

bool Complex::operator <=(Complex const& n) const {
	return (*this == n) || (*this < n);
}

Complex Complex::operator / (Complex const& n) const {
	if (n.r == 0)
	{
		throw std::logic_error("Деление на 0");
	}
	Complex temp;
	temp.r = r / n.r;
	temp.a = a - n.a;
	return temp;
}

Complex Complex::operator * (Complex const& n) const {
	Complex temp;
	temp.r = r * n.r;
	temp.a = a + n.a;
	return temp;
}

Complex Complex::operator - () const {
	Complex temp;
	temp.r = r;
	temp.a = 0 - a;
	return temp;
}

std::string Complex::toString() const noexcept {
        std::stringstream str;
        str << "z =  " << r << " * (cos(" << a << ") + " << "i * sin(" << a << ")).\n";
        return str.str();
}

std::ostream& operator <<(std::ostream& os, const Complex &a)  {
	os << a.toString();
	return os;
}

std::istream& operator >>(std::istream& is, Complex& a) {
	double mod, arg;
	is.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	is >> mod >> arg;
	a.Init(mod, arg);
	return is;
}
