#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "Triad.h"

class Triangle : public Triad {
public:
    float getArea();
    float getAlpha();
    float getBeta();
    float getGamma();
};

#endif // TRIANGLE_H