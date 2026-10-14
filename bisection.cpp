#include "algorithms.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

// Bisection method for finding roots of a function
// inputs:  (string) function type, interval [a, b], constants

double tol = 1e-6; // tolerance for the bisection method
double runBisection(const AppConfig& config, double tol, int max_iter) {
    double a = config.a;
    double b = config.b;
    double root = 0.0;
}