#include "token.h"

vector<Token> tokenize(const string& input) {
    vector<Token> tokens;
    size_t i = 0;
    while (i < input.size()) {
        char c = input[i];
        if (isspace(c)) {
            i++;
        } else if (isdigit(c) || c == '.' || c == 'i') {
            string num;
            bool isImaginary = false;
            if (c == 'i') {
                num = "1i";
                isImaginary = true;
                i++;
            } else {
                while (i < input.size() && (isdigit(input[i]) || input[i] == '.')) {
                    num += input[i++];
                }
                if (i < input.size() && input[i] == 'i') {
                    num += input[i++];
                    isImaginary = true;
                }
            }

            tokens.push_back(Token(NUMBER, num));
        } else if (isalpha(c)) {
            string var;
            while (i < input.size() && isalpha(input[i])) {
                var += input[i++];
            }
            if (var == "sin" || var == "cos" || var == "ln" || var == "exp") {
                tokens.push_back(Token(FUNCTION, var));
            } else {
                if (var.size() > 1 && var.back() == 'i') {
                    tokens.push_back(Token(VARIABLE, var.substr(0, var.size() - 1)));
                    tokens.push_back(Token(OPERATOR, "*"));
                    tokens.push_back(Token(NUMBER, "1i"));
                } else {
                    tokens.push_back(Token(VARIABLE, var));
                }
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (c == '-' && (tokens.empty() ||
                tokens.back().type == LEFT_PAREN ||
                tokens.back().type == OPERATOR)) {
                tokens.push_back(Token(OPERATOR, "u-")); \
            } else {
                tokens.push_back(Token(OPERATOR, string(1, c)));
            }
            i++;
        } else if (c == '(') {
            tokens.push_back(Token(LEFT_PAREN, "("));
            i++;
        } else if (c == ')') {
            tokens.push_back(Token(RIGHT_PAREN, ")"));
            i++;
        } else {
            throw invalid_argument("Unknown character: " + string(1, c));
        }
    }
    return tokens;
}
