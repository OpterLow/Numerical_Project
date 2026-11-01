#pragma once // Prevents the header from being included multiple times
#include <string>
#include <vector>

struct AppConfig {
    double a;
    double b;
    std::string functionType;
    std::string solver;
    std::vector<double> constants;
    double tol = 1e-12;
    double step = 1e-5;   // step for the numerical derivative
};

// Function declarations
bool parseArguments(int argc, char** argv, AppConfig& config, std::string& error);
bool validateConfig(const AppConfig& config, std::string& error);
