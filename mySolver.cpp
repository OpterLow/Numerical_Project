#include <iostream>
#include "config.h"
#include "algorithms.h"

using namespace std;

int main(int argc, char** argv) {
    AppConfig config;

<<<<<<< HEAD
    if (argc > 1) {
        equationType = argv[1];
        solver = argv[2];
        // Parse constants
        for (int i = 3; i < argc - 2; ++i) {
            constants.push_back(atof(argv[i]));
        }
        a = atof(argv[argc - 2]);
        b = atof(argv[argc - 1]);
        
        // run each solver based on the input, with the provided constants and interval [a, b]
<<<<<<< HEAD
        // construct arguments string for the solver: "a b <equationType> <constants vector>"
        string arguments;
        arguments = to_string(a) + " " + to_string(b) + " " + equationType;
        for (double c : constants) {
            arguments += " " + to_string(c);
=======
        // construct arguments string for the solver: "a b <equationType> <constants vector>"
        string arguments;
        arguments = to_string(a) + " " + to_string(b) + " " + equationType;
        for (double c : constants) {
            arguments += " " + to_string(c);
>>>>>>> origin/main
        }

        // vanity print of the constructed arguments string
        string vanityArguments = "a = " + to_string(a) + ", b = " + to_string(b) + ", equationType = " + equationType + ", constants =";
        for (double c : constants) {
            vanityArguments += " " + to_string(c);
        }
        
        if (solver == "bisection") {
            // Call bisection method
            // system(("./bisection " + arguments).c_str());
<<<<<<< HEAD
            cout << "Running bisection with arguments: " << vanityArguments << endl;
=======
            cout << "Running bisection with arguments: " << vanityArguments << endl;
>>>>>>> origin/main

        } else if (solver == "newton") {
            // Call Newton's method
            cout << "Running newton with arguments: " << vanityArguments << endl;
        } else if (solver == "false position") {
            // Call false position method
            cout << "Running false position with arguments: " << vanityArguments << endl;
        } else {
            cerr << "Unknown solver: " << solver << endl;
        }
        return 0;
        
    }
    else {
        cerr << "Usage: " << argv[0] << " <equationType> <solver> <constants...> <a> <b>" << endl;
        return 1;
    }
}
=======
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
>>>>>>> feature/kennym
