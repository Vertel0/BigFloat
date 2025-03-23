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



void parseArguments(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Use: differentiator --eval <expression> [variables] or differentiator --diff <expression> --by <variable>" << endl;
        exit(1);
    }

    string mode = argv[1];

    if (mode == "--eval") {
        if (argc < 3) {
            cerr << "Error: No expression provided for evaluation." << endl;
            exit(1);
        }

        string expression = argv[2];
        map<string, complex<double>> variables;
        for (int i = 3; i < argc; i++) {
            string arg = argv[i];
            size_t eqPos = arg.find('=');
            if (eqPos == string::npos) {
                cerr << "Error: Invalid variable format: " << arg << endl;
                exit(1);
            }
            string var = arg.substr(0, eqPos);
            string valueStr = arg.substr(eqPos + 1);
            size_t plusPos = valueStr.find('+');
            size_t minusPos = valueStr.find('-', 1);
            size_t iPos = valueStr.find('i');

            double realPart = 0.0;
            double imagPart = 0.0;

            if (iPos != string::npos) {
                if (plusPos != string::npos) {
                    realPart = stod(valueStr.substr(0, plusPos));
                    imagPart = stod(valueStr.substr(plusPos + 1, iPos - plusPos - 1));
                } else if (minusPos != string::npos) {
                    realPart = stod(valueStr.substr(0, minusPos));
                    imagPart = stod(valueStr.substr(minusPos, iPos - minusPos));
                } else {
                    imagPart = stod(valueStr.substr(0, iPos));
                }
            } else {
                realPart = stod(valueStr);
            }

            variables[var] = complex<double>(realPart, imagPart);
        }

        try {
            auto tokens = tokenize(expression);
            vector<string> varNames;
            for (const auto& pair : variables) {
                varNames.push_back(pair.first);
            }
            auto expr = parseExpression<complex<double>>(tokens, varNames);
            map<string, complex<double>> params;
            for (const auto& pair : variables) {
                params[pair.first] = pair.second;
            }
            complex<double> result = expr->eval(params);
            cout << formatComplex(result) << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            exit(1);
        }
    } else if (mode == "--diff") {
        if (argc < 5 || string(argv[3]) != "--by") {
            cerr << "Error: Invalid command format for derivative calculation." << endl;
            exit(1);
        }

        string expression = argv[2];
        string var = argv[4];
        try {
            auto tokens = tokenize(expression);
            vector<string> varNames = {var};
            auto expr = parseExpression<complex<double>>(tokens, varNames);
            auto derivative = expr->dif(var);
            cout << derivative->ToString() << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            exit(1);
        }
    } else {
        cerr << "Error: Unknown mode: " << mode << endl;
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    parseArguments(argc, argv);
    return 0;
}
