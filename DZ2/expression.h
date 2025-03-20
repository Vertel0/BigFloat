#include<iostream>
#include<map>
#include<memory>
#include<cmath>
#include <string>
#include <sstream>
using namespace std;


enum operation {Plus, Minus, Div, Mul, Pow};
enum functions {Sin, Cos, Ln, Exp};

class operators {
public:
    operation value;
    int priority;
    operators(operation op) : value(op) {
        if (value == Plus || value == Minus) {
            priority = 1;
        }
        if (value == Div || value == Mul) {
            priority = 2;
        }
        if (value == Pow) {
            priority = 3;
        }
    }
};

template<typename T>
class Expression{

    public:
    virtual shared_ptr<Expression> dif(string &s) = 0;
    virtual T eval(map<string, T> & parametrs) = 0;
    virtual string ToString() = 0;

};

template<typename T>
class ConstantExpression : public Expression<T>{
    private:
        T value;
    public:
        ConstantExpression(T val) : value(val) {
        };

        ConstantExpression(const ConstantExpression&) = default;
        ConstantExpression& operator=(const ConstantExpression&) = default;
        ConstantExpression(ConstantExpression&&) = default;
        ConstantExpression& operator=(ConstantExpression&&) = default;
        T getValue() {
            return value;
        }
        T eval(map<string, T> &parametrs);
        shared_ptr<Expression<T>> dif(string &s);
        string ToString();
        ~ConstantExpression() = default;
};

template<typename T>
T ConstantExpression<T>::eval(map<string, T>& parametrs){
    return value;
}


template<typename T>
shared_ptr<Expression<T>>  ConstantExpression<T>:: dif(string &s){
    return make_shared<ConstantExpression<T>>(ConstantExpression<T>(0));
}


template<typename T>
class VariableExpression : public Expression<T>{
    private:
        string value;
    public:
        VariableExpression(string val) : value(val) {};

        VariableExpression(const VariableExpression&) = default;
        VariableExpression& operator=(const VariableExpression&) = default;
        VariableExpression(VariableExpression&&) = default;
        VariableExpression& operator=(VariableExpression&&) = default;
        T getValue() {
            return value;
        }
        T eval(map<string, T> &parametrs) override;
        shared_ptr<Expression<T>> dif(string &s) override;
        string ToString() override;
        ~VariableExpression() = default;
};


template<typename T>
T VariableExpression<T>::eval(map<string, T>& parametrs){
    return parametrs[value];
}


template<typename T>
shared_ptr<Expression<T>>  VariableExpression<T>:: dif(string &s){
    if(s == value){
        return make_shared<ConstantExpression<T>>(ConstantExpression<T>(T(1)));
    }
    return make_shared<ConstantExpression<T>>(ConstantExpression<T>(T(0)));
}


template<typename T>
class MonoExpression: public Expression<T>{
public:
    shared_ptr<Expression<T>> expr;
    functions f;
public:
    MonoExpression(shared_ptr<Expression<T>> expr, functions f){
        this->expr = expr;
        this->f = f;
    }
    MonoExpression(const MonoExpression&) = default;
    MonoExpression& operator=(const MonoExpression&) = default;
    MonoExpression(MonoExpression&&) = default;
    MonoExpression& operator=(MonoExpression&&) = default;

    T eval(map<string, T> &parametrs) override;
    shared_ptr<Expression<T>> dif(string &s) override;
    string ToString() override;
    ~MonoExpression() = default;
};


template<typename T>
T MonoExpression<T>:: eval(map<string, T> &parametrs){
    switch (f) {
        case Cos:
            return cos(expr->eval(parametrs));
        case Sin:
            return sin(expr->eval(parametrs));
        case Ln:
            return log(expr->eval(parametrs));
        case Exp:
            return exp(expr->eval(parametrs));
    }
}


template<typename T>
class BinaryExpression : public Expression<T> {
public:
    shared_ptr<Expression<T>> LeftExpr;
    shared_ptr<Expression<T>> RightExpr;
    operators op;

public:
    BinaryExpression(const shared_ptr<Expression<T>> LeftExpr, const shared_ptr<Expression<T>> RightExpr, operation op): op(op) {
        this->LeftExpr = LeftExpr;
        this->RightExpr = RightExpr;
    }

    BinaryExpression(const BinaryExpression&) = default;
    BinaryExpression& operator=(const BinaryExpression&) = default;
    BinaryExpression(BinaryExpression&&) = default;
    BinaryExpression& operator=(BinaryExpression&&) = default;

    shared_ptr<Expression<T>> GetLeftExpr() {
         return LeftExpr;
    }
    void SetLeftExpr(shared_ptr<Expression<T>> LeftExpr) {
         this->LeftExpr = LeftExpr;
    }
    operators getOp() {
         return op;
    }
    T eval(map<string, T> &parametrs) override;
    shared_ptr<Expression<T>> dif(string &s) override;
    string ToString() override;
    ~BinaryExpression() = default;
};


