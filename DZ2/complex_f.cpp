#include "complex_f.h"
#include "token.h"
#include "parser.h"
#include "expression.h"

#include <sstream>
#include <map>
using namespace std;


string formatComplex(complex<double> value) {
    ostringstream oss;
    if (value.imag() == 0) {
        oss << value.real();
    } else if (value.real() == 0) {
        oss << value.imag() << "i";
    } else {
        oss << value.real() << " + " << value.imag() << "i";
    }
    return oss.str();
}

string ParseArguments(int argc, char* argv[]) {
    if (argc < 2) {
        return "-1";
    }

    string mode = argv[1];

    if (mode == "--eval") {
        if (argc < 3) {
            return "-1";
        }

        string expression = argv[2];
        map<string, complex<double>> variables;
        for (int i = 3; i < argc; i++) {
            string arg = argv[i];
            size_t eqPos = arg.find('=');
            if (eqPos == string::npos) {
                return "-1";
            }
            string var = arg.substr(0, eqPos);
            double value = stod(arg.substr(eqPos + 1));
            variables[var] = value;
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
            return formatComplex(result);
        } catch (const exception& e) {
            return "-1";
        }
    } else if (mode == "--diff") {
        if (argc < 5 || string(argv[3]) != "--by") {
            return "-1";
        }

        string expression = argv[2];
        string var = argv[4];
        try {
            auto tokens = tokenize(expression);
            vector<string> varNames = {var};
            auto expr = parseExpression<complex<double>>(tokens, varNames);
            auto derivative = expr->dif(var);
            return derivative->ToString();
        } catch (const exception& e) {
            return "-1";
        }
    } else {
        return "-1";
    }
}


