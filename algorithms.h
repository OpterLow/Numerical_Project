#pragma once
#include "config.h"
#include <utility>

// Declaration of the bisection solver function
double runBisection(const AppConfig& config);
double runNewton(const AppConfig& config);
double runFalsePosition(const AppConfig& config);
std::pair<double, double> runHorner(double x, const AppConfig& config, bool computeDerivative = false);