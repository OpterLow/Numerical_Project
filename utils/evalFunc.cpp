#include "algorithms.h"
#include <cmath>
#include <iostream>
#include "config.h"

double evaluateFunction(double x, const AppConfig& config, bool computeDerivative) {
    if (config.functionType == "polynomial") {
        const auto result = runHorner(x, config, computeDerivative);
        return computeDerivative ? result.second : result.first;
    } 

    else if (config.functionType == "cos") {
        // Example: cos x = c; where  -1 < c < 1, and  0 < x < pi  
        if (config.constants.size() >= 1) {
            return acos(config.constants[0]);
        }

    }
    else if (config.functionType == "sin") {
        //  sin𝑥 =𝑐; where 𝑐 ∈[−1,1], and 𝑥 ∈[−𝜋/2 ,𝜋/2 ] 
        if (config.constants.size() >= 2) {
            return config.constants[0] * sin(config.constants[1] * x);
        }
    }
    
    else if (config.functionType == "tan") {
        // 4. TAN: tan𝑥 =𝑐; where 𝑐 ∈(−∞,+∞), and 𝑥 ∈(−𝜋/2,𝜋/2 ) 

        if (config.constants.size() >= 2) {
            return config.constants[0] * tan(config.constants[1] * x);
        }
    }

    else if (config.functionType == "exp") {
        // 5. EXP: 𝑒𝑥 =𝑐; where 𝑎 ∈(0,+∞), and 𝑥 ∈(−∞,+∞) 
        // 6. LOG: ln𝑥 =𝑐; where 𝑎 ∈(−∞,+∞), and 𝑥 ∈(0,+∞)
        if (config.constants.size() >= 2) {
            return config.constants[0] * exp(config.constants[1] * x);
        }
    } 

    std::cerr << "Error: Unknown or unsupported function type for evaluation.\n";
    return 0.0;
}