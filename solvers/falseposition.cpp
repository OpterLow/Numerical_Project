#include "../algorithms.h"
#include "../config.h"
#include <iostream>
#include <cmath>

using namespace std;

double runFalsePosition(const AppConfig& config) {
    double a = config.a;
    double b = config.b;
    double root = a;

    double f_a = evaluateFunction(a, config);
    double f_b = evaluateFunction(b, config);

    if (f_a * f_b >= 0) {
        cerr << "Error: False position requires f(a) and f(b) to have opposite signs.\n";
        return 0.0;
    }

    for (int i = 0; i < 1000; ++i) {
        root = (a * f_b - b * f_a) / (f_b - f_a);
        double f_root = evaluateFunction(root, config);

        if (fabs(f_root) < config.tol || fabs(b - a) < config.tol) {
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

    return root;
}