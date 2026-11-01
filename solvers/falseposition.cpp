#include "../algorithms.h"
#include "../config.h"
#include <iostream>
#include <cmath>

using namespace std;

SolverResult runFalsePosition(const AppConfig& config) {
    double a = config.a;
    double b = config.b;
    double root = a;
    int iterations = 0;

    double f_a = evaluateFunction(a, config).value;
    double f_b = evaluateFunction(b, config).value;

    if (f_a == 0.0) return {a, 0, true};
    if (f_b == 0.0) return {b, 0, true};
    if (f_a * f_b > 0) {
        cerr << "Error: False position requires f(a) and f(b) to have opposite signs.\n";
        return {0.0, 0, false};
    }

    const int maxIter = 1000;
    bool converged = false;
    for (int i = 0; i < maxIter; ++i) {
        iterations = i + 1;
        root = (a * f_b - b * f_a) / (f_b - f_a);
        double f_root = evaluateFunction(root, config).value;

        if (fabs(f_root) < config.tol || fabs(b - a) < config.tol) {
            converged = true;
            break;
        }

        if (f_a * f_root < 0) {
            b = root;
            f_b = f_root;
        } else {
            a = root;
            f_a = f_root;
        }
    }

    if (!converged) {
        cerr << "False position: reached the maximum number of iterations\n";
    }
    return {root, iterations, converged};
}