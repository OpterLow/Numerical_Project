#include "algorithms.h"

double numericalDerivative(double x, const AppConfig& config, double h) {
    if (h <= 0.0) {
        h = 1e-5;
    }
    double fPlus = evaluateFunction(x + h, config, DERIV_NONE).value;
    double fMinus = evaluateFunction(x - h, config, DERIV_NONE).value;
    return (fPlus - fMinus) / (2.0 * h);
}
