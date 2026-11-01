#pragma once
#include "config.h"
#include <optional>

// Declaration of the bisection solver function
double runBisection(const AppConfig& config);
double runNewton(const AppConfig& config, char derivMode);
double runFalsePosition(const AppConfig& config);

// Derivative modes: none, analytic (from evaluateFunction), numeric (finite difference)
const char DERIV_NONE     = '0';
const char DERIV_ANALYTIC = 'A';
const char DERIV_NUMERIC  = 'N';

// Result of evaluating f(x). derivative is empty unless it was requested
// (and supported for the function type).
struct EvalResult {
    double value;
    std::optional<double> derivative;
};

EvalResult runHorner(double x, const AppConfig& config, bool computeDerivative = false);
// derivative is only filled in when derivMode == DERIV_ANALYTIC
EvalResult evaluateFunction(double x, const AppConfig& config, char derivMode = DERIV_NONE);

// Central-difference estimate of f'(x). h <= 0 uses the default step 1e-5.
double numericalDerivative(double x, const AppConfig& config, double h = 0.0);
