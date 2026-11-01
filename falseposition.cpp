#include "algorithms.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;
    // struct AppConfig {
    //     double a;
    //     double b;
    //     std::string functionType;
    //     std::string solver;
    //     std::vector<double> constants;
    //     double tol = 1e-5;
    // };
double tol = 1e-6; // tolerance for the false position method method
double runFalsePosition(const AppConfig& config, double tol, int max_iter) {
    double a = config.a;
    double b = config.b;
    double root = 0.0;
}