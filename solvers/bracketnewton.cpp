#include "algorithms.h"
#include <cmath>
#include <iostream>

using namespace std;

// Bracket-Newton: Newton's method safeguarded by bisection.
// The root stays bracketed in [a, b]. A Newton step is used when it lands inside
// the bracket and reduces |f|; otherwise a bisection step is taken instead.

SolverResult runBracketNewton(const AppConfig& config, char derivMode) {
    const int maxIter = 200;
    double a = config.a;
    double b = config.b;
    double fa = evaluateFunction(a, config, DERIV_NONE).value;
    double fb = evaluateFunction(b, config, DERIV_NONE).value;

    if (fa * fb > 0) {
        cerr << "Error: Bracket-Newton requires f(a) and f(b) to have opposite signs.\n";
        return {0.0, 0, false};
    }
    if (fa == 0.0) return {a, 0, true};
    if (fb == 0.0) return {b, 0, true};

    double x = (a + b) / 2.0;
    for (int i = 0; i < maxIter; ++i) {
        EvalResult r = evaluateFunction(x, config, derivMode);
        double fx = r.value;
        if (fabs(fx) < config.tol || fabs(b - a) < config.tol) {
            return {x, i + 1, true};
        }

        // Shrink the bracket using the sign of f(x)
        if (fa * fx < 0) {
            b = x;
            fb = fx;
        } else {
            a = x;
            fa = fx;
        }

        double deriv;
        if (derivMode == DERIV_ANALYTIC && r.derivative) {
            deriv = *r.derivative;
        } else {
            deriv = numericalDerivative(x, config);
        }

        bool useBisection = true;
        double xNew = (a + b) / 2.0;
        if (deriv != 0.0 && isfinite(deriv)) {
            double xNewton = x - fx / deriv;
            if (xNewton > a && xNewton < b) {
                double fNewton = evaluateFunction(xNewton, config, DERIV_NONE).value;
                if (fabs(fNewton) < fabs(fx)) {
                    xNew = xNewton;
                    useBisection = false;
                }
            }
        }

        if (!useBisection && fabs(xNew - x) < config.tol) {
            return {xNew, i + 1, true};
        }
        x = xNew;
    }

    cerr << "Bracket-Newton: reached the maximum number of iterations\n";
    return {x, maxIter, false};
}
