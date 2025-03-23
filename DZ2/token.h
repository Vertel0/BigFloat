#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <complex>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

enum TokType {
    NUMBER,
    VARIABLE,
    OPERATOR,
    FUNCTION,
    LEFT_PAREN,
    RIGHT_PAREN
};

struct Token {
    TokType type;
    string value;

    Token(TokType t, const string& v) : type(t), value(v) {}
};

vector<Token> tokenize(const string& input);

#endif
