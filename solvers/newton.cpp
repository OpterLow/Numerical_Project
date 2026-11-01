#include "algorithms.h"
#include <cmath>
#include <iostream>

using namespace std;

// Newton's method for finding roots of a function
// derivMode: DERIV_ANALYTIC uses the exact derivative, DERIV_NUMERIC a finite difference
SolverResult runNewton(const AppConfig& config, char derivMode) {
    const int maxIter = 100;
    double x = (config.a + config.b) / 2.0;

    for (int i = 0; i < maxIter; ++i) {
        EvalResult r = evaluateFunction(x, config, derivMode);
        if (fabs(r.value) < config.tol) {
            return {x, i + 1, true};
        }

        double deriv;
        if (derivMode == DERIV_ANALYTIC && r.derivative) {
            deriv = *r.derivative;
        } else {
            deriv = numericalDerivative(x, config);
        }

        if (deriv == 0.0 || !isfinite(deriv)) {
            cerr << "Newton: derivative is zero or invalid at x = " << x << "\n";
            return {x, i + 1, false};
        }

        double xNew = x - r.value / deriv;
        if (fabs(xNew - x) < config.tol) {
            return {xNew, i + 1, true};
        }
        x = xNew;
    }

    cerr << "Newton: reached the maximum number of iterations\n";
    return {x, maxIter, false};
}
