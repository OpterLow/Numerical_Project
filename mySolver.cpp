#include <iostream>
#include "config.h"
#include "algorithms.h"

using namespace std;

int main(int argc, char** argv) {
    AppConfig config;

    if (!parseArguments(argc, argv, config)) {
        cerr << "Usage: " << argv[0] << " <a> <b> <functionType> [constants...]\n";
        return 1;
    }

    // 2. Route to the requested algorithm
    if (config.functionType == "bisection") {
        double root = runBisection(config);
        cout << "Bisection Root: " << root << endl;
    } 
    else if (config.functionType == "newton") {
        double root = runNewton(config);
        cout << "Newton Root: " << root << endl;
    } 
    else {
        cerr << "Unknown function type: " << config.functionType << "\n";
        return 1;
    }

    return 0;
}