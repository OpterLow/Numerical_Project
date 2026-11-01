#include "algorithms.h"
#include <cmath>
#include <iostream>
#include "config.h"

using std::nullopt;

EvalResult evaluateFunction(double x, const AppConfig& config, char derivMode) {
    const bool computeDerivative = (derivMode == DERIV_ANALYTIC);

    if (config.functionType == "polynomial") {
        return runHorner(x, config, computeDerivative);
    } 

    else if (config.functionType == "cos") {
        // cos x = c; where  -1 < c < 1, and  0 < x < pi  
        if (config.constants.size() >= 1) {
            double v = cos(x) - config.constants[0];
            if (computeDerivative) {
                return {v, -sin(x)};
            }
            return {v, nullopt};
        }

    }
    else if (config.functionType == "sin") {
        //  sin x = c; where -1 < c < 1, and −pi/2 < x < pi/2 
        if (config.constants.size() >= 1) {
            double v = sin(x) - config.constants[0];
            if (computeDerivative) {
                return {v, cos(x)};
            }
            return {v, nullopt};
        }
    }
    
    else if (config.functionType == "tan") {
        // 4. TAN: tan x = c; where -inf < c < inf, and −pi/2 < x < pi/2 
        if (config.constants.size() >= 1) {
            double v = tan(x) - config.constants[0];
            if (computeDerivative) {
                return {v, 1.0 / (cos(x) * cos(x))};
            }
            return {v, nullopt};
        }
    }

    else if (config.functionType == "exp") {
        // 5. EXP: e^x = c; where c > 0, and -inf < x < inf
        if (config.constants.size() >= 1) {
            double v = exp(x) - config.constants[0];
            if (computeDerivative) {
                return {v, exp(x)};
            }
            return {v, nullopt};
        }
    }
    else if (config.functionType == "log") {
        // 6. LOG: ln x = c; where -inf < c < inf, and x > 0
        if (config.constants.size() >= 1) {
            double v = log(x) - config.constants[0];
            if (computeDerivative) {
                return {v, 1.0 / x};
            }
            return {v, nullopt};
        }
    }

    std::cerr << "Error: Unknown or unsupported function type for evaluation.\n";
    return {0.0, nullopt};
}