#include "catch_amalgamated.hpp"
#include <cstdint>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "expression.h"
#include "parser.h"
#include "token.h"
#include "complex_f.h"
using namespace std;

TEST_CASE("Simple complex addition", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x + y", "x=1+1i", "y=2+2i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(3,3)");
}

TEST_CASE("Complex subtraction", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x - y", "x=5+5i", "y=2+3i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(3,2)");
}

TEST_CASE("Complex multiplication", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x * y", "x=1+2i", "y=3+4i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(-5,10)");
}

TEST_CASE("Complex division", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x / y", "x=4+4i", "y=2+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(2,2)");
}

TEST_CASE("Complex sin function", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "sin(x)", "x=0+1i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0,1.1752)");
}

TEST_CASE("Complex cos function", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "cos(x)", "x=0+1i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "1.54308");
}

TEST_CASE("Complex exp function", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "exp(x)", "x=1+1i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(1.46869,2.28736)");
}

TEST_CASE("Complex ln function", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "ln(x)", "x=1+1i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0.346574,0.785398)");
}

TEST_CASE("Nested complex operations", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "(x + y) * (z - w)", "x=1+1i", "y=2+2i", "z=3+3i", "w=1+1i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0,12)");
}

TEST_CASE("Complex with real numbers", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x + 5", "x=2+3i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(7,3)");
}

TEST_CASE("Pure imaginary multiplication", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x * y", "x=0+2i", "y=0+3i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "-6");
}

TEST_CASE("Complex conjugate", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x * y", "x=3+4i", "y=3-4i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "25");
}

TEST_CASE("Multiple operations", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x * y + z * w", "x=1+1i", "y=2+2i", "z=3+3i", "w=4+4i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0,28)");  
}

TEST_CASE("Complex division with imaginary denominator", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x / y", "x=1+1i", "y=0+1i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(1,-1)");
}

TEST_CASE("Complex power of real number", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x ^ y", "x=2+0i", "y=3+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "8");
}

TEST_CASE("Complex power with imaginary exponent", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x ^ y", "x=1+1i", "y=0+1i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0.428829,0.154872)");
}

TEST_CASE("Nested functions", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "sin(cos(x))", "x=1+1i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(1.13297,-0.778408)");
}

TEST_CASE("Complex expression with parentheses", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "(x + y) * (z + w)", "x=1+0i", "y=0+1i", "z=2+0i", "w=0+2i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0,4)");
}

TEST_CASE("Complex variables without imaginary part", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x + y", "x=5", "y=3"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "8");
}

TEST_CASE("Mixed real and complex variables", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x + y", "x=5", "y=3+2i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(8,2)");
}

TEST_CASE("Complex expression with multiple operations", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x * y - z / w", "x=1+1i", "y=2+2i", "z=4+4i", "w=2+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(-2,2)");
}

TEST_CASE("Complex derivative of polynomial", "[diff]") {
    const char* a[] = {"differentiator", "--diff", "x^2 + 3*x + 5", "--by", "x"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "((((2,0) * (x ^ ((2,0) - (1,0)))) + (((0,0) * x) + ((3,0) * (1,0)))) + (0,0))");
}

TEST_CASE("Complex derivative of sin function", "[diff]") {
    const char* a[] = {"differentiator", "--diff", "sin(x)", "--by", "x"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(cos(x) * (1,0))");
}

TEST_CASE("Complex derivative of cos function", "[diff]") {
    const char* a[] = {"differentiator", "--diff", "cos(x)", "--by", "x"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(((-1,0) * sin(x)) * (1,0))");
}

TEST_CASE("Complex derivative of exp function", "[diff]") {
    const char* a[] = {"differentiator", "--diff", "exp(x)", "--by", "x"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "((1,0) * exp(x))");
}

TEST_CASE("Complex derivative of ln function", "[diff]") {
    const char* a[] = {"differentiator", "--diff", "ln(x)", "--by", "x"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "((1,0) / x)");
}

TEST_CASE("Complex derivative of product", "[diff]") {
    const char* a[] = {"differentiator", "--diff", "x * sin(x)", "--by", "x"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(((1,0) * sin(x)) + (x * (cos(x) * (1,0))))");
}

TEST_CASE("Complex derivative of quotient", "[diff]") {
    const char* a[] = {"differentiator", "--diff", "x / ln(x)", "--by", "x"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "((((1,0) * ln(x)) - (x * ((1,0) / x))) / (ln(x) * ln(x)))");
}

TEST_CASE("Complex derivative of power function", "[diff]") {
    const char* a[] = {"differentiator", "--diff", "x^3", "--by", "x"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "((3,0) * (x ^ ((3,0) - (1,0))))");
}

TEST_CASE("Complex derivative of nested functions", "[diff]") {
    const char* a[] = {"differentiator", "--diff", "sin(cos(x))", "--by", "x"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(cos(cos(x)) * (((-1,0) * sin(x)) * (1,0)))");
}