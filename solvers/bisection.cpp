#include "../algorithms.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

// Bisection method for finding roots of a function
// inputs:  (string) function type, interval [a, b], constants

double runBisection(const AppConfig& config) {
    double a = config.a;
    double b = config.b;
    double root = 0.0;

    int max_iter = ceil((log(b - a) - log(config.tol)) / log(2));
    
    for (int i = 0; i < max_iter; ++i) {
        root = (a + b) / 2.0;
        double f_root = 0.0; // Replace with actual function evaluation using config
        if (fabs(f_root) < config.tol) {
            break;
        }
        double f_a = 0.0; // Replace with actual function evaluation using config
        if (f_a * f_root < 0) {
            b = root;
        } else {
            a = root;
        }
    }
    return root;
}