#ifndef ComplexTEST_H
#define ComplexTEST_H

#include "Complex.h"
#include "UnitTest.h"

using namespace UnitTest;

class ComplexTest : public Test
{
    Complex t;
public:
    void run()
    {
        testCreate();
        testAdd();
        testSub();
        testMul();
        testDev();
        testCompare();
        testException();
    }

    void testCreate()
    {
        Complex var1;              check(var1 == t);
        var1 = Complex(12, 15);    check(var1 == t); // error
        Complex var2(12, 15);      check(var2 == var1);
        var1 = var2;               check(var1 == var2);
    }

    void testAdd()
    {
        Complex var1 = Complex(12, 15) + Complex(18, 9);
        Complex var2 = Complex(12, 15) + Complex(18, 9);    check(var1 == var2);
        Complex var3 = Complex(12, 15) + Complex(7, 7);     check(var1 == var3); // error
    }

    void testSub()
    {
        Complex var1 = Complex(18, 15) - Complex(12, 9);
        Complex var2 = Complex(18, 15) - Complex(12, 9);    check(var1 == var2);
        Complex var3 = Complex(12, 15) - Complex(7, 7);     check(var1 == var3); // error
    }

    void testMul()
    {
        Complex var1 = Complex(12, 2) * Complex(12, 2);
        Complex var2 = Complex(12, 2) * Complex(12, 2);     check(var1 == var2);
        Complex var3 = Complex(3, 3) * Complex(5, 3);       check(var1 == var3); // error     
    }

    void testDev()
    {
        Complex var1 = Complex(15, 2) / Complex(12, 2);
        Complex var2 = Complex(15, 2) / Complex(12, 2);     check(var1 == var2);
        Complex var3 = Complex(6, 6) / Complex(2, 2);       check(var1 == var3); // error
    }

    void testCompare()
    {
        Complex var1(12, 12);
        check(var1 == Complex(12, 12));
        check(var1 != Complex(12, 2)); // error
        check(var1 <= Complex(12, 12));
        check(var1 < Complex(16, 12));
        check(var1 > Complex(7, 8));
        check(var1 >= Complex(12, 5));
        check(var1 < Complex(12, 18)); // error
    }

    void testException()
    {
        try {
            Complex var1;
            // Complex var2 = var1 / 0; // Раскомментировать, чтобы посмотреть проверку исключения
        } catch (Complex::ComplexError &e) {
            success();
        }
    }
};

#endif // ComplexTEST_H
