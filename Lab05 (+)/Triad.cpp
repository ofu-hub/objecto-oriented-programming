#include "Triad.h"
#include <iostream>

float Triad::getA() {
    return a;
}
 
float Triad::getB() {
    return b;
}
 
float Triad::getC() {
    return c;
}
 
void Triad::setA(float n) {
    this->a = n;
}
 
void Triad::setB(float n) {
    this->b = n;
}
 
void Triad::setC(float n) {
    this->c = n;
}
 
double Triad::getSum() {
    return a + b + c;
}