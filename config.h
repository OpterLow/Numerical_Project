#pragma once // Prevents the header from being included multiple times
#include <string>
#include <vector>

struct AppConfig {
    double a;
    double b;
    std::string functionType;
    std::string solver;
    std::vector<double> constants;
    double tol = 1e-5;
};

// Function declaration
bool parseArguments(int argc, char** argv, AppConfig& config);