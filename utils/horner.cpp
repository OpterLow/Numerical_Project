#include <stdexcept>
#include <vector>
#include "../config.h"
#include "../algorithms.h"

using namespace std;

pair<double, double> runHorner(double x, const AppConfig& config, bool computeDerivative) {
    const vector<double>& coefficients = config.constants;
    if (coefficients.empty()) {
        throw invalid_argument("Polynomial must have at least one coefficient");
    }

    double value = coefficients.front();
    double derivative = 0.0;
    vector<double> quotientCoefficients;
    if (computeDerivative) {
        quotientCoefficients.reserve(coefficients.size() - 1);
    }

    for (size_t i = 1; i < coefficients.size(); ++i) {
        if (computeDerivative) {
            quotientCoefficients.push_back(value);
        }
        value = value * x + coefficients[i];
    }

    if (computeDerivative) {
        for (double coefficient : quotientCoefficients) {
            derivative = derivative * x + coefficient;
        }
    }

    return {value, derivative};
}