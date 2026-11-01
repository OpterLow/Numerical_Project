#include "../algorithms.h"
#include "../config.h"
#include <iostream>
#include <cmath>

using namespace std;

// Forward declaration to satisfy the compiler when the implementation is
// available elsewhere in the project.
double evaluateFunction(double x, const AppConfig& config, bool derivative);

double runNewton(const AppConfig& config) {
    double x = (config.a + config.b) / 2.0; // Initial guess: midpoint
    int max_iter = 1000;

    for (int i = 0; i < max_iter; ++i) {
        double f_val = evaluateFunction(x, config, false);

        if (fabs(f_val) < config.tol) {
            return x;
        }

        double f_prime = evaluateFunction(x, config, true);
        if (fabs(f_prime) < 1e-12) {
            cerr << "Error: Derivative near zero in Newton's method.\n";
            return x;
        }

        x = x - f_val / f_prime;
    }

    return x;
}