#include "config.h"
#include "algorithms.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// usage: ./mySolver problem solver constants... a b

static string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
    return s;
}

static bool parseNumber(const char* text, double& out) {
    try {
        size_t used = 0;
        out = stod(text, &used);
        return used == string(text).size() && isfinite(out);
    } catch (const exception&) {
        return false;
    }
}

bool parseArguments(int argc, char** argv, AppConfig& config, string& error) {
    vector<char*> positional(argv + 1, argv + argc);

    if (positional.size() < 5) {
        error = "expected at least 5 arguments";
        return false;
    }

    config.functionType = toLower(positional[0]);
    config.solver = toLower(positional[1]);

    for (size_t i = 2; i < positional.size(); ++i) {
        double value;
        if (!parseNumber(positional[i], value)) {
            error = string("argument '") + positional[i] + "' is not a valid finite number";
            return false;
        }
        if (i < positional.size() - 2) config.constants.push_back(value);
        else if (i == positional.size() - 2) config.a = value;
        else config.b = value;
    }
    return true;
}

bool validateConfig(const AppConfig& config, string& error) {
    const double pi = acos(-1.0);
    const string& type = config.functionType;

    const char* problems[] = {"poly", "cos", "sin", "tan", "exp", "log"};
    if (find(begin(problems), end(problems), type) == end(problems)) {
        error = "unknown problem type '" + type + "' (use POLY, COS, SIN, TAN, EXP or LOG)";
        return false;
    }
    const char* solvers[] = {"bisec", "falsepos", "newton1", "newton2", "bracket-newton1", "bracket-newton2"};
    if (find(begin(solvers), end(solvers), config.solver) == end(solvers)) {
        error = "unknown solver '" + config.solver +
                "' (use BiSec, FalsePos, Newton1, Newton2, Bracket-Newton1 or Bracket-Newton2)";
        return false;
    }

    if (type == "poly") {
        if (config.constants.empty()) {
            error = "POLY needs at least one coefficient before a and b";
            return false;
        }
        if (config.constants.front() == 0.0) {
            error = "the leading coefficient of the polynomial must be nonzero";
            return false;
        }
    } else if (config.constants.size() != 1) {
        error = "this problem takes exactly one constant c, then a and b";
        return false;
    }

    if (!(config.a < config.b)) {
        error = "the interval must satisfy a < b";
        return false;
    }

    const double c = config.constants.empty() ? 0.0 : config.constants[0];
    if ((type == "cos" || type == "sin") && (c < -1.0 || c > 1.0)) {
        error = "c must be in [-1, 1]";
        return false;
    }
    if (type == "exp" && c <= 0.0) {
        error = "c must be greater than 0 for EXP";
        return false;
    }
    if (type == "cos" && (config.a < 0.0 || config.b > pi)) {
        error = "COS interval must lie within [0, pi]";
        return false;
    }
    if (type == "sin" && (config.a < -pi / 2 || config.b > pi / 2)) {
        error = "SIN interval must lie within [-pi/2, pi/2]";
        return false;
    }
    if (type == "tan" && (config.a <= -pi / 2 || config.b >= pi / 2)) {
        error = "TAN interval must lie strictly inside (-pi/2, pi/2)";
        return false;
    }
    if (type == "log" && config.a <= 0.0) {
        error = "LOG interval must have a > 0";
        return false;
    }

    // Assignment note 1: only check that f(a) * f(b) <= 0
    double fa = evaluateFunction(config.a, config, DERIV_NONE).value;
    double fb = evaluateFunction(config.b, config, DERIV_NONE).value;
    if (!(fa * fb <= 0.0)) {
        error = "f(a) and f(b) must have opposite signs (f(a)*f(b) <= 0)";
        return false;
    }
    return true;
}