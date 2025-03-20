#include <iostream>
#include <map>
#include <memory>
#include <complex>
#include "expression.h"
using namespace std;

int main()
{
    map<string, int> m;
    shared_ptr<Expression<int> > x = make_shared<ConstantExpression<int> >(5);
    cout<<x->eval(m);
    return 0;
}
