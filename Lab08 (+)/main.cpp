#include "Hex.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Doctest.h"

TEST_CASE("Тесты класса Array") {
    Array t;    // Нулевой объект
    SUBCASE("Конструкторы") {
        Array array1;
        REQUIRE(array1 == t);
        REQUIRE(array1.size() == 0);
        REQUIRE(array1.getData() == nullptr);
        Array array2(2);
        REQUIRE(array2.toString() == "00");
        Array array3(4, 4);
        REQUIRE(array3.toString() == "4444");
        array2 = array3;
        REQUIRE(array2.toString() == "4444");
        array2.push_back(3);
        REQUIRE(array2.toString() == "44443");
        Array array4 = {1, 2, 3};
        REQUIRE(array4.toString() == "123");
        array4 = {};
        REQUIRE(array4.size() == 0);
        Array array5(array2);
        array5.pop_back();
        REQUIRE(array5.toString() == "4444");
    }
    SUBCASE("Индексация, добавление и удаление") {
        Array array1("1234");
        REQUIRE(array1[0] == 1);
        REQUIRE(array1[2] == 3);
        array1.push_back(1);
        REQUIRE(*(array1.end()-1) == 1);
        REQUIRE(*(array1.begin()+2) == 3);
        array1.erase(array1.begin()+2, array1.end());
        REQUIRE(array1.toString() == "12");
    }
    SUBCASE("Операции сравнения") {
        Array array1 = {1, 2};
        Array array2 = {1, 4};
        Array array3 = array2;
        Array array4 = {2, 4, 3};

        REQUIRE(array1 < array2);
        REQUIRE(array2 > array1);
        REQUIRE(array2 >= array3);
        REQUIRE(array1 <= array4);
        REQUIRE(array2 == array3);
        REQUIRE(array2 != array4);
    }
    SUBCASE("Тест исключений") {
        CHECK_THROWS([&](){     // Индекс за диапазоном
            Array array1(3, 4);
            array1[6];
        }());
        CHECK_THROWS([&](){     // Нулевой размер
            Array array1(0, 4);
        }());
    }
}

TEST_CASE("Тесты класса Hex") {
    Hex t;
    SUBCASE("Конструкторы") {
        Hex hex;
        REQUIRE(hex == t);
        REQUIRE(hex.size() == 0);
        REQUIRE(hex.getData() == nullptr);
        Hex hex1(5, 4);
        REQUIRE(hex1.toString() == "44444");
        Hex hex2 = hex1;
        hex2.pop_back();
        hex2.push_back(1);
        REQUIRE(hex2.toString() == "44441");
        Hex hex3 = {1, 3, 4};
        REQUIRE(hex3.toString() == "134");
    }
    SUBCASE("Тест сложения") {
        Hex hex("2011");
        Hex hex1("1003");
        Hex hex2 = hex + hex1;
        hex += hex1;
        REQUIRE(hex2.toString() == "3014");
        REQUIRE(hex.toString() == "3014");
    }
    SUBCASE("Тест вычитания") {
        Hex hex("2011");
        Hex hex1("1003");
        Hex hex2 = hex - hex1;
        hex -= hex1;
        REQUIRE(hex2.toString() == "1003");
        REQUIRE(hex.toString() == "1003");
    }
    SUBCASE("Тест умножения") {
        Hex hex("2011");
        Hex hex1("1003");
        Hex hex2 = hex * hex1;
        hex *= hex1;
        REQUIRE(hex2.toString() == "2022033");
        REQUIRE(hex.toString() == "2022033");
    }
    SUBCASE("Тест деления") {
        Hex hex("2011");
        Hex hex1("1003");
        Hex hex2 = hex / hex1;
        hex /= hex1;
        REQUIRE(hex2.toString() == "2");
        REQUIRE(hex.toString() == "2");
    }
    SUBCASE("Тест исключений") {
        CHECK_THROWS([&](){     // Не 16-ричное число
            Hex hex(15, 17);
        }());
        CHECK_THROWS([&](){     // var1 < var2 при вычитании
            Hex hex1("14");
            Hex hex2("1003");
            hex1 -= hex2;
        }());
        CHECK_THROWS([&](){     // Деление на 0
            Hex hex1(4, 2);
            Hex hex2(1, 0);
            hex1 /= hex2;
        }());
    }
}