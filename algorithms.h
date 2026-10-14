#pragma once
#include "config.h"

// Declaration of the bisection solver function
double runBisection(const AppConfig& config);
double runNewton(const AppConfig& config);
double runFalsePosition(const AppConfig& config);