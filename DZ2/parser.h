#ifndef PARSER_H
#define PARSER_H
#include <stack>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#include "token.h"
#include "expression.h"

template<typename T>
shared_ptr<Expression<T>> parseExpression(const vector<Token>& tokens, const vector<string>& variables) {
    stack<shared_ptr<Expression<T>>> values;
    stack<string> operators;

    map<string, int> precedence = {
        {"+", 1}, {"-", 1},
        {"*", 2}, {"/", 2},
        {"^", 3},
        {"sin", 4}, {"cos", 4}, {"ln", 4}, {"exp", 4}
    };

    for (const auto& token : tokens) {
        if (token.type == NUMBER) {
            T value;
            if (token.value.back() == 'i') {
                string numStr = token.value.substr(0, token.value.size() - 1);
                double num = numStr.empty() ? 1.0 : stod(numStr);
                value = T(0, num);
            } else {
                value = T(stod(token.value), 0);
            }
            values.push(make_shared<ConstantExpression<T>>(value));
        } else if (token.type == VARIABLE) {
            if (find(variables.begin(), variables.end(), token.value) == variables.end()) {
                values.push(make_shared<ConstantExpression<T>>(T(0)));
            } else {
                values.push(make_shared<VariableExpression<T>>(token.value));
            }
        } else if (token.type == FUNCTION) {
            operators.push(token.value);
        } else if (token.type == OPERATOR) {
            while (!operators.empty() && operators.top() != "(" &&
                   precedence[operators.top()] >= precedence[token.value]) {
                string op = operators.top();
                operators.pop();

                if (op == "sin" || op == "cos" || op == "ln" || op == "exp") {
                    auto expr = values.top();
                    values.pop();
                    functions f = (op == "sin") ? Sin : (op == "cos") ? Cos : (op == "ln") ? Ln : Exp;
                    values.push(make_shared<MonoExpression<T>>(expr, f));
                } else {
                    auto right = values.top();
                    values.pop();
                    auto left = values.top();
                    values.pop();
                    operation op_type = (op == "+") ? Plus : (op == "-") ? Minus : (op == "*") ? Mul : (op == "/") ? Div : Pow;
                    values.push(make_shared<BinaryExpression<T>>(left, right, op_type));
                }
            }
            operators.push(token.value);
        } else if (token.type == LEFT_PAREN) {
            operators.push(token.value);
        } else if (token.type == RIGHT_PAREN) {
            while (!operators.empty() && operators.top() != "(") {
                string op = operators.top();
                operators.pop();

                if (op == "sin" || op == "cos" || op == "ln" || op == "exp") {
                    auto expr = values.top();
                    values.pop();
                    functions f = (op == "sin") ? Sin : (op == "cos") ? Cos : (op == "ln") ? Ln : Exp;
                    values.push(make_shared<MonoExpression<T>>(expr, f));
                } else {
                    auto right = values.top();
                    values.pop();
                    auto left = values.top();
                    values.pop();
                    operation op_type = (op == "+") ? Plus : (op == "-") ? Minus : (op == "*") ? Mul : (op == "/") ? Div : Pow;
                    values.push(make_shared<BinaryExpression<T>>(left, right, op_type));
                }
            }
            if (!operators.empty() && operators.top() == "(") {
                operators.pop();
            } else {
                throw invalid_argument("Mismatched parentheses");
            }
        }
    }

    while (!operators.empty()) {
        string op = operators.top();
        operators.pop();

        if (op == "sin" || op == "cos" || op == "ln" || op == "exp") {
            auto expr = values.top();
            values.pop();
            functions f = (op == "sin") ? Sin : (op == "cos") ? Cos : (op == "ln") ? Ln : Exp;
            values.push(make_shared<MonoExpression<T>>(expr, f));
        } else {
            auto right = values.top();
            values.pop();
            auto left = values.top();
            values.pop();
            operation op_type = (op == "+") ? Plus : (op == "-") ? Minus : (op == "*") ? Mul : (op == "/") ? Div : Pow;
            values.push(make_shared<BinaryExpression<T>>(left, right, op_type));
        }
    }

    if (values.size() != 1) {
        throw invalid_argument("Invalid expression");
    }

    return values.top();
}
#endif
