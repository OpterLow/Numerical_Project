#include "algorithms.h"
#include <cmath>
#include <iostream>

double evaluateFunction(double x, const AppConfig& config) {
    if (config.functionType == "polynomial") {
        return runHorner(x, config);
    } 

    else if (config.functionType == "cos") {
        // Example: c[0] * sin(c[1] * x)
        if (config.constants.size() >= 2) {
            return config.constants[0] * sin(config.constants[1] * x);
        }
    }

    else if (config.functionType == "sin") {
        // Example: c[0] * sin(c[1] * x)
        if (config.constants.size() >= 2) {
            return config.constants[0] * sin(config.constants[1] * x);
        }
    }
    
    else if (config.functionType == "tan") {
        // Example: c[0] * tan(c[1] * x)
        if (config.constants.size() >= 2) {
            return config.constants[0] * tan(config.constants[1] * x);
        }
    }

    else if (config.functionType == "exp") {
        // Example: c[0] * e^(c[1] * x) + c[2]
        if (config.constants.size() >= 2) {
            return config.constants[0] * exp(config.constants[1] * x);
        }
    } 

    std::cerr << "Error: Unknown or unsupported function type for evaluation.\n";
    return 0.0;
}