template<typename T>
T BinaryExpression<T>:: eval(map<string, T> & parametrs){
    switch(op.value){
    case Plus:
        return LeftExpr->eval(parametrs) + RightExpr->eval(parametrs);
    case Minus:
        return LeftExpr->eval(parametrs) - RightExpr->eval(parametrs);
    case Mul:
        return LeftExpr->eval(parametrs) * RightExpr->eval(parametrs);
    case Div:
        if(RightExpr->eval(parametrs) == T(0)){
            //throw exception
        }
        return LeftExpr->eval(parametrs) / RightExpr->eval(parametrs);
    case Pow:
        return pow(LeftExpr->eval(parametrs), RightExpr->eval(parametrs));
    }
}


template <typename T>
shared_ptr<Expression<T>> MonoExpression<T> :: dif(string& s){
    auto ExprDif = expr->dif(s);
    switch(f){
    case Sin:{
        return make_shared<BinaryExpression<T>>(make_shared<MonoExpression<T>>(MonoExpression<T>(expr, Cos)),ExprDif,Mul);

    }
    case Cos:{
        return make_shared<BinaryExpression<T>>(
        make_shared<BinaryExpression<T>>(BinaryExpression<T>(
        make_shared<ConstantExpression<T>>(ConstantExpression<T>(T(-1))),
        make_shared<MonoExpression<T>>(MonoExpression<T>(expr, Sin)),
        Mul)), ExprDif, Mul);
    }
    case Ln:{
        return make_shared<BinaryExpression<T>>(BinaryExpression<T>(ExprDif, expr, Div));
    }
    case Exp:{
        return make_shared<BinaryExpression<T>>(BinaryExpression<T>(ExprDif,make_shared<MonoExpression<T>>(MonoExpression<T>(expr, f)),Mul));
    }
    return nullptr;
    }
}


template<typename T>
shared_ptr<Expression<T>> BinaryExpression<T>:: dif(string& s){
    auto LeftExprDif = LeftExpr->dif(s);
    auto RightExprDif = RightExpr->dif(s);
    switch(op.value){
    case Plus:{
        return make_shared <BinaryExpression<T>>(BinaryExpression<T>(LeftExprDif, RightExprDif, Plus));
    }
    case Minus:{
        return make_shared <BinaryExpression<T>>(BinaryExpression<T>(LeftExprDif, RightExprDif, Minus));
    }
    case Mul:{
        return make_shared <BinaryExpression<T>>(BinaryExpression<T>(
         make_shared <BinaryExpression<T>>(BinaryExpression<T>(LeftExprDif, RightExpr, Mul)),
         make_shared <BinaryExpression<T>>(BinaryExpression<T>(LeftExpr, RightExprDif, Mul)),
         Plus));
    }
    case Div:{
        return make_shared<BinaryExpression<T>>(BinaryExpression<T>(make_shared <BinaryExpression<T>>(BinaryExpression<T>(
         make_shared <BinaryExpression<T>>(BinaryExpression<T>(LeftExprDif, RightExpr, Mul)),
         make_shared <BinaryExpression<T>>(BinaryExpression<T>(LeftExpr, RightExprDif, Mul)),
         Minus)),
         make_shared<BinaryExpression<T>>(BinaryExpression<T>(RightExpr, RightExpr, Mul)),
         Div));
    }
    case Pow:{
        return make_shared <BinaryExpression<T>>(BinaryExpression<T>(
         RightExpr,
         make_shared <BinaryExpression<T>>(BinaryExpression<T>(LeftExpr,
         make_shared<BinaryExpression<T>>(BinaryExpression<T>(RightExpr, make_shared<ConstantExpression<T>>(ConstantExpression<T>(T(1))), Minus)),
         Pow)),
         Mul));
    }
    }
}

template <typename T>
string ConstantExpression<T>::ToString() {
    ostringstream oss;
    oss << value;
    return oss.str();
}


template <typename T>
string VariableExpression<T>::ToString() {
    return value;
}


template <typename T>
string MonoExpression<T>::ToString()  {
    string tmp;
    switch (f) {
        case Cos:
            tmp = "cos";
        break;
        case Sin:
            tmp = "sin";
        break;
    case Ln:
        tmp = "ln";
        break;
    case Exp:
            tmp = "exp";
        break;
    }
    return tmp + "(" + expr->   ToString() + ")";
}


template <typename T>
string BinaryExpression<T>::ToString() {
    string tmp;
    switch (op.value) {
        case Plus:
            tmp = "+";
        break;
        case Minus:
            tmp = "-";
        break;
        case Mul:
            tmp = "*";
        break;
        case Div:
            tmp = "/";
        break;
        case Pow:
            tmp = "^";
        break;
    }
    return "(" + LeftExpr->ToString() + " " + tmp + " " + RightExpr->ToString() + ")";
}
