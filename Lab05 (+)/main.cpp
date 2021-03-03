#include <iostream>
#include "Triangle.h"
#include "Triad.h"

using namespace std;

int main() {
    Triangle t;

    t.setA(3.0);
    t.setB(4.0);
    t.setC(5.0);

    cout << t.getArea() << endl;
    cout << t.getAlpha() << endl;
    cout << t.getBeta() << endl;
    cout << t.getGamma() << endl;

    return 0;
}