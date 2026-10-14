#include "config.h"
#include <iostream>
using namespace std;

// for usage ./mySolver functionType solver constants a b
 
bool parseArguments(int argc, char** argv, AppConfig& config) {
    if (argc < 6) return false;
    
    config.functionType = argv[1];
    config.solver = argv[2];

    for (int i = 3; i < argc; ++i) {
        config.constants.push_back(stod(argv[i]));
    }
    config.a = stod(argv[argc-2]);
    config.b = stod(argv[argc-1]);
    return true;
}