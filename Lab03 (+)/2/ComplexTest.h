#include "Complex.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "catch2/Doctest.h"

TEST_CASE( "Comparison operations" ) {

    SUBCASE( "operator<" ) {
        REQUIRE( Complex(12, 12) < Complex(18, 20) );
        REQUIRE( Complex(12, 12) < Complex(7, 4) );
    }

    SUBCASE( "operator>" ) {
        REQUIRE( Complex(12, 12) > Complex(7, 4) );
        REQUIRE( Complex(12, 12) > Complex(18, 20) );
    }

    SUBCASE( "operator<=" ) {
        REQUIRE( Complex(12, 12) <= Complex(18, 20) );
        REQUIRE( Complex(12, 12) <= Complex(7, 4) );
    }

    SUBCASE( "operator>=" ) {
        REQUIRE( Complex(12, 12) >= Complex(18, 20) );
        REQUIRE( Complex(12, 12) >= Complex(7, 4) );
    }

    SUBCASE( "operator==" ) {
        REQUIRE( Complex(12, 12) == Complex(12, 12) );
        REQUIRE( Complex(4, 1) == Complex(4, 1) );
    }

    SUBCASE( "operator!=" ) {
        REQUIRE( Complex(12, 12) != Complex(7, 4) );
        REQUIRE( Complex(27, 4) != Complex(7, 4) );
    }
}

TEST_CASE( "Arithmetic operations" ) {

    SUBCASE( "operator+" ) {
        REQUIRE( Complex(12, 12) + Complex(12, 12) == Complex(12, 12) + Complex(12, 12) );
    }

    SUBCASE( "operator-" ) {
        REQUIRE( Complex(12, 12) - Complex(12, 12) == Complex(12, 12) - Complex(12, 12) );
    }

    SUBCASE( "operator/ (result double)" ) {
        REQUIRE( Complex(12, 12) / Complex(3, 3) == Complex(12, 12) / Complex(3, 3) );
    }

    SUBCASE( "operator*" ) {
        REQUIRE( Complex(12, 12) * Complex(5, 5) == Complex(12, 12) * Complex(5, 5) );
    }

    SUBCASE( "operator/ (result Complex)" ) {
        REQUIRE( Complex(12, 12) / Complex(2, 2) == Complex(12, 12) / Complex(2, 2) );
    }
}