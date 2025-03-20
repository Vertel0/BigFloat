#include <iostream>
#include <map>
#include <memory>
#include <complex>
#include "expression.h"
using namespace std;

int main()
{
    map<string, complex<double>> m;
    m["a"] = 2.0 +3i;
    m["b"] = 0;
    string a = "a";
    shared_ptr< Expression <complex<double>> > expr = make_shared<BinaryExpression<complex<double>> >
    (make_shared<VariableExpression<complex<double>> >("a"),
      make_shared<VariableExpression<complex<double>> >("b"),
      Div);
    cout<<(expr->eval(m));
    return 0;
}
