#include <iostream>
#include "config.h"
#include "algorithms.h"

using namespace std;

// usage: ./mySolver functionType Solver Constants A B
// functions: poly, cos, sin, tan, exp, log
// solvers: bisection, newton, false_position

// todo: enforce bounds depending on functions
// todo: make all inputs uppercase

int main(int argc, char** argv) {
    AppConfig config;

    if (!parseArguments(argc, argv, config)) {
        cerr << "Usage: " << argv[0] << " <functionType> <solver> <a> <b> [constants...]\n";
        return 1;
    }


    // 2. Route to the requested algorithm
    if (config.solver == "bisection") {

        double root = runBisection(config);
        cout << "Bisection Root: " << root << endl;
    } 
    else if (config.solver == "newton") {
        double root = runNewton(config);
        cout << "Newton Root: " << root << endl;
    } 
    else if (config.solver == "false_position") {
        double root = runFalsePosition(config);
        cout << "False Position Root: " << root << endl;
    }
    else {
        cerr << "Unknown solver type: " << config.solver << "\n";
        return 1;
    }

    return 0;
}