#ifndef COMP_H
#define COMP_H
#include <complex>
#include <string>
#include <map>
#include "token.h"
#include "parser.h"
#include "expression.h"
using namespace std;

string formatComplex(complex<double> value);
string ParseArguments(int argc, char* argv[]);

#endif
