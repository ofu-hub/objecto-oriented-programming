#include "Triangle.h"
#include <iostream>
#include <cmath>

#define PI 3.14159265

float Triangle::getArea() {
    float p = getSum() / 2.0;
    return sqrt(p*(p-getA())*(p-getB())*(p-getC()));
}
 
float Triangle::getAlpha() {
    return 180.0-getBeta()-getGamma();
}
 
float Triangle::getBeta() {
    return asin(2.0*getArea()/(getC()*getA()))*180/PI;
}
 
float Triangle::getGamma() {
    return acos((getC()*getC()-getA()*getA()-getB()*getB())/(-2.0*getA()*getB()))*180/PI;
}