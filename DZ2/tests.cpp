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


TEST_CASE( "ln", "[expression]" ) {
    const char* a[] = {"expression.exe", "--eval", "ln(x)", "x=10"};
    int b = sizeof(a) / sizeof(a[0]);
    string q = ParseArguments(b, const_cast<char**>(a));
    REQUIRE(q == to_string(log(10)));
}

