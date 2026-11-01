#include "../algorithms.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

// Bisection method for finding roots of a function
// inputs:  (string) function type, interval [a, b], constants

SolverResult runBisection(const AppConfig& config) {
    double a = config.a;
    double b = config.b;
    double root = 0.0;
    int iterations = 0;

    int max_iter = ceil((log(b - a) - log(config.tol)) / log(2));

    double f_a = evaluateFunction(a, config, DERIV_NONE).value;
    if (f_a == 0.0) return {a, 0, true};
    if (evaluateFunction(b, config, DERIV_NONE).value == 0.0) return {b, 0, true};

    for (int i = 0; i < max_iter; ++i) {
        iterations = i + 1;
        root = (a + b) / 2.0;
        double f_root = evaluateFunction(root, config, DERIV_NONE).value;

        if (fabs(f_root) < config.tol) {
            break;
        }

        if (f_a * f_root < 0) {
            b = root;
        } else {
            a = root;
            f_a = f_root;
        }
    }
    return {root, iterations, true};
}