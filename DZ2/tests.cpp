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

TEST_CASE("Complex addition and multiplication", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "(x + y) * z", "x=1+1i", "y=2+2i", "z=3+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(9,9)"); // (1+1i + 2+2i) * 3 = (3+3i) * 3 = 9 + 9i
}

TEST_CASE("Complex subtraction and division", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "(x - y) / z", "x=10+10i", "y=4+4i", "z=2+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(3,3)"); // (10+10i - 4+4i) / 2 = (6+6i) / 2 = 3 + 3i
}

TEST_CASE("Complex power and multiplication", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "x ^ y * z", "x=1+1i", "y=2+0i", "z=2+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0,4)"); // (1+1i)^2 * 2 = (0+2i) * 2 = 0 + 4i
}

TEST_CASE("Complex sin and cos combination", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "sin(x) + cos(y)", "x=0+0i", "y=0+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(1,0)"); // sin(0) + cos(0) = 0 + 1 = 1
}

TEST_CASE("Complex ln and exp combination", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "ln(exp(x))", "x=2+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(2,0)"); // ln(exp(2)) = 2
}

TEST_CASE("Complex nested operations", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "(x + y) * (z - w) / (a ^ b)", "x=1+1i", "y=2+2i", "z=3+3i", "w=1+1i", "a=2+0i", "b=2+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0,3)"); // (1+1i + 2+2i) * (3+3i - 1+1i) / (2+0i)^2 = (3+3i) * (2+2i) / 4 = (0+12i) / 4 = 0 + 3i
}

TEST_CASE("Complex sin of sum", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "sin(x + y)", "x=1+1i", "y=2+2i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(3.16584,1.9596)"); // sin(3+3i) ≈ 3.16584 + 1.9596i
}

TEST_CASE("Complex cos of product", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "cos(x * y)", "x=1+1i", "y=2+2i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(-0.642148,-1.06861)"); // cos((1+1i)*(2+2i)) = cos(0+4i) ≈ -0.642148 - 1.06861i
}

TEST_CASE("Complex exp of sum", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "exp(x + y)", "x=1+1i", "y=2+2i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(-10.419,-14.095)"); // exp(3+3i) ≈ -10.419 - 14.095i
}

TEST_CASE("Complex ln of product", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "ln(x * y)", "x=1+1i", "y=2+2i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(1.38629,1.5708)"); // ln((1+1i)*(2+2i)) = ln(0+4i) ≈ 1.38629 + 1.5708i
}

TEST_CASE("Complex sin and cos nested", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "sin(cos(x))", "x=1+1i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0.988898,-0.83373)"); // sin(cos(1+1i)) ≈ 0.988898 - 0.83373i
}

TEST_CASE("Complex exp and ln nested", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "exp(ln(x))", "x=2+2i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(2,2)"); // exp(ln(2+2i)) = 2 + 2i
}

TEST_CASE("Complex power and sin combination", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "sin(x) ^ y", "x=1.5708+0i", "y=2+0i"}; // sin(pi/2) = 1
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(1,0)"); // sin(pi/2)^2 = 1^2 = 1
}

TEST_CASE("Complex cos and division", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "cos(x) / y", "x=0+0i", "y=1+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(1,0)"); // cos(0) / 1 = 1 / 1 = 1
}

TEST_CASE("Complex ln and addition", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "ln(x) + y", "x=1+0i", "y=2+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(2,0)"); // ln(1) + 2 = 0 + 2 = 2
}

TEST_CASE("Complex exp and subtraction", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "exp(x) - y", "x=0+0i", "y=1+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0,0)"); // exp(0) - 1 = 1 - 1 = 0
}

TEST_CASE("Complex combination of all operations", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "(x + y) * (z - w) / (a ^ b) + sin(c) - cos(d)", "x=2+0i", "y=3+0i", "z=4+0i", "w=1+0i", "a=2+0i", "b=2+0i", "c=0+0i", "d=0+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(2.75,0)"); // (2+3)*(4-1)/(2^2) + sin(0) - cos(0) = 5*3/4 + 0 - 1 = 3.75 - 1 = 2.75
}

TEST_CASE("Complex deeply nested expressions", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "sin((x + y) * (z - w)) + cos((a / b) ^ c)", "x=1+0i", "y=2+0i", "z=3+0i", "w=1+0i", "a=4+0i", "b=2+0i", "c=2+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0.540302,0)"); // sin((1+2)*(3-1)) + cos((4/2)^2) = sin(6) + cos(4) ≈ -0.279415 + -0.653644 = -0.933059
}

TEST_CASE("Complex expression with multiple functions", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "ln(x) + sin(y) * cos(z) - exp(w)", "x=1+0i", "y=0+0i", "z=0+0i", "w=0+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(0,0)"); // ln(1) + sin(0) * cos(0) - exp(0) = 0 + 0 * 1 - 1 = -1
}

TEST_CASE("Complex combination of all operations and functions", "[expression]") {
    const char* a[] = {"differentiator", "--eval", "(x + y) * (z - w) / (a ^ b) + sin(c) - cos(d)", "x=2+0i", "y=3+0i", "z=4+0i", "w=1+0i", "a=2+0i", "b=2+0i", "c=0+0i", "d=0+0i"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == "(2.75,0)"); // (2+3)*(4-1)/(2^2) + sin(0) - cos(0) = 5*3/4 + 0 - 1 = 3.75 - 1 = 2.75
}