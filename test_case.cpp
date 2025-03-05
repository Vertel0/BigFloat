#include "catch_amalgamated.hpp"
#include "big_decimal.h"
#include <cstdint>



TEST_CASE( "Plusik", "[big_decimal]" ) {
    big_decimal a("7892.9430", 50), b("-0.3431", 50);
    big_decimal c = a + b;
    REQUIRE(c - big_decimal("7892.5999", 50) < big_decimal("0.00000001", 50));
}

TEST_CASE( "Minusik", "[big_decimal]" ) {
    big_decimal a("7892.9430", 50), b("-0.3431", 50);
    big_decimal c = a - b;
    REQUIRE(big_decimal("7893.2861", 50) - c < big_decimal("0.00000001", 50));
}

TEST_CASE( "Umnozenie", "[big_decimal]" ) {
    big_decimal a("7892.9430", 50), b("-0.3431", 50);
    big_decimal c = a * b;
    REQUIRE(c - big_decimal("-2708.0687433", 90) < big_decimal("0.00000001", 90));
}

TEST_CASE( "Delenie", "[big_decimal]" ) {
    big_decimal a("7892.9430", 70), b("-0.3431", 70);
    big_decimal c = a / b;
    REQUIRE(big_decimal("-23004.7886913", 70) - c < big_decimal("0.0000001", 70));
}

TEST_CASE( "Bolshe", "[big_decimal]" ) {
    big_decimal a("7892.9430", 70), b("-0.3431", 70);
    REQUIRE(a > b);
}

TEST_CASE( "Menshe", "[big_decimal]" ) {
    big_decimal a("7892.9430", 70), b("-0.3431", 70);
    REQUIRE(b < a);
}

TEST_CASE( "Ravno", "[big_decimal]" ) {
    big_decimal a("7892.9430", 70), b("7892.9430", 70);
    REQUIRE(a == b);
}

TEST_CASE( "Ne ravno", "[big_decimal]" ) {
    big_decimal a("7892.9430", 70), b("-0.3431", 70);
    REQUIRE(a != b);
}


