#pragma once
#include "config.h"
#include <utility>

double evaluateFunction(double x, const AppConfig& config, bool computeDerivative = false);

double runBisection(const AppConfig& config);
double runNewton(const AppConfig& config);
double runFalsePosition(const AppConfig& config);
std::pair<double, double> runHorner(double x, const AppConfig& config, bool computeDerivative = false